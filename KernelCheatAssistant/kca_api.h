#ifndef KCA_API_H
#define KCA_API_H
//#define TARGET_PROCESS_NAME "DNF.exe"
#define TARGET_PROCESS_NAME L"YoudaoDict.exe"
#define DEVICE_SHOST_NAME L"kca"
#define DEVICE_NAME (L"\\Device\\" DEVICE_SHOST_NAME)
#define SYMBOLIC_LINK_SHORT_NAME L"kca"
#define SYMBOLIC_LINK_NAME (L"\\DosDevices\\" SYMBOLIC_LINK_SHORT_NAME)


#define KCTL_CODE(x) CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800 + x, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

#define KCA_READ_VIRTUAL_MEMORY KCTL_CODE(1)
#define KCA_WRITE_VIRTUAL_MEMORY KCTL_CODE(2)
#define KCA_GET_PROCESS_ID KCTL_CODE(3)
#define KCA_GET_PROCESS_HANDLE KCTL_CODE(4)
#define KCA_GET_THREAD_HANDLE KCTL_CODE(5)

typedef struct _KCA_REMOTE_CALL_STRUCT {
	IN HANDLE Process;
	IN HANDLE Thread;
	IN PVOID CallSite; //call 地址
	IN ULONG ArgumentCount;// 参数数量
	IN PULONG Arguments;//参数
	IN BOOLEAN PassContext;
	IN BOOLEAN AlreadySuspended;
}KCA_REMOTE_CALL_STRUCT,*PKCA_REMOTE_CALL_STRUCT;

typedef struct _READ_VIRTUAL_MEMORY_STRUCT
{
	ULONG Address;
	PVOID Response;
	SIZE_T Size;

}KCA_READ_VIRTUAL_MEMORY_STRUCT, *PKCA_READ_VIRTUAL_MEMORY_STRUCT;

typedef struct _WRITE_VIRTUAL_MEMORY_STRUCT
{
	ULONG Address;
	PVOID Value;
	SIZE_T Size;

}KCA_WRITE_VIRTUAL_MEMORY_STRUCT, *PKCA_WRITE_VIRTUAL_MEMORY_STRUCT;

#endif // !KCA_API_H





