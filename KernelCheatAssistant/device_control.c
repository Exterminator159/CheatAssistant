#include "kca.h"

NTSTATUS KcaDispatchDeviceControl(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
)
{
	NTSTATUS Status = STATUS_SUCCESS;
	PIO_STACK_LOCATION Stack;
	PKCA_READ_VIRTUAL_MEMORY_STRUCT rvms;
	PKCA_WRITE_VIRTUAL_MEMORY_STRUCT wvms;
	PKCA_REMOTE_CALL_STRUCT rcs;

	//得到当前堆栈
	Stack = IoGetCurrentIrpStackLocation(Irp);

	if (Stack)
	{
		switch (Stack->Parameters.DeviceIoControl.IoControlCode)
		{
		case KCA_READ_VIRTUAL_MEMORY:
		{
			rvms = (PKCA_READ_VIRTUAL_MEMORY_STRUCT)Irp->AssociatedIrp.SystemBuffer;
			if (rvms)
			{
				Status = KcaReadVirtualMemory(rvms);
			}
			Irp->IoStatus.Information = sizeof(KCA_READ_VIRTUAL_MEMORY_STRUCT);
		}
		break;
		case KCA_WRITE_VIRTUAL_MEMORY:
		{
			wvms = (PKCA_WRITE_VIRTUAL_MEMORY_STRUCT)Irp->AssociatedIrp.SystemBuffer;
			if (wvms)
			{
				Status = KcaWriteVirtualMemory(wvms);
			}
			Irp->IoStatus.Information = sizeof(KCA_WRITE_VIRTUAL_MEMORY_STRUCT);
		}
		break;
		case KCA_GET_PROCESS_ID:
		{
			if (g_TargetProcessInfo.ProcessStatus == TRUE)
			{
				*(ULONG*)Irp->AssociatedIrp.SystemBuffer = (ULONG)(ULONG_PTR)g_TargetProcessInfo.ProcessId;
			}
			Irp->IoStatus.Information = sizeof(ULONG);
		}
		break;
		case KCA_GET_PROCESS_HANDLE:
		{
			if (g_TargetProcessInfo.ProcessStatus == TRUE) {
				*(HANDLE*)Irp->AssociatedIrp.SystemBuffer = KcaGetProcessHandle(g_TargetProcessInfo.Process);
			}
			Irp->IoStatus.Information = sizeof(HANDLE);
		}
		break;
		case KCA_GET_THREAD_HANDLE:
		{
			if (g_TargetProcessInfo.ProcessStatus == TRUE) {
				*(HANDLE*)Irp->AssociatedIrp.SystemBuffer = KcaGetThreadHandle(g_TargetProcessInfo.MainThread);
			}
			Irp->IoStatus.Information = sizeof(HANDLE);
		}
		break; 
		case KCA_PROTECT_CURRENT_PROCESS:
		{
			dprintf("保护");
			KcaProtectProcess(PsGetCurrentProcessId());
			Irp->IoStatus.Information = 0;
		}
		break; 
		default:
			Status = STATUS_INVALID_DEVICE_REQUEST;
			break;
		}

	}
	else {
		Status = STATUS_NOT_SUPPORTED;
	}
	Irp->IoStatus.Status = Status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return Status;
}