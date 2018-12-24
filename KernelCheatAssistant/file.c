#include "kca.h"
//
//PVOID  g_CallBackHandle = NULL;
//WCHAR  g_FilePath[265] = { 0 };
//HANDLE g_CurrentProcessId = 0;
//
//UNICODE_STRING  GetFilePathByFileObject(PVOID FileObject)
//{
//	POBJECT_NAME_INFORMATION ObjetNameInfor;
//	IoQueryFileDosDeviceName((PFILE_OBJECT)FileObject, &ObjetNameInfor);
//	return ObjetNameInfor->Name;
//}
//VOID EnableObType(POBJECT_TYPE ObjectType)
//{
//	POBJECT_TYPE_TEMP  ObjectTypeTemp = (POBJECT_TYPE_TEMP)ObjectType;
//	ObjectTypeTemp->TypeInfo.SupportsObjectCallbacks = 1; 
//}
//
//OB_PREOP_CALLBACK_STATUS PreCallBack(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION OperationInformation)
//{
//	UNICODE_STRING uniDosName;
//	UNICODE_STRING uniFilePath;
//	PFILE_OBJECT FileObject = (PFILE_OBJECT)OperationInformation->Object;
//	HANDLE CurrentProcessId = PsGetCurrentProcessId();
//	if (OperationInformation->ObjectType != *IoFileObjectType)
//	{
//		return OB_PREOP_SUCCESS;
//	}
//	//过滤无效指针
//	if (FileObject->FileName.Buffer == NULL ||
//		!MmIsAddressValid(FileObject->FileName.Buffer) ||
//		FileObject->DeviceObject == NULL ||
//		!MmIsAddressValid(FileObject->DeviceObject))
//	{
//		return OB_PREOP_SUCCESS;
//	}
//	uniFilePath = GetFilePathByFileObject(FileObject);
//	if (uniFilePath.Buffer == NULL || uniFilePath.Length == 0)
//	{
//		return OB_PREOP_SUCCESS;
//	}
//	if (g_CurrentProcessId == CurrentProcessId)
//	{
//		return OB_PREOP_SUCCESS;
//	}
//	if (wcsstr(uniFilePath.Buffer, g_FilePath) || wcsstr(uniFilePath.Buffer, DRIVER_FILE_NAME))
//	{
//		//dprintf("PID : %ld File : %wZ  %wZ\r\n", (ULONG64)CurrentProcessId, &uniDosName, &uniFilePath);
//		//dprintf("g_FilePath->:%ls", g_FilePath);
//		if (
//			FileObject->DeleteAccess == TRUE || 
//			FileObject->WriteAccess == TRUE ||
//			FileObject->ReadAccess == TRUE ||
//			FileObject->SharedRead == TRUE ||
//			FileObject->SharedWrite == TRUE ||
//			FileObject->SharedDelete == TRUE
//			)
//		{
//			if (OperationInformation->Operation == OB_OPERATION_HANDLE_CREATE)
//			{
//				OperationInformation->Parameters->CreateHandleInformation.DesiredAccess = 0;
//			}
//			if (OperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
//			{
//				OperationInformation->Parameters->DuplicateHandleInformation.DesiredAccess = 0;
//			}
//		}
//	}
//	RtlVolumeDeviceToDosName(FileObject->DeviceObject, &uniDosName);
//	
//	return OB_PREOP_SUCCESS;
//}
//
//
//NTSTATUS KcaProtectFileByObRegisterCallbacks(HANDLE ProcessId)
//{
//	OB_CALLBACK_REGISTRATION  CallBackReg;
//	OB_OPERATION_REGISTRATION OperationReg;
//	NTSTATUS  Status;
//
//	g_CurrentProcessId = ProcessId;
//	GetProcessPathBySectionObject(ProcessId, g_FilePath);
//
//	//dprintf("g_FilePath->:%s", g_FilePath);
//
//	EnableObType(*IoFileObjectType);      //开启文件对象回调
//	memset(&CallBackReg, 0, sizeof(OB_CALLBACK_REGISTRATION));
//	CallBackReg.Version = ObGetFilterVersion();
//	CallBackReg.OperationRegistrationCount = 1;
//	CallBackReg.RegistrationContext = NULL;
//	RtlInitUnicodeString(&CallBackReg.Altitude, L"401900"); 
//	//RtlInitUnicodeString(&CallBackReg.Altitude, L"321000");
//	memset(&OperationReg, 0, sizeof(OB_OPERATION_REGISTRATION)); //初始化结构体变量
//
//
//	OperationReg.ObjectType = IoFileObjectType;
//	OperationReg.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;
//
//	OperationReg.PreOperation = (POB_PRE_OPERATION_CALLBACK)&PreCallBack; //在这里注册一个回调函数指针
//	CallBackReg.OperationRegistration = &OperationReg; //注意这一条语句   将结构体信息放入大结构体
//	Status = ObRegisterCallbacks(&CallBackReg, &g_CallBackHandle);
//	if (!NT_SUCCESS(Status))
//	{
//		Status = STATUS_UNSUCCESSFUL;
//	}
//	else
//	{
//		Status = STATUS_SUCCESS;
//	}
//	return Status;
//}
//
//
//VOID KcaUnProtectFileByObRegisterCallbacks()
//{
//	if (g_CallBackHandle != NULL)
//	{
//		ObUnRegisterCallbacks(g_CallBackHandle);
//		g_CallBackHandle = NULL;
//	}
//}


//typedef struct _AUX_ACCESS_DATA {
//	PPRIVILEGE_SET PrivilegesUsed;
//	GENERIC_MAPPING GenericMapping;
//	ACCESS_MASK AccessesToAudit;
//	ACCESS_MASK MaximumAuditMask;
//} AUX_ACCESS_DATA, *PAUX_ACCESS_DATA;
//
//
//NTSTATUS
//IoCompletionRoutine(
//	IN PDEVICE_OBJECT DeviceObject,
//	IN PIRP Irp,
//	IN PVOID Context)
//{
//	*Irp->UserIosb = Irp->IoStatus;
//	if (Irp->UserEvent)
//		KeSetEvent(Irp->UserEvent, IO_NO_INCREMENT, 0);
//	if (Irp->MdlAddress)
//	{
//		IoFreeMdl(Irp->MdlAddress);
//		Irp->MdlAddress = NULL;
//	}
//	IoFreeIrp(Irp);
//	return STATUS_MORE_PROCESSING_REQUIRED;
//}
//
//NTSTATUS
//IrpCreateFile(
//	OUT PFILE_OBJECT *FileObject,
//	IN ACCESS_MASK DesiredAccess,
//	IN PUNICODE_STRING FilePath,
//	OUT PIO_STATUS_BLOCK IoStatusBlock,
//	IN PLARGE_INTEGER AllocationSize OPTIONAL,
//	IN ULONG FileAttributes,
//	IN ULONG ShareAccess,
//	IN ULONG CreateDisposition,
//	IN ULONG CreateOptions,
//	IN PVOID EaBuffer OPTIONAL,
//	IN ULONG EaLength)
//{
//	NTSTATUS ntStatus;
//
//	HANDLE hFile;
//	PFILE_OBJECT pFile, _FileObject;
//	UNICODE_STRING UniDeviceNameString;
//	OBJECT_ATTRIBUTES ObjectAttributes;
//	PDEVICE_OBJECT DeviceObject, RealDevice;
//
//	PIRP Irp;
//	KEVENT kEvent;
//	PIO_STACK_LOCATION IrpSp;
//	ACCESS_STATE AccessState;
//	AUX_ACCESS_DATA AuxData;
//	IO_SECURITY_CONTEXT SecurityContext;
//
//	WCHAR DeviceNameString[] = L"\\DosDevices\\*:\\";
//
//	if (FilePath->Length < 6)
//		return STATUS_INVALID_PARAMETER;
//	// \\??\c:\xxxx
//
//	DeviceNameString[12] = FilePath->Buffer[0];
//
//	RtlInitUnicodeString(&UniDeviceNameString, DeviceNameString);
//	InitializeObjectAttributes(&ObjectAttributes, &UniDeviceNameString, OBJ_KERNEL_HANDLE, NULL, NULL);
//
//	ntStatus = IoCreateFile(&hFile,
//		GENERIC_READ | SYNCHRONIZE,
//		&ObjectAttributes,
//		IoStatusBlock,
//		NULL,
//		FILE_ATTRIBUTE_NORMAL,
//		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
//		FILE_OPEN,
//		FILE_SYNCHRONOUS_IO_NONALERT,
//		NULL,
//		0,
//		CreateFileTypeNone,
//		NULL,
//		IO_NO_PARAMETER_CHECKING);
//
//	if (!NT_SUCCESS(ntStatus))
//	{
//		KdPrint(("IrpCreateFile: IoCreateFile 0x%X.\n", ntStatus));
//		return ntStatus;
//	}
//	RecoverOneKernelRoutine("ObReferenceObjectByHandle");
//	ntStatus = ObReferenceObjectByHandle(hFile,
//		FILE_READ_ACCESS, // ACCESS_MASK
//		*IoFileObjectType,
//		KernelMode,
//		(PVOID*)&pFile,
//		0);
//
//	NtClose(hFile);
//
//	if (!NT_SUCCESS(ntStatus))
//	{
//		KdPrint(("IrpCreateFile: ObReferenceObjectByHandle 0x%X.\n", ntStatus));
//		return ntStatus;
//	}
//
//	DeviceObject = pFile->Vpb->DeviceObject;
//	RealDevice = pFile->Vpb->RealDevice;
//	ObDereferenceObject(pFile);
//
//	InitializeObjectAttributes(&ObjectAttributes, NULL, OBJ_CASE_INSENSITIVE, 0, NULL);
//
//	ntStatus = ObCreateObject(KernelMode,
//		*IoFileObjectType,
//		&ObjectAttributes,
//		KernelMode,
//		NULL,
//		sizeof(FILE_OBJECT),
//		0,
//		0,
//		(PVOID*)&_FileObject);
//
//	if (!NT_SUCCESS(ntStatus))
//	{
//		KdPrint(("IrpCreateFile: ObCreateObject 0x%X.\n", ntStatus));
//		return ntStatus;
//	}
//
//	Irp = IoAllocateIrp(DeviceObject->StackSize, FALSE);
//	if (Irp == NULL)
//	{
//		KdPrint(("IrpCreateFile: IoAllocateIrp 0x%X.\n", ntStatus));
//		ObDereferenceObject(_FileObject);
//		return STATUS_INSUFFICIENT_RESOURCES;
//	}
//
//	KeInitializeEvent(&kEvent, SynchronizationEvent, FALSE);
//
//	RtlZeroMemory(_FileObject, sizeof(FILE_OBJECT));
//	_FileObject->Type = IO_TYPE_FILE;
//	_FileObject->Size = sizeof(FILE_OBJECT);
//	_FileObject->DeviceObject = RealDevice;
//	_FileObject->Flags = FO_SYNCHRONOUS_IO;
//	////////\\??\c:\xxxxx
//	RtlInitUnicodeString(&_FileObject->FileName, &FilePath->Buffer[2]);
//	KdPrint(("准备打开文件：%ws\n", _FileObject->FileName.Buffer));
//	KeInitializeEvent(&_FileObject->Lock, SynchronizationEvent, FALSE);
//	KeInitializeEvent(&_FileObject->Event, NotificationEvent, FALSE);
//
//	RtlZeroMemory(&AuxData, sizeof(AUX_ACCESS_DATA));
//	ntStatus = SeCreateAccessState(&AccessState,
//		&AuxData,
//		DesiredAccess,
//		IoGetFileObjectGenericMapping());
//
//	if (!NT_SUCCESS(ntStatus))
//	{
//		KdPrint((" IrpCreateFile: SeCreateAccessState 0x%X.\n", ntStatus));
//		IoFreeIrp(Irp);
//		ObDereferenceObject(_FileObject);
//		return ntStatus;
//	}
//
//	SecurityContext.SecurityQos = NULL;
//	SecurityContext.AccessState = &AccessState;
//	SecurityContext.DesiredAccess = DesiredAccess;
//	SecurityContext.FullCreateOptions = 0;
//
//	Irp->MdlAddress = NULL;
//	Irp->AssociatedIrp.SystemBuffer = EaBuffer;
//	Irp->Flags = IRP_CREATE_OPERATION | IRP_SYNCHRONOUS_API;
//	Irp->RequestorMode = KernelMode;
//	Irp->UserIosb = IoStatusBlock;
//	Irp->UserEvent = &kEvent;
//	Irp->PendingReturned = FALSE;
//	Irp->Cancel = FALSE;
//	Irp->CancelRoutine = NULL;
//	Irp->Tail.Overlay.Thread = PsGetCurrentThread();
//	Irp->Tail.Overlay.AuxiliaryBuffer = NULL;
//	Irp->Tail.Overlay.OriginalFileObject = _FileObject;
//
//	IrpSp = IoGetNextIrpStackLocation(Irp);
//	IrpSp->MajorFunction = IRP_MJ_CREATE;
//	IrpSp->DeviceObject = DeviceObject;
//	IrpSp->FileObject = _FileObject;
//	IrpSp->Parameters.Create.SecurityContext = &SecurityContext;
//	IrpSp->Parameters.Create.Options = (CreateDisposition << 24) | CreateOptions;
//	IrpSp->Parameters.Create.FileAttributes = (USHORT)FileAttributes;
//	IrpSp->Parameters.Create.ShareAccess = (USHORT)ShareAccess;
//	IrpSp->Parameters.Create.EaLength = EaLength;
//
//	IoSetCompletionRoutine(Irp, IoCompletionRoutine, 0, TRUE, TRUE, TRUE);
//	//add 
//	RecoverIopfCompleteRequest();
//	ntStatus = IofCallDriverEx(DeviceObject, Irp);
//	if (ntStatus == STATUS_PENDING)
//		KeWaitForSingleObject(&kEvent, Executive, KernelMode, TRUE, 0);
//
//	ntStatus = IoStatusBlock->Status;
//
//	if (!NT_SUCCESS(ntStatus))
//	{
//		KdPrint(("IrpCreateFile: IoCallDriver 0x%X.\n", ntStatus));
//		_FileObject->DeviceObject = NULL;
//		ObDereferenceObject(_FileObject);
//	}
//	else
//	{
//		InterlockedIncrement((volatile LONG *)&_FileObject->DeviceObject->ReferenceCount);
//		if (_FileObject->Vpb)
//			InterlockedIncrement((volatile LONG *)&_FileObject->Vpb->ReferenceCount);
//		*FileObject = _FileObject;
//	}
//
//	return ntStatus;
//}
//UNICODE_STRING Name;
//IO_STATUS_BLOCK IoBlock;
//RtlInitUnicodeString(&Name,L"C:\\test1.exe");
//Status=IrpCreateFile(&FileObj,GENERIC_READ|DELETE,&Name,&IoBlock,0,FILE_ATTRIBUTE_NORMAL,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,FILE_OPEN,0,0,0);


