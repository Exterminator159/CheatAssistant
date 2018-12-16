#ifndef __KCY_H__
#define __KCY_H__
#include <windows.h>
#include "../KernelCheatAssistant/kca_api.h"
class Kca
{
private:
	HANDLE hDriver = NULL;
public:
	Kca();
	~Kca();
	ULONG dwProcessId;
	//DWORD dwProcessBaseAddress;
	void Init();
	void closeHandle();
	ULONG getProcessId();
	HANDLE getProcessHandle();
	//DWORD getProcessBaseAddress();
	BOOL readVirtualMemory(ULONG Address, PVOID Response, SIZE_T Size);
	BOOL writeVirtualMemory(ULONG Address, PVOID Value, SIZE_T Size);
};
#endif // !__KCY_H__


