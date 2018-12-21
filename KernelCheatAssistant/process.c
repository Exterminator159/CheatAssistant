#include "kca.h"

#define PROCESS_TERMINATE                  (0x0001)  
#define PROCESS_CREATE_THREAD              (0x0002)  
#define PROCESS_SET_SESSIONID              (0x0004)  
#define PROCESS_VM_OPERATION               (0x0008)  
#define PROCESS_VM_READ                    (0x0010)  
#define PROCESS_VM_WRITE                   (0x0020)  
#define PROCESS_DUP_HANDLE                 (0x0040)  
#define PROCESS_CREATE_PROCESS             (0x0080)  
#define PROCESS_SET_QUOTA                  (0x0100)  
#define PROCESS_SET_INFORMATION            (0x0200)  
#define PROCESS_QUERY_INFORMATION          (0x0400)  
#define PROCESS_SUSPEND_RESUME             (0x0800)  
#define PROCESS_QUERY_LIMITED_INFORMATION  (0x1000)  
#define PROCESS_SET_LIMITED_INFORMATION    (0x2000) 

HANDLE g_ProtegeProcessId = NULL;
PVOID g_RegistrationHandle = NULL;//定义一个void*类型的变量，它将会作为ObRegisterCallbacks函数的第2个参数。

HANDLE KcaGetProcessHandle(PEPROCESS Process)
{
	HANDLE ProcessHandle = NULL;
	ObOpenObjectByPointer(
		Process,
		0,
		NULL,
		PROCESS_ALL_ACCESS,
		*PsProcessType,
		KernelMode,
		&ProcessHandle
	);
	return ProcessHandle;
}


OB_PREOP_CALLBACK_STATUS CallbackRegistration(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION pOperationInformation)
{
	HANDLE pid = PsGetProcessId((PEPROCESS)pOperationInformation->Object);
	UNREFERENCED_PARAMETER(RegistrationContext);
	if (pid == g_ProtegeProcessId)
	{
		if (pOperationInformation->Operation == OB_OPERATION_HANDLE_CREATE || pOperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
		{
			if ((pOperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_TERMINATE) == PROCESS_TERMINATE)
			{
				pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_TERMINATE;
			}
			if ((pOperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_OPERATION) == PROCESS_VM_OPERATION)
			{
				pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_OPERATION;
			}
			if ((pOperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_READ) == PROCESS_VM_READ)
			{
				pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_READ;
			}
			if ((pOperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_WRITE) == PROCESS_VM_WRITE)
			{
				pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_WRITE;
			}
		}
	}
	return OB_PREOP_SUCCESS;
}

VOID KcaUnProtectProcess()
{
	if (g_RegistrationHandle != NULL)
	{
		ObUnRegisterCallbacks(g_RegistrationHandle);
		g_RegistrationHandle = NULL;
	}
}

NTSTATUS KcaProtectProcess(HANDLE ProtegeProcessId)
{
	OB_CALLBACK_REGISTRATION obReg;
	OB_OPERATION_REGISTRATION opReg;

	g_ProtegeProcessId = ProtegeProcessId;


	memset(&obReg, 0, sizeof(obReg));
	obReg.Version = ObGetFilterVersion();
	obReg.OperationRegistrationCount = 1;
	obReg.RegistrationContext = NULL;
	//RtlInitUnicodeString(&obReg.Altitude, L"321000");
	RtlInitUnicodeString(&obReg.Altitude, L"401902");

	memset(&opReg, 0, sizeof(opReg)); //初始化结构体变量

	//下面 请注意这个结构体的成员字段的设置
	opReg.ObjectType = PsProcessType;
	opReg.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;

	opReg.PreOperation = (POB_PRE_OPERATION_CALLBACK)&CallbackRegistration; //在这里注册一个回调函数指针

	obReg.OperationRegistration = &opReg; //注意这一条语句

	return ObRegisterCallbacks(&obReg, &g_RegistrationHandle); //在这里注册回调函数
}