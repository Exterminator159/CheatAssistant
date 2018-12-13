#include <windows.h>
#include "../KernelCheatAssistant/kca_api.h"
class Kca
{
private:
	HANDLE hDriver = NULL;
public:
	Kca();
	~Kca();
	DWORD dwProcessId;
	//DWORD dwProcessBaseAddress;
	void Init();
	void closeHandle();
	DWORD getProcessId();
	HANDLE getProcessHandle();
	//DWORD getProcessBaseAddress();
	BOOL readVirtualMemory(ULONG Address, PVOID Response, SIZE_T Size);
	BOOL writeVirtualMemory(ULONG Address, PVOID Value, SIZE_T Size);
};
