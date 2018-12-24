#include "kca.h"
//
//
//
//HANDLE g_ProtegeProcessId = NULL;
//PVOID g_RegistrationHandle = NULL;//定义一个void*类型的变量，它将会作为ObRegisterCallbacks函数的第2个参数。
//
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
//
//
//OB_PREOP_CALLBACK_STATUS CallbackRegistration(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION pOperationInformation)
//{
//	HANDLE pid = PsGetProcessId((PEPROCESS)pOperationInformation->Object);
//	UNREFERENCED_PARAMETER(RegistrationContext);
//	if (pOperationInformation->ObjectType == *PsProcessType && pid == g_ProtegeProcessId)
//	{
//		if (pOperationInformation->Operation == OB_OPERATION_HANDLE_CREATE || pOperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
//		{
//			if ((pOperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_TERMINATE) == PROCESS_TERMINATE)
//			{
//				pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_TERMINATE;
//			}
//			if ((pOperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_OPERATION) == PROCESS_VM_OPERATION)
//			{
//				pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_OPERATION;
//			}
//			if ((pOperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_READ) == PROCESS_VM_READ)
//			{
//				pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_READ;
//			}
//			if ((pOperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_WRITE) == PROCESS_VM_WRITE)
//			{
//				pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_WRITE;
//			}
//		}
//		//if (pOperationInformation->Operation == OB_OPERATION_HANDLE_CREATE)
//		//{
//		//	//create handle			
//
//		//	ACCESS_MASK da = pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess;
//
//		//	//DbgPrint("PID %d(%p) opened a handle to the CE process(%p) with access mask %x", PsGetCurrentProcessId(), PsGetCurrentProcess(), DRMProcess, da);
//
//		//	da = da & (PROCESS_TERMINATE | PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_SUSPEND_RESUME);
//
//		//	//da = da & PROCESS_SUSPEND_RESUME;
//
//		//	pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess = 0;// da;
//		//}
//		//else if (pOperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
//		//{
//		//	//duplicate handle
//		//	ACCESS_MASK da = pOperationInformation->Parameters->DuplicateHandleInformation.DesiredAccess;
//
//		//	//DbgPrint("PID %d(%p) opened a handle to the CE process(%p) with access mask %x", PsGetCurrentProcessId(), PsGetCurrentProcess(), DRMProcess, da);
//
//
//		//	da = da & (PROCESS_TERMINATE | PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_SUSPEND_RESUME);
//
//		//	//da = da & PROCESS_SUSPEND_RESUME;
//
//		//	pOperationInformation->Parameters->DuplicateHandleInformation.DesiredAccess = 0;// da;
//		//}
//
//		
//	}
//	return OB_PREOP_SUCCESS;
//}
//
//VOID KcaUnProtectProcess()
//{
//	if (g_RegistrationHandle != NULL)
//	{
//		ObUnRegisterCallbacks(g_RegistrationHandle);
//		g_RegistrationHandle = NULL;
//	}
//}
//
//NTSTATUS KcaProtectProcess(HANDLE ProtegeProcessId)
//{
//	OB_CALLBACK_REGISTRATION obReg;
//	OB_OPERATION_REGISTRATION opReg;
//
//	g_ProtegeProcessId = ProtegeProcessId;
//
//
//	memset(&obReg, 0, sizeof(obReg));
//	obReg.Version = ObGetFilterVersion();
//	obReg.OperationRegistrationCount = 1;
//	obReg.RegistrationContext = NULL;
//	//RtlInitUnicodeString(&obReg.Altitude, L"321000");
//	RtlInitUnicodeString(&obReg.Altitude, L"401900");
//
//	memset(&opReg, 0, sizeof(opReg)); //初始化结构体变量
//
//	//下面 请注意这个结构体的成员字段的设置
//	opReg.ObjectType = PsProcessType;
//	opReg.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;
//
//	opReg.PreOperation = (POB_PRE_OPERATION_CALLBACK)&CallbackRegistration; //在这里注册一个回调函数指针
//
//	obReg.OperationRegistration = &opReg; //注意这一条语句
//
//	return ObRegisterCallbacks(&obReg, &g_RegistrationHandle); //在这里注册回调函数
//}