#ifndef __KCY_H__
#define __KCY_H__
#include <windows.h>
#include <psapi.h>
class Kca
{
private:
	//HANDLE hDriver = NULL;
public:
	HANDLE hProcess = NULL;
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
	BOOL writeVirtualMemoryEx(ULONG Address, PVOID Value, SIZE_T Size);
	HMODULE getModuleHandleByModuleName(const wchar_t * moduleName);
};
#endif // !__KCY_H__


