//#pragma once
//typedef unsigned short      WORD;
//typedef struct _KIDTENTRY
//{
//	WORD Offset;
//	WORD Selector;
//	WORD Access;
//	WORD ExtendedOffset;
//} KIDTENTRY, *PKIDTENTRY;
//typedef struct _KGDTENTRY
//{
//	WORD LimitLow;
//	WORD BaseLow;
//	ULONG HighWord;
//} KGDTENTRY, *PKGDTENTRY;
//typedef struct _KEXECUTE_OPTIONS
//{
//	ULONG ExecuteDisable : 1;
//	ULONG ExecuteEnable : 1;
//	ULONG DisableThunkEmulation : 1;
//	ULONG Permanent : 1;
//	ULONG ExecuteDispatchEnable : 1;
//	ULONG ImageDispatchEnable : 1;
//	ULONG Spare : 2;
//} KEXECUTE_OPTIONS, *PKEXECUTE_OPTIONS;
//typedef struct _KPROCESS
//{
//	DISPATCHER_HEADER Header;
//	LIST_ENTRY ProfileListHead;
//	ULONG DirectoryTableBase;
//	ULONG Unused0;
//	KGDTENTRY LdtDescriptor;
//	KIDTENTRY Int21Descriptor;
//	WORD IopmOffset;
//	UCHAR Iopl;
//	UCHAR Unused;
//	ULONG ActiveProcessors;
//	ULONG KernelTime;
//	ULONG UserTime;
//	LIST_ENTRY ReadyListHead;
//	SINGLE_LIST_ENTRY SwapListEntry;
//	PVOID VdmTrapcHandler;
//	LIST_ENTRY ThreadListHead;
//	ULONG ProcessLock;
//	ULONG Affinity;
//	union
//	{
//		ULONG AutoAlignment : 1;
//		ULONG DisableBoost : 1;
//		ULONG DisableQuantum : 1;
//		ULONG ReservedFlags : 29;
//		LONG ProcessFlags;
//	};
//	CHAR BasePriority;
//	CHAR QuantumReset;
//	UCHAR State;
//	UCHAR ThreadSeed;
//	UCHAR PowerState;
//	UCHAR IdealNode;
//	UCHAR Visited;
//	union
//	{
//		KEXECUTE_OPTIONS Flags;
//		UCHAR ExecuteOptions;
//	};
//	ULONG StackCount;
//	LIST_ENTRY ProcessListEntry;
//	UINT64 CycleTime;
//} KPROCESS, *PKPROCESS;
//typedef struct _HANDLE_TRACE_DB_ENTRY
//{
//	CLIENT_ID ClientId;
//	PVOID Handle;
//	ULONG Type;
//	VOID * StackTrace[16];
//} HANDLE_TRACE_DB_ENTRY, *PHANDLE_TRACE_DB_ENTRY;
//typedef struct _HANDLE_TRACE_DEBUG_INFO
//{
//	LONG RefCount;
//	ULONG TableSize;
//	ULONG BitMaskFlags;
//	FAST_MUTEX CloseCompactionLock;
//	ULONG CurrentStackIndex;
//	HANDLE_TRACE_DB_ENTRY TraceDb[1];
//} HANDLE_TRACE_DEBUG_INFO, *PHANDLE_TRACE_DEBUG_INFO;
//typedef struct _HANDLE_TABLE_ENTRY_INFO
//{
//	ULONG AuditMask;
//} HANDLE_TABLE_ENTRY_INFO, *PHANDLE_TABLE_ENTRY_INFO;
//typedef struct _HANDLE_TABLE_ENTRY
//{
//	union
//	{
//		PVOID Object;
//		ULONG ObAttributes;
//		PHANDLE_TABLE_ENTRY_INFO InfoTable;
//		ULONG Value;
//	};
//	union
//	{
//		ULONG GrantedAccess;
//		struct
//		{
//			WORD GrantedAccessIndex;
//			WORD CreatorBackTraceIndex;
//		};
//		LONG NextFreeTableEntry;
//	};
//} HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY;
//typedef struct _HANDLE_TABLE
//{
//	ULONG TableCode;
//	PEPROCESS QuotaProcess;
//	PVOID UniqueProcessId;
//	EX_PUSH_LOCK HandleLock;
//	LIST_ENTRY HandleTableList;
//	EX_PUSH_LOCK HandleContentionEvent;
//	PHANDLE_TRACE_DEBUG_INFO DebugInfo;
//	LONG ExtraInfoPages;
//	ULONG Flags;
//	ULONG StrictFIFO : 1;
//	LONG FirstFreeHandle;
//	PHANDLE_TABLE_ENTRY LastFreeHandleEntry;
//	LONG HandleCount;
//	ULONG NextHandleNeedingPool;
//} HANDLE_TABLE, *PHANDLE_TABLE;
//typedef struct _EX_FAST_REF
//{
//	union
//	{
//		PVOID Object;
//		ULONG RefCnt : 3;
//		ULONG Value;
//	};
//} EX_FAST_REF, *PEX_FAST_REF;
//typedef struct _MMADDRESS_NODE
//{
//	ULONG u1;
//	PMMADDRESS_NODE LeftChild;
//	PMMADDRESS_NODE RightChild;
//	ULONG StartingVpn;
//	ULONG EndingVpn;
//} MMADDRESS_NODE, *PMMADDRESS_NODE;
//typedef struct _MM_AVL_TABLE
//{
//	MMADDRESS_NODE BalancedRoot;
//	ULONG DepthOfTree : 5;
//	ULONG Unused : 3;
//	ULONG NumberGenericTableElements : 24;
//	PVOID NodeHint;
//	PVOID NodeFreeHint;
//} MM_AVL_TABLE, *PMM_AVL_TABLE;
//typedef struct _HARDWARE_PTE
//{
//	union
//	{
//		ULONG Valid : 1;
//		ULONG Write : 1;
//		ULONG Owner : 1;
//		ULONG WriteThrough : 1;
//		ULONG CacheDisable : 1;
//		ULONG Accessed : 1;
//		ULONG Dirty : 1;
//		ULONG LargePage : 1;
//		ULONG Global : 1;
//		ULONG CopyOnWrite : 1;
//		ULONG Prototype : 1;
//		ULONG reserved0 : 1;
//		ULONG PageFrameNumber : 26;
//		ULONG reserved1 : 26;
//		ULONG LowPart;
//	};
//	ULONG HighPart;
//} HARDWARE_PTE, *PHARDWARE_PTE;
//typedef struct _SE_AUDIT_PROCESS_CREATION_INFO
//{
//	POBJECT_NAME_INFORMATION ImageFileName;
//} SE_AUDIT_PROCESS_CREATION_INFO, *PSE_AUDIT_PROCESS_CREATION_INFO;
//typedef struct _MMSUPPORT_FLAGS
//{
//	ULONG SessionSpace : 1;
//	ULONG ModwriterAttached : 1;
//	ULONG TrimHard : 1;
//	ULONG MaximumWorkingSetHard : 1;
//	ULONG ForceTrim : 1;
//	ULONG MinimumWorkingSetHard : 1;
//	ULONG SessionMaster : 1;
//	ULONG TrimmerAttached : 1;
//	ULONG TrimmerDetaching : 1;
//	ULONG Reserved : 7;
//	ULONG MemoryPriority : 8;
//	ULONG WsleDeleted : 1;
//	ULONG VmExiting : 1;
//	ULONG Available : 6;
//} MMSUPPORT_FLAGS, *PMMSUPPORT_FLAGS;
//typedef struct _MMWSLE
//{
//	ULONG u1;
//} MMWSLE, *PMMWSLE;
//typedef struct _MMWSLE_HASH
//{
//	ULONG Index;
//} MMWSLE_HASH, *PMMWSLE_HASH;
//typedef struct _MMWSLE_NONDIRECT_HASH
//{
//	PVOID Key;
//	ULONG Index;
//} MMWSLE_NONDIRECT_HASH, *PMMWSLE_NONDIRECT_HASH;
//typedef struct _MMWSL
//{
//	ULONG FirstFree;
//	ULONG FirstDynamic;
//	ULONG LastEntry;
//	ULONG NextSlot;
//	PMMWSLE Wsle;
//	PVOID LowestPagableAddress;
//	ULONG LastInitializedWsle;
//	ULONG NextEstimationSlot;
//	ULONG NextAgingSlot;
//	ULONG EstimatedAvailable;
//	ULONG GrowthSinceLastEstimate;
//	ULONG NumberOfCommittedPageTables;
//	ULONG VadBitMapHint;
//	ULONG NonDirectCount;
//	PMMWSLE_NONDIRECT_HASH NonDirectHash;
//	PMMWSLE_HASH HashTableStart;
//	PMMWSLE_HASH HighestPermittedHashAddress;
//	PVOID HighestUserAddress;
//	WORD UsedPageTableEntries[1536];
//	ULONG CommittedPageTables[48];
//} MMWSL, *PMMWSL;
//typedef struct _MMSUPPORT
//{
//	LIST_ENTRY WorkingSetExpansionLinks;
//	WORD LastTrimStamp;
//	WORD NextPageColor;
//	MMSUPPORT_FLAGS Flags;
//	ULONG PageFaultCount;
//	ULONG PeakWorkingSetSize;
//	ULONG Spare0;
//	ULONG MinimumWorkingSetSize;
//	ULONG MaximumWorkingSetSize;
//	PMMWSL VmWorkingSetList;
//	ULONG Claim;
//	ULONG Spare[1];
//	ULONG WorkingSetPrivateSize;
//	ULONG WorkingSetSizeOverhead;
//	ULONG WorkingSetSize;
//	PKEVENT ExitEvent;
//	EX_PUSH_LOCK WorkingSetMutex;
//	PVOID AccessLog;
//} MMSUPPORT, *PMMSUPPORT;
//typedef struct _ALPC_PROCESS_CONTEXT
//{
//	EX_PUSH_LOCK Lock;
//	LIST_ENTRY ViewListHead;
//	ULONG PagedPoolQuotaCache;
//} ALPC_PROCESS_CONTEXT, *PALPC_PROCESS_CONTEXT;
//typedef struct _PAGEFAULT_HISTORY
//{
//	ULONG CurrentIndex;
//	ULONG MapIndex;
//	KSPIN_LOCK SpinLock;
//	PVOID Reserved;
//	PROCESS_WS_WATCH_INFORMATION WatchInfo[1];
//} PAGEFAULT_HISTORY, *PPAGEFAULT_HISTORY;
//typedef struct _EPROCESS_QUOTA_BLOCK
//{
//	struct _EPROCESS_QUOTA_ENTRY QuotaEntry[3];
//	struct _LIST_ENTRY QuotaList;
//	ULONG32 ReferenceCount;
//	ULONG32 ProcessCount;
//}EPROCESS_QUOTA_BLOCK, *PEPROCESS_QUOTA_BLOCK;
//typedef struct _EPROCESS
//{
//	KPROCESS Pcb;
//	EX_PUSH_LOCK ProcessLock;
//	LARGE_INTEGER CreateTime;
//	LARGE_INTEGER ExitTime;
//	EX_RUNDOWN_REF RundownProtect;
//	PVOID UniqueProcessId;
//	LIST_ENTRY ActiveProcessLinks;
//	ULONG QuotaUsage[3];
//	ULONG QuotaPeak[3];
//	ULONG CommitCharge;
//	ULONG PeakVirtualSize;
//	ULONG VirtualSize;
//	LIST_ENTRY SessionProcessLinks;
//	PVOID DebugPort;
//	union
//	{
//		PVOID ExceptionPortData;
//		ULONG ExceptionPortValue;
//		ULONG ExceptionPortState : 3;
//	};
//	PHANDLE_TABLE ObjectTable;
//	EX_FAST_REF Token;
//	ULONG WorkingSetPage;
//	EX_PUSH_LOCK AddressCreationLock;
//	PETHREAD RotateInProgress;
//	PETHREAD ForkInProgress;
//	ULONG HardwareTrigger;
//	PMM_AVL_TABLE PhysicalVadRoot;
//	PVOID CloneRoot;
//	ULONG NumberOfPrivatePages;
//	ULONG NumberOfLockedPages;
//	PVOID Win32Process;
//	PEJOB Job;
//	PVOID SectionObject;
//	PVOID SectionBaseAddress;
//	PAGEFAULT_HISTORY * QuotaBlock;
//	EPROCESS_QUOTA_BLOCK * WorkingSetWatch;
//	PVOID Win32WindowStation;
//	PVOID InheritedFromUniqueProcessId;
//	PVOID LdtInformation;
//	PVOID VadFreeHint;
//	PVOID VdmObjects;
//	PVOID DeviceMap;
//	PVOID EtwDataSource;
//	PVOID FreeTebHint;
//	union
//	{
//		HARDWARE_PTE PageDirectoryPte;
//		UINT64 Filler;
//	};
//	PVOID Session;
//	UCHAR ImageFileName[16];
//	LIST_ENTRY JobLinks;
//	PVOID LockedPagesList;
//	LIST_ENTRY ThreadListHead;
//	PVOID SecurityPort;
//	PVOID PaeTop;
//	ULONG ActiveThreads;
//	ULONG ImagePathHash;
//	ULONG DefaultHardErrorProcessing;
//	LONG LastThreadExitStatus;
//	PPEB Peb;
//	EX_FAST_REF PrefetchTrace;
//	LARGE_INTEGER ReadOperationCount;
//	LARGE_INTEGER WriteOperationCount;
//	LARGE_INTEGER OtherOperationCount;
//	LARGE_INTEGER ReadTransferCount;
//	LARGE_INTEGER WriteTransferCount;
//	LARGE_INTEGER OtherTransferCount;
//	ULONG CommitChargeLimit;
//	ULONG CommitChargePeak;
//	PVOID AweInfo;
//	SE_AUDIT_PROCESS_CREATION_INFO SeAuditProcessCreationInfo;
//	MMSUPPORT Vm;
//	LIST_ENTRY MmProcessLinks;
//	ULONG ModifiedPageCount;
//	ULONG Flags2;
//	ULONG JobNotReallyActive : 1;
//	ULONG AccountingFolded : 1;
//	ULONG NewProcessReported : 1;
//	ULONG ExitProcessReported : 1;
//	ULONG ReportCommitChanges : 1;
//	ULONG LastReportMemory : 1;
//	ULONG ReportPhysicalPageChanges : 1;
//	ULONG HandleTableRundown : 1;
//	ULONG NeedsHandleRundown : 1;
//	ULONG RefTraceEnabled : 1;
//	ULONG NumaAware : 1;
//	ULONG ProtectedProcess : 1;
//	ULONG DefaultPagePriority : 3;
//	ULONG PrimaryTokenFrozen : 1;
//	ULONG ProcessVerifierTarget : 1;
//	ULONG StackRandomizationDisabled : 1;
//	ULONG Flags;
//	ULONG CreateReported : 1;
//	ULONG NoDebugInherit : 1;
//	ULONG ProcessExiting : 1;
//	ULONG ProcessDelete : 1;
//	ULONG Wow64SplitPages : 1;
//	ULONG VmDeleted : 1;
//	ULONG OutswapEnabled : 1;
//	ULONG Outswapped : 1;
//	ULONG ForkFailed : 1;
//	ULONG Wow64VaSpace4Gb : 1;
//	ULONG AddressSpaceInitialized : 2;
//	ULONG SetTimerResolution : 1;
//	ULONG BreakOnTermination : 1;
//	ULONG DeprioritizeViews : 1;
//	ULONG WriteWatch : 1;
//	ULONG ProcessInSession : 1;
//	ULONG OverrideAddressSpace : 1;
//	ULONG HasAddressSpace : 1;
//	ULONG LaunchPrefetched : 1;
//	ULONG InjectInpageErrors : 1;
//	ULONG VmTopDown : 1;
//	ULONG ImageNotifyDone : 1;
//	ULONG PdeUpdateNeeded : 1;
//	ULONG VdmAllowed : 1;
//	ULONG SmapAllowed : 1;
//	ULONG ProcessInserted : 1;
//	ULONG DefaultIoPriority : 3;
//	ULONG SparePsFlags1 : 2;
//	LONG ExitStatus;
//	WORD Spare7;
//	union
//	{
//		struct
//		{
//			UCHAR SubSystemMinorVersion;
//			UCHAR SubSystemMajorVersion;
//		};
//		WORD SubSystemVersion;
//	};
//	UCHAR PriorityClass;
//	MM_AVL_TABLE VadRoot;
//	ULONG Cookie;
//	ALPC_PROCESS_CONTEXT AlpcContext;
//} EPROCESS, *PEPROCESS;


typedef struct _LDR_DATA_TABLE_ENTRY64
{
	LIST_ENTRY64    InLoadOrderLinks;
	LIST_ENTRY64    InMemoryOrderLinks;
	LIST_ENTRY64    InInitializationOrderLinks;
	PVOID            DllBase;
	PVOID            EntryPoint;
	ULONG            SizeOfImage;
	UNICODE_STRING    FullDllName;
	UNICODE_STRING     BaseDllName;
	ULONG            Flags;
	USHORT            LoadCount;
	USHORT            TlsIndex;
	PVOID            SectionPointer;
	ULONG            CheckSum;
	PVOID            LoadedImports;
	PVOID            EntryPointActivationContext;
	PVOID            PatchInformation;
	LIST_ENTRY64    ForwarderLinks;
	LIST_ENTRY64    ServiceTagLinks;
	LIST_ENTRY64    StaticLinks;
	PVOID            ContextInformation;
	ULONG64            OriginalBase;
	LARGE_INTEGER    LoadTime;
} LDR_DATA_TABLE_ENTRY64, *PLDR_DATA_TABLE_ENTRY64;

typedef struct _OBJECT_TYPE_INITIALIZER
{
	UINT16       Length;
	union
	{
		UINT8        ObjectTypeFlags;
		struct
		{
			UINT8        CaseInsensitive : 1;
			UINT8        UnnamedObjectsOnly : 1;
			UINT8        UseDefaultObject : 1;
			UINT8        SecurityRequired : 1;
			UINT8        MaintainHandleCount : 1;
			UINT8        MaintainTypeList : 1;
			UINT8        SupportsObjectCallbacks : 1;
		};
	};
	ULONG32      ObjectTypeCode;
	ULONG32      InvalidAttributes;
	struct _GENERIC_MAPPING GenericMapping;
	ULONG32      ValidAccessMask;
	ULONG32      RetainAccess;
	enum _POOL_TYPE PoolType;
	ULONG32      DefaultPagedPoolCharge;
	ULONG32      DefaultNonPagedPoolCharge;
	PVOID        DumpProcedure;
	PVOID        OpenProcedure;
	PVOID         CloseProcedure;
	PVOID         DeleteProcedure;
	PVOID         ParseProcedure;
	PVOID        SecurityProcedure;
	PVOID         QueryNameProcedure;
	PVOID         OkayToCloseProcedure;
}OBJECT_TYPE_INITIALIZER, *POBJECT_TYPE_INITIALIZER;

typedef struct _OBJECT_TYPE_TEMP
{
	struct _LIST_ENTRY TypeList;
	struct _UNICODE_STRING Name;
	VOID*        DefaultObject;
	UINT8        Index;
	UINT8        _PADDING0_[0x3];
	ULONG32      TotalNumberOfObjects;
	ULONG32      TotalNumberOfHandles;
	ULONG32      HighWaterNumberOfObjects;
	ULONG32      HighWaterNumberOfHandles;
	UINT8        _PADDING1_[0x4];
	struct _OBJECT_TYPE_INITIALIZER TypeInfo;
	ULONG64 TypeLock;
	ULONG32      Key;
	UINT8        _PADDING2_[0x4];
	struct _LIST_ENTRY CallbackList;
}OBJECT_TYPE_TEMP, *POBJECT_TYPE_TEMP;