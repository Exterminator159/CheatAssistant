#include "kca.h"

//HANDLE TargetProcessId = 0;
//PVOID TargetProcessBaseAddress = NULL;
//PEPROCESS TargetProcess;

TARGET_PROCESS_INFO g_TargetProcessInfo;

UNICODE_STRING SymbolicLinkName;
KEVENT Event;
KSPIN_LOCK Lock;
LIST_ENTRY ListHead;

//VOID NotifyImageLoadCallback(
//	_In_opt_ PUNICODE_STRING FullImageName,
//	_In_ HANDLE ProcessId,                // pid into which image is being mapped
//	_In_ PIMAGE_INFO ImageInfo
//)
//{
//	if (wcsstr(FullImageName->Buffer, TARGET_PROCESS_NAME) && wcsstr(FullImageName->Buffer, L"Device"))
//	{
//		dprintf("TargetName %ls\n", FullImageName->Buffer);
//		dprintf("TargetProcessId %d\n", ProcessId);
//		dprintf("TargetImageBase %x\n", ImageInfo->ImageBase);
//		TargetProcessId = ProcessId;
//		TargetProcessBaseAddress = ImageInfo->ImageBase;
//	}
//}

VOID CreateProcessNotifyEx(
	_Inout_  PEPROCESS              Process,
	_In_     HANDLE                 ProcessId,
	_In_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo
) {
	if (NULL != CreateInfo)
	{
		g_TargetProcessInfo.Process = Process;
		g_TargetProcessInfo.ProcessId = ProcessId;
		g_TargetProcessInfo.CreateInfo = CreateInfo;
		dprintf("进程加载 ProcessId->:%d", ProcessId);
	}
	else {
		dprintf("进程退出 ProcessId->:%d", ProcessId);
	}
}

//VOID CreateProcessNotify(
//	IN HANDLE   ParentId,
//	IN HANDLE   ProcessId,
//	IN BOOLEAN  Create
//) {
//	WCHAR			wzParentProcessPath[512] = { 0 };
//	WCHAR			wzProcessPath[512] = { 0 };
//	UNICODE_STRING	usProcessParameters;
//
//	GetProcessPathBySectionObject(ParentId, wzParentProcessPath);
//	GetProcessPathBySectionObject(ProcessId, wzProcessPath);
//
//	if (Create)
//	{
//		dprintf("[CreateProcessNotify] [%04ld] %ws 创建进程：[%04ld] %ws",
//			ParentId, wzParentProcessPath, ProcessId, wzProcessPath);
//	}
//	else
//	{
//		dprintf("ExitProcess begin ----------------------");
//		dprintf("ProcessId: %ld", ProcessId);
//		dprintf("ProcessName: %s", GetProcessNameByProcessId(ProcessId));
//		dprintf("ProcessPath: %ws", wzProcessPath);
//		dprintf("ParentProcessId: %ld", ParentId);
//		dprintf("ParentProcessPath: %ws", wzParentProcessPath);
//		dprintf("ExitProcess end ----------------------");
//		dprintf("[CreateProcessNotify] [%04ld] %ws 进程退出，父进程：[%04ld] %ws",
//			ProcessId, wzProcessPath, ParentId, wzParentProcessPath);
//	}
//}

NTSTATUS DefaultDispatchFunction(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
)
{
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

VOID DriverUnload(
	_In_ PDRIVER_OBJECT DriverObject
)
{
	PsSetCreateProcessNotifyRoutineEx(CreateProcessNotifyEx, TRUE);
	//PsSetCreateProcessNotifyRoutine(CreateProcessNotify, TRUE);
	/*if (!NT_SUCCESS(PsRemoveLoadImageNotifyRoutine(NotifyImageLoadCallback)))
	{
		dprintf("Delete NotifyImageLoadCallback Failure");
	}*/
	if (!NT_SUCCESS(IoDeleteSymbolicLink(&SymbolicLinkName)))
	{
		dprintf("Delete SymbolicLinkName Failure");
	}
	IoDeleteDevice(DriverObject->DeviceObject);
}

NTSTATUS DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath
)
{
	NTSTATUS Status = STATUS_SUCCESS;
	PDEVICE_OBJECT DeviceObject;
	UNICODE_STRING DeviceName;
	// 创建虚拟设备
	RtlInitUnicodeString(&DeviceName, DEVICE_NAME);
	Status = IoCreateDevice(DriverObject, 0, &DeviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &DeviceObject);
	if (!NT_SUCCESS(Status))
	{
		dprintf("Create DeviceObject Failure");
		return Status;
	}
	// 创建设备的符号链接
	RtlInitUnicodeString(&SymbolicLinkName, SYMBOLIC_LINK_NAME);
	Status = IoCreateSymbolicLink(&SymbolicLinkName, &DeviceName);
	if (!NT_SUCCESS(Status))
	{
		dprintf("Create SymbolicLink Failure");
		IoDeleteDevice(DeviceObject);
		return Status;
	}

	// 处理Irp请求
	for (size_t i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		DriverObject->MajorFunction[i] = DefaultDispatchFunction;
	}
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = KcaDispatchDeviceControl;
	DriverObject->DriverUnload = DriverUnload;

	DriverObject->Flags |= DO_BUFFERED_IO;
	DeviceObject->Flags &= (~DO_DEVICE_INITIALIZING);
	//// 镜像加载通知回调函数
	//Status = PsSetLoadImageNotifyRoutine(NotifyImageLoadCallback);
	//if (!NT_SUCCESS(Status))
	//{
	//	dprintf("Create LoadImageNotifyRoutine Failure");
	//	IoDeleteSymbolicLink(&SymbolicLinkName);
	//	IoDeleteDevice(DeviceObject);
	//}
	// 创建进程回调
	Status = PsSetCreateProcessNotifyRoutineEx(CreateProcessNotifyEx, FALSE);
	if (!NT_SUCCESS(Status))
	{
		IoDeleteSymbolicLink(&SymbolicLinkName);
		IoDeleteDevice(DeviceObject);
		dprintf("Failed to call PsSetCreateProcessNotifyRoutineEx, error code = 0x%08X", Status);
	}
	/*Status = PsSetCreateProcessNotifyRoutine(CreateProcessNotify, FALSE);
	if (!NT_SUCCESS(Status))
	{
		IoDeleteSymbolicLink(&SymbolicLinkName);
		IoDeleteDevice(DeviceObject);
		dprintf("Failed to call PsSetCreateProcessNotifyRoutine, error code = 0x%08X", Status);
	}*/

	// 初始化事件、锁、链表头

	KeInitializeEvent(&Event, SynchronizationEvent, TRUE);
	KeInitializeSpinLock(&Lock);
	InitializeListHead(&ListHead);
	return Status;
}