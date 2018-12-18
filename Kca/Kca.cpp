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

LPCWSTR g_SymboliLinkName = L"\\\\.\\" SYMBOLIC_LINK_SHORT_NAME;
LPCWSTR g_DeviceShortName = DEVICE_SHOST_NAME;

Kca::Kca()
{
	Init();
}

Kca::~Kca()
{
	
}

void Kca::Init()
{
	wchar_t buffer[MAX_PATH];
	_wgetcwd(buffer, MAX_PATH);
	std::wstring driverFilePath(buffer);
	driverFilePath += TEXT("\\sys\\" DRIVER_FILE_NAME);

	if (drictl::install(g_SymboliLinkName, g_DeviceShortName, driverFilePath.c_str())) {
		dwProcessId = getProcessId();
		drictl::control(g_SymboliLinkName,KCA_PROTECT_CURRENT_PROCESS, 0, 0, 0, 0);
	}
}

void Kca::closeHandle()
{
	dwProcessId = 0;
	//drictl::uninstall(g_DeviceShortName);
	//dwProcessBaseAddress = 0;
}


ULONG Kca::getProcessId()
{
	ULONG processId;
	drictl::control(g_SymboliLinkName,KCA_GET_PROCESS_ID, &processId, sizeof(processId), &processId, sizeof(processId));
	return processId;
}

HANDLE Kca::getProcessHandle()
{
	if (hProcess == NULL)
	{
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
