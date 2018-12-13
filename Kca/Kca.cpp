#include "Kca.h"



Kca::Kca()
{
}


Kca::~Kca()
{
	closeHandle();
}



void Kca::Init()
{
	hDriver = CreateFile(
		L"\\\\.\\" SYMBOLIC_LINK_SHORT_NAME,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0,
		OPEN_EXISTING,
		0,
		0
	);
	if (hDriver == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"#��������ʧ��,����취����\n\n#��ͥ�û���رհ�ȫ���\n#������ɵ����ɷ���ǽ�ص�\n\n#������Ϸ���û�н�������������������Թ���Ա�������", NULL, NULL);
		exit(0);
	}
	dwProcessId = getProcessId();
	//dwProcessBaseAddress = getProcessBaseAddress();
}

void Kca::closeHandle()
{
	if (hDriver != NULL)
	{
		CloseHandle(hDriver);
		hDriver = NULL;
		dwProcessId = 0;
		//dwProcessBaseAddress = 0;
	}

}

DWORD Kca::getProcessId()
{
	ULONG processId;
	DeviceIoControl(hDriver, KCA_GET_PROCESS_ID, &processId, sizeof(processId), &processId, sizeof(processId), 0, 0);
	return processId;
}

HANDLE Kca::getProcessHandle()
{
	HANDLE processHandle;
	DeviceIoControl(hDriver, KCA_GET_PROCESS_HANDLE, &processHandle, sizeof(processHandle), &processHandle, sizeof(processHandle), 0, 0);
	return processHandle;
}

//DWORD Kca::getProcessBaseAddress()
//{
//	ULONG baseAddress;
//	DeviceIoControl(hDriver, KCA_GET_PROCESS_BASE_ADDRESS, &baseAddress, sizeof(baseAddress), &baseAddress, sizeof(baseAddress), 0, 0);
//	return baseAddress;
//}

BOOL Kca::readVirtualMemory(ULONG Address, PVOID Response, SIZE_T Size)
{
	KCA_READ_VIRTUAL_MEMORY_STRUCT rvms;
	rvms.Response = Response;
	rvms.Address = Address;
	rvms.Size = Size;
	return DeviceIoControl(hDriver, KCA_READ_VIRTUAL_MEMORY, &rvms, sizeof(rvms), &rvms, sizeof(rvms), 0, 0);
}

BOOL Kca::writeVirtualMemory(ULONG Address, PVOID Value, SIZE_T Size)
{
	KCA_WRITE_VIRTUAL_MEMORY_STRUCT wvms;
	wvms.Address = Address;
	wvms.Value = Value;
	wvms.Size = Size;
	return DeviceIoControl(hDriver, KCA_WRITE_VIRTUAL_MEMORY, &wvms, sizeof(wvms), &wvms, sizeof(wvms), 0, 0);
}
