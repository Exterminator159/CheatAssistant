#ifndef KCA_H
#define KCA_H
#include <ntdef.h>
#include <ntifs.h>
#include <ntddk.h>
//#include "C:\Program Files (x86)\Windows Kits\10\Include\10.0.17134.0\um\winnt.h"
#include "kca_api.h"
#define DEBUG
#ifdef DEBUG
#define dprintf(Format, ...) DbgPrint("KCA: " Format "\n", __VA_ARGS__)
#endif // DEBUG

#define MAX_STRING_LENGTH			512

typedef struct _TARGET_PROCESS_INFO
{
	PEPROCESS Process;
	HANDLE ProcessId;
	HANDLE ProcessHandle;
	PVOID ProcessBaseAddress;

	HANDLE MainThreadId;
	PETHREAD MainThread;
	HANDLE MainThreadHandle;

	BOOLEAN ProcessStatus;

}KCA_TARGET_PROCESS_INFO_STRUCT, *PKCA_TARGET_PROCESS_INFO_STRUCT;

extern KCA_TARGET_PROCESS_INFO_STRUCT g_TargetProcessInfo;

// system
NTSTATUS NTAPI MmCopyVirtualMemory
(
	PEPROCESS SourceProcess,
	CONST VOID * SourceAddress,
	PEPROCESS TargetProcess,
	PVOID TargetAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T ReturnSize
);

NTKERNELAPI PCHAR PsGetProcessImageFileName(
	PEPROCESS Process
);

NTKERNELAPI NTSTATUS PsReferenceProcessFilePointer(
	IN PEPROCESS Process,
	OUT PVOID *pFilePointer
);

NTKERNELAPI PVOID PsGetProcessSectionBaseAddress(
	__in PEPROCESS Process
);

//NTSTATUS NTAPI RtlRemoteCall(
//	IN HANDLE Process,
//	IN HANDLE Thread,
//	IN PVOID CallSite, //call 地址
//	IN ULONG ArgumentCount,// 参数数量
//	IN PULONG Arguments,//参数
//	IN BOOLEAN PassContext,
//	IN BOOLEAN AlreadySuspended
//);
//device_control
NTSTATUS KcaDispatchDeviceControl(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
);
// virtual_memory
NTSTATUS KcaReadVirtualMemory(
	PKCA_READ_VIRTUAL_MEMORY_STRUCT rvms
);

NTSTATUS KcaWriteVirtualMemory(
	PKCA_WRITE_VIRTUAL_MEMORY_STRUCT wvms
);

// utils
PCHAR GetProcessNameByProcessId(
	HANDLE hProcessId
);

BOOLEAN GetPathByFileObject(
	PFILE_OBJECT FileObject,
	WCHAR* wzPath
);
BOOLEAN GetProcessPathBySectionObject(
	HANDLE ulProcessID,
	WCHAR* wzProcessPath
);
// process
HANDLE KcaGetProcessHandle(
	PEPROCESS Process
);
VOID KcaUnProtectProcess();
NTSTATUS KcaProtectProcess(
	HANDLE ProtegeProcessId
);
// thread
HANDLE KcaGetThreadHandle(
	PETHREAD Thread
);

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE,MmCopyVirtualMemory)
#pragma alloc_text(PAGE,KcaDispatchDeviceControl)
#pragma alloc_text(PAGE,KcaReadVirtualMemory)
#pragma alloc_text(PAGE,KcaWriteVirtualMemory)
#endif

#endif // !KCA_H
