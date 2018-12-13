#include "kca.h"

KCA_TARGET_PROCESS_INFO_STRUCT g_TargetProcessInfo;
UNICODE_STRING SymbolicLinkName;

VOID CreateProcessNotifyEx(
	_Inout_  PEPROCESS              Process,
	_In_     HANDLE                 ProcessId,
	_In_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo
) {
	if (NULL != CreateInfo)
	{
		//dprintf("CreateInfo->ImageFileName->Buffer->:%ls", CreateInfo->ImageFileName->Buffer);
		if (wcsstr(CreateInfo->ImageFileName->Buffer, L"dnf.exe"))
		{
			g_TargetProcessInfo.ProcessStatus = TRUE;
			g_TargetProcessInfo.ProcessId = ProcessId;
			g_TargetProcessInfo.Process = Process;
			//dprintf("�����Ѿ�����");
		}
	}
	else {
		if (ProcessId == g_TargetProcessInfo.ProcessId)
		{
			g_TargetProcessInfo.ProcessHandle = NULL;
			g_TargetProcessInfo.MainThreadHandle = NULL;
			g_TargetProcessInfo.ProcessStatus = FALSE;
			//dprintf("�����Ѿ��˳�");
		}
	}
	
}


VOID NotifyImageLoadCallback(
	_In_opt_ PUNICODE_STRING FullImageName,
	_In_ HANDLE ProcessId,                // pid into which image is being mapped
	_In_ PIMAGE_INFO ImageInfo
)
{
	if (wcsstr(FullImageName->Buffer, TARGET_PROCESS_NAME) && wcsstr(FullImageName->Buffer, L"Device"))
	{
		//dprintf("FullImageName->Buffer->:%ls", FullImageName->Buffer);
		g_TargetProcessInfo.MainThreadId = PsGetCurrentThreadId();
		g_TargetProcessInfo.MainThread = PsGetCurrentThread();
		g_TargetProcessInfo.ProcessBaseAddress = ImageInfo->ImageBase;
	}
}

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
	if (!NT_SUCCESS(PsRemoveLoadImageNotifyRoutine(NotifyImageLoadCallback)))
	{
#ifdef DEBUG
		dprintf("Delete NotifyImageLoadCallback Failure");
#endif // DEBUG
	}
	// ɾ���������̻ص�
	if (!NT_SUCCESS(PsSetCreateProcessNotifyRoutineEx(CreateProcessNotifyEx, TRUE))) {
#ifdef DEBUG
		dprintf("Delete CreateProcessNotifyRoutineEx Failure");
#endif // DEBUG
	}
	// ɾ����������
	if (!NT_SUCCESS(IoDeleteSymbolicLink(&SymbolicLinkName)))
	{
#ifdef DEBUG
		dprintf("Delete SymbolicLinkName Failure");
#endif // DEBUG
	}
	// ɾ���豸
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
	// ���������豸
	RtlInitUnicodeString(&DeviceName, DEVICE_NAME);
	Status = IoCreateDevice(DriverObject, 0, &DeviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &DeviceObject);
	if (!NT_SUCCESS(Status))
	{
#ifdef DEBUG
		dprintf("Create DeviceObject Failure");
#endif // DEBUG
		return Status;
	}
	// �����豸�ķ�������
	RtlInitUnicodeString(&SymbolicLinkName, SYMBOLIC_LINK_NAME);
	Status = IoCreateSymbolicLink(&SymbolicLinkName, &DeviceName);
	if (!NT_SUCCESS(Status))
	{
#ifdef DEBUG
		dprintf("Create SymbolicLink Failure");
#endif // DEBUG
		IoDeleteDevice(DeviceObject);
		return Status;
	}

	// ����Irp����
	for (size_t i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		DriverObject->MajorFunction[i] = DefaultDispatchFunction;
	}
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = KcaDispatchDeviceControl;
	DriverObject->DriverUnload = DriverUnload;

	DriverObject->Flags |= DO_BUFFERED_IO;
	DeviceObject->Flags &= (~DO_DEVICE_INITIALIZING);

	// �������̻ص�
	*(PULONG)((PCHAR)DriverObject->DriverSection + 13 * sizeof(void*)) |= 0x20;//��������ò����������
	Status = PsSetCreateProcessNotifyRoutineEx(CreateProcessNotifyEx, FALSE);
	if (!NT_SUCCESS(Status))
	{
		IoDeleteSymbolicLink(&SymbolicLinkName);
		IoDeleteDevice(DeviceObject);
#ifdef DEBUG
		dprintf("Failed to call PsSetCreateProcessNotifyRoutineEx, error code = 0x%08X", Status);
#endif // DEBUG
	}

	// �������֪ͨ�ص�����
	Status = PsSetLoadImageNotifyRoutine(NotifyImageLoadCallback);
	if (!NT_SUCCESS(Status))
	{
#ifdef DEBUG
		dprintf("Create LoadImageNotifyRoutine Failure");
#endif // DEBUG
		IoDeleteSymbolicLink(&SymbolicLinkName);
		IoDeleteDevice(DeviceObject);
	}
#ifdef DEBUG
	dprintf("Loader Success!");
#endif // DEBUG
	return Status;
}