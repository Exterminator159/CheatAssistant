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
	ULONG dwProcessId = NULL;
	//DWORD dwProcessBaseAddress;
	void Init();
	void closeHandle();
	ULONG getProcessId();
	BOOL protectCurrentProcess(BOOLEAN enable);
	BOOL protectCurrentProcessFile();
	BOOL unProtectCurrentProcessFile();
	HANDLE getProcessHandle();
	//DWORD getProcessBaseAddress();
	BOOL readVirtualMemory(ULONG Address, PVOID Response, SIZE_T Size);
	BOOL writeVirtualMemory(ULONG Address, PVOID Value, SIZE_T Size);
	BOOL writeVirtualMemoryEx(ULONG Address, PVOID Value, SIZE_T Size);
	HMODULE getModuleHandleByModuleName(const wchar_t * moduleName);
	BOOL getModuleInfoByModuleName(LPMODULEINFO ModuleInfo, const wchar_t * moduleName);
};
#endif // !__KCY_H__


