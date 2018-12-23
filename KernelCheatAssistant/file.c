#include "kca.h"

PVOID  g_CallBackHandle = NULL;
WCHAR  g_FilePath[265] = { 0 };
HANDLE g_CurrentProcessId = 0;

UNICODE_STRING  GetFilePathByFileObject(PVOID FileObject)
{
	POBJECT_NAME_INFORMATION ObjetNameInfor;
	IoQueryFileDosDeviceName((PFILE_OBJECT)FileObject, &ObjetNameInfor);
	return ObjetNameInfor->Name;
}
VOID EnableObType(POBJECT_TYPE ObjectType)
{
	POBJECT_TYPE_TEMP  ObjectTypeTemp = (POBJECT_TYPE_TEMP)ObjectType;
	ObjectTypeTemp->TypeInfo.SupportsObjectCallbacks = 1;
}

OB_PREOP_CALLBACK_STATUS PreCallBack(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION OperationInformation)
{
	UNICODE_STRING uniDosName;
	UNICODE_STRING uniFilePath;
	PFILE_OBJECT FileObject = (PFILE_OBJECT)OperationInformation->Object;
	HANDLE CurrentProcessId = PsGetCurrentProcessId();
	if (OperationInformation->ObjectType != *IoFileObjectType)
	{
		return OB_PREOP_SUCCESS;
	}
	//过滤无效指针
	if (FileObject->FileName.Buffer == NULL ||
		!MmIsAddressValid(FileObject->FileName.Buffer) ||
		FileObject->DeviceObject == NULL ||
		!MmIsAddressValid(FileObject->DeviceObject))
	{
		return OB_PREOP_SUCCESS;
	}
	uniFilePath = GetFilePathByFileObject(FileObject);
	if (uniFilePath.Buffer == NULL || uniFilePath.Length == 0)
	{
		return OB_PREOP_SUCCESS;
	}
	if (g_CurrentProcessId == CurrentProcessId)
	{
		return OB_PREOP_SUCCESS;
	}
	if (wcsstr(uniFilePath.Buffer, g_FilePath) || wcsstr(uniFilePath.Buffer, DRIVER_FILE_NAME))
	{
		//dprintf("PID : %ld File : %wZ  %wZ\r\n", (ULONG64)CurrentProcessId, &uniDosName, &uniFilePath);
		//dprintf("g_FilePath->:%ls", g_FilePath);
		if (
			FileObject->DeleteAccess == TRUE || 
			FileObject->WriteAccess == TRUE ||
			FileObject->ReadAccess == TRUE ||
			FileObject->SharedRead == TRUE ||
			FileObject->SharedWrite == TRUE ||
			FileObject->SharedDelete == TRUE
			)
		{
			if (OperationInformation->Operation == OB_OPERATION_HANDLE_CREATE)
			{
				OperationInformation->Parameters->CreateHandleInformation.DesiredAccess = 0;
			}
			if (OperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
			{
				OperationInformation->Parameters->DuplicateHandleInformation.DesiredAccess = 0;
			}
		}
	}
	RtlVolumeDeviceToDosName(FileObject->DeviceObject, &uniDosName);
	
	return OB_PREOP_SUCCESS;
}


NTSTATUS KcaProtectFileByObRegisterCallbacks(HANDLE ProcessId)
{
	OB_CALLBACK_REGISTRATION  CallBackReg;
	OB_OPERATION_REGISTRATION OperationReg;
	NTSTATUS  Status;

	g_CurrentProcessId = ProcessId;
	GetProcessPathBySectionObject(ProcessId, g_FilePath);

	//dprintf("g_FilePath->:%s", g_FilePath);

	EnableObType(*IoFileObjectType);      //开启文件对象回调
	memset(&CallBackReg, 0, sizeof(OB_CALLBACK_REGISTRATION));
	CallBackReg.Version = ObGetFilterVersion();
	CallBackReg.OperationRegistrationCount = 1;
	CallBackReg.RegistrationContext = NULL;
	RtlInitUnicodeString(&CallBackReg.Altitude, L"401900"); 
	//RtlInitUnicodeString(&CallBackReg.Altitude, L"321000");
	memset(&OperationReg, 0, sizeof(OB_OPERATION_REGISTRATION)); //初始化结构体变量


	OperationReg.ObjectType = IoFileObjectType;
	OperationReg.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;

	OperationReg.PreOperation = (POB_PRE_OPERATION_CALLBACK)&PreCallBack; //在这里注册一个回调函数指针
	CallBackReg.OperationRegistration = &OperationReg; //注意这一条语句   将结构体信息放入大结构体
	Status = ObRegisterCallbacks(&CallBackReg, &g_CallBackHandle);
	if (!NT_SUCCESS(Status))
	{
		Status = STATUS_UNSUCCESSFUL;
	}
	else
	{
		Status = STATUS_SUCCESS;
	}
	return Status;
}


VOID KcaUnProtectFileByObRegisterCallbacks()
{
	if (g_CallBackHandle != NULL)
	{
		ObUnRegisterCallbacks(g_CallBackHandle);
		g_CallBackHandle = NULL;
	}
}