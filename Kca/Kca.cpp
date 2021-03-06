#include "Kca.h"
#include <direct.h>
#include <string>
#ifndef KCA_API_H
#include "../KernelCheatAssistant/kca_api.h"
#endif // !KCA_API_H

#ifndef DRIVER_CONTROL_H
#include "../driver_control/drictl.h"
#pragma comment(lib,"../x64/Release/library/driver_control.lib")
#endif // !DRIVER_CONTROL_H

#include "../VMProtectSDK.h"

LPCWSTR g_SymboliLinkName = L"";
LPCWSTR g_DeviceShortName = L"";

Kca::Kca()
{
	Init();
}

Kca::~Kca()
{
	//closeHandle();
}

void Kca::Init()
{
	
	wchar_t buffer[MAX_PATH];
	_wgetcwd(buffer, MAX_PATH);
	std::wstring driverFilePath(buffer);
	driverFilePath += VMProtectDecryptStringW(L"\\sys\\" DRIVER_FILE_NAME);

	g_SymboliLinkName = VMProtectDecryptStringW(L"\\\\.\\" SYMBOLIC_LINK_SHORT_NAME);
	g_DeviceShortName = VMProtectDecryptStringW(DEVICE_SHOST_NAME);

	/*printf("g_SymboliLinkName->:%ws\n", g_SymboliLinkName);
	printf("g_DeviceShortName->:%ws\n", g_DeviceShortName);
	printf("driverFilePath->:%ws\n", driverFilePath.c_str());*/

	if (drictl::install(g_SymboliLinkName, g_DeviceShortName, driverFilePath.c_str())) {
		//dwProcessId = getProcessId();
		protectCurrentProcess(TRUE);
		//protectCurrentProcessFile();
		//getModuleHandleByModuleName(L"tcj.dll");
	}
}

void Kca::closeHandle()
{
	dwProcessId = 0;
	//drictl::uninstall(g_DeviceShortName);
	//dwProcessBaseAddress = 0;
	protectCurrentProcess(FALSE);
}

ULONG Kca::getProcessId()
{
	ULONG processId;
	drictl::control(g_SymboliLinkName,KCA_GET_PROCESS_ID, &processId, sizeof(processId), &processId, sizeof(processId));
	return processId;
}

BOOL Kca::protectCurrentProcess(BOOLEAN enable)
{
	return drictl::control(g_SymboliLinkName, KCA_PROTECT_CURRENT_PROCESS, &enable, sizeof(enable),0, 0);
}

BOOL Kca::protectCurrentProcessFile() 
{
	return drictl::control(g_SymboliLinkName, KCA_PROTECT_CURRENT_PROCESS_FILE, 0, 0, 0, 0);
}

BOOL Kca::unProtectCurrentProcessFile()
{
	return drictl::control(g_SymboliLinkName, KCA_UN_PROTECT_CURRENT_PROCESS_FILE, 0, 0, 0, 0);
}

HANDLE Kca::getProcessHandle()
{
	if (hProcess == NULL || dwProcessId != getProcessId())
	{
		dwProcessId = getProcessId();
		drictl::control(g_SymboliLinkName,KCA_GET_PROCESS_HANDLE, &hProcess, sizeof(hProcess), &hProcess, sizeof(hProcess));
	}
	return hProcess;
}

BOOL Kca::readVirtualMemory(ULONG Address, PVOID Response, SIZE_T Size)
{
	KCA_READ_VIRTUAL_MEMORY_STRUCT rvms;
	rvms.Response = Response;
	rvms.Address = Address;
	rvms.Size = Size;
	return drictl::control(g_SymboliLinkName,KCA_READ_VIRTUAL_MEMORY, &rvms, sizeof(rvms), &rvms, sizeof(rvms));
}

BOOL Kca::writeVirtualMemory(ULONG Address, PVOID Value, SIZE_T Size)
{
	KCA_WRITE_VIRTUAL_MEMORY_STRUCT wvms;
	BOOL result = TRUE;
	wvms.Address = Address;
	wvms.Value = Value;
	wvms.Size = Size;
	result =  drictl::control(g_SymboliLinkName,KCA_WRITE_VIRTUAL_MEMORY, &wvms, sizeof(wvms), &wvms, sizeof(wvms));
	if (result == FALSE)
	{
		result = writeVirtualMemoryEx(Address, Value, Size);
	}
	return result;
}

BOOL Kca::writeVirtualMemoryEx(ULONG Address, PVOID Value, SIZE_T Size)
{
	DWORD oldProtect;
	BOOL result = TRUE;
	result = VirtualProtectEx(getProcessHandle(),(LPVOID)(ULONG_PTR)Address, Size,PAGE_EXECUTE_READWRITE, &oldProtect);
	/*if (result) {
		printf("修改内存属性成功\n");
	}
	else {
		printf("修改内存属性失败\n");
	}*/
	KCA_WRITE_VIRTUAL_MEMORY_STRUCT wvms;
	wvms.Address = Address;
	wvms.Value = Value;
	wvms.Size = Size;
	result =  drictl::control(g_SymboliLinkName, KCA_WRITE_VIRTUAL_MEMORY, &wvms, sizeof(wvms), &wvms, sizeof(wvms));
	result = VirtualProtectEx(getProcessHandle(), (LPVOID)(ULONG_PTR)Address, Size, oldProtect, &oldProtect);
	/*if (result) {
		printf("还原内存属性成功\n");
	}
	else {
		printf("还原内存属性失败\n");
	}*/
	return result;
}

HMODULE Kca::getModuleHandleByModuleName(const wchar_t *moduleName)
{
	HMODULE hMods[1024];
	DWORD cbNeeded;
	if (EnumProcessModulesEx(getProcessHandle(), hMods, sizeof(hMods), &cbNeeded, LIST_MODULES_32BIT))
	{
		//setlocale(LC_CTYPE, "");
		for (size_t i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];
			GetModuleFileNameEx(getProcessHandle(), hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR));
			if (wcsstr(szModName, moduleName)) {
				/*printf("moduleName->:%ws hmodule->:%p", szModName, hMods[i]);
				printf("\n");*/
				return hMods[i];
			}
		}
	}
	return NULL;
}


BOOL Kca::getModuleInfoByModuleName(LPMODULEINFO ModuleInfo, const wchar_t *moduleName)
{
	HMODULE hMods[1024];
	DWORD cbNeeded;

	if (EnumProcessModulesEx(getProcessHandle(), hMods, sizeof(hMods), &cbNeeded, LIST_MODULES_32BIT))
	{
		//setlocale(LC_CTYPE, "");
		for (size_t i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];
			GetModuleFileNameEx(getProcessHandle(), hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR));
			if (wcsstr(szModName, moduleName)) {
				/*printf("moduleName->:%ws hmodule->:%p", szModName, hMods[i]);
				printf("\n");*/
				return GetModuleInformation(getProcessHandle(), hMods[i], ModuleInfo, sizeof(MODULEINFO));
			}
		}
	}
	return FALSE;
}