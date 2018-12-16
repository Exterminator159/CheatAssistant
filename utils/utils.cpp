#include "utils.h"


HANDLE msdk_handle;

void utils::myprintf(const char *_Format, WORD Color, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
	va_list argList;
	char buffer[0x1024];
	va_start(argList, Color);
	vsprintf_s(buffer, _Format, argList);
	std::locale loc("chs");
	std::cout << buffer << std::endl;
	va_end(argList);
}
void utils::mywprintf(const wchar_t * _Format, WORD Color, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
	va_list argList;
	wchar_t buffer[0x1024];
	va_start(argList, Color);
	vswprintf_s(buffer, _Format, argList);
	setlocale(LC_CTYPE, "");
	wprintf(L"name %s\n", buffer);
	va_end(argList);
}
void utils::printString(const char * _Format, WORD Color, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
	va_list argList;
	char buffer[0x1024];
	va_start(argList, Color);
	vsprintf_s(buffer, _Format, argList);
	std::locale loc("chs");
	std::cout << buffer << std::endl;
	va_end(argList);
}
void utils::printWString(const wchar_t * _Format, WORD Color, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
	va_list argList;
	wchar_t buffer[0x1024];
	va_start(argList, Color);
	vswprintf_s(buffer, _Format, argList);
	setlocale(LC_CTYPE, "");
	wprintf(L"name %s\n", buffer);
	va_end(argList);
}
HWND utils::getWindowHandle()
{
	//std::wstring wstr(_T("���³�����ʿ"));
	//return FindWindow(wstr.c_str(), wstr.c_str());
}
WINDOW_INFO utils::getWindowInfo(HWND hWnd)
{
	RECT rect;
	WINDOW_INFO window_info;
	GetWindowRect(hWnd, &rect);
	window_info.bottom = rect.bottom;
	window_info.left = rect.left;
	window_info.right = rect.right;
	window_info.top = rect.top;
	window_info.width = window_info.right - window_info.left;
	window_info.height = window_info.bottom - window_info.top;
	return window_info;
}
int utils::createRandom(int min, int max)
{
	int Random = 0;
	if (max > min) {
		srand((unsigned)time(NULL));
		Random = (rand() % (min - max + 1) + max);
	}
	else {
		srand((unsigned)time(NULL));
		Random = (rand() % (max - min + 1) + min);
	}
	return Random;
}
void utils::randomSleep(int min, int max)
{
	Sleep(createRandom(min, max));
}
void utils::outputDbebugWString(const wchar_t *lpcszFormat, ...)
{
	va_list argList;
	wchar_t buffer[0x1024];
	wchar_t temp_buffer[0x1024];
	va_start(argList, lpcszFormat);
	vswprintf_s(buffer, lpcszFormat, argList);
	//swprintf_s(temp_buffer, L"DXFһ�� %s", buffer);
	OutputDebugStringW(temp_buffer);
	va_end(argList);
}
void utils::outputDbebugString(const char *lpcszFormat, ...)
{
	va_list argList;
	char buffer[0x1024];
	char temp_buffer[0x1024];
	va_start(argList, lpcszFormat);
	vsprintf_s(buffer, lpcszFormat, argList);
	//sprintf_s(temp_buffer, "DXFһ�� %s", buffer);
	OutputDebugStringA(temp_buffer);
	va_end(argList);
}


void utils::windowInitialize()
{
	RECT rect;
	int cx, cy;
	int width, height;
	cx = GetSystemMetrics(SM_CXFULLSCREEN);
	cy = GetSystemMetrics(SM_CYFULLSCREEN);
	HWND g_self_window_handle = GetConsoleWindow();
	GetWindowRect(g_self_window_handle, &rect);
	MoveWindow(g_self_window_handle, 0, 0, 800, 600, TRUE);
	GetWindowRect(g_self_window_handle, &rect);
	width = (rect.right - rect.left);
	height = (rect.bottom - rect.top);
	MoveWindow(g_self_window_handle, cx - width, cy - height, width, height, TRUE);

	EnableMenuItem(GetSystemMenu(g_self_window_handle, FALSE), SC_CLOSE, MF_GRAYED);
	SetConsoleTitle(_T("x64"));
	//SetLayeredWindowAttributes(g_self_window_handle, 0, 200, 3);//͸��������
}

std::string utils::formatString(const char *lpcszFormat, ...)
{
	char *pszStr = NULL;
	if (NULL != lpcszFormat)
	{
		va_list marker = NULL;
		va_start(marker, lpcszFormat); //��ʼ����������
		size_t nLength = _vscprintf(lpcszFormat, marker) + 1; //��ȡ��ʽ���ַ�������
		pszStr = new char[nLength];
		memset(pszStr, '\0', nLength);
		_vsnprintf_s(pszStr, nLength, nLength, lpcszFormat, marker);
		va_end(marker); //���ñ�������
	}
	std::string strResult(pszStr);
	delete[]pszStr;
	return strResult;
}

std::wstring utils::formatWstring(const wchar_t *lpcwszFormat, ...)
{
	wchar_t *pszStr = NULL;
	if (NULL != lpcwszFormat)
	{
		va_list marker = NULL;
		va_start(marker, lpcwszFormat); //��ʼ����������
		size_t nLength = _vscwprintf(lpcwszFormat, marker) + 1; //��ȡ��ʽ���ַ�������
		pszStr = new wchar_t[nLength];
		memset(pszStr, L'\0', nLength);
		_vsnwprintf_s(pszStr, nLength, nLength, lpcwszFormat, marker);
		va_end(marker); //���ñ�������
	}
	std::wstring strResult(pszStr);
	delete[]pszStr;
	return strResult;
}

void utils::vectorBytesToBytes(std::vector<byte> v_bytes, byte* bytes)
{
	for (size_t i = 0; i < v_bytes.size(); i++)
	{
		bytes[i] = v_bytes[i];
	}
}

std::vector<byte>  utils::bytesToVectorBytes(byte* bytes, size_t size)
{
	std::vector<byte> v_bytes;
	v_bytes.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		v_bytes[i] = bytes[i];
	}
	return v_bytes;
}

// ��ȡʱ���
DWORD utils::getTime()
{
	DWORD t_start;
	t_start = GetTickCount();//�Ӳ���ϵͳ������������elapsed���ĺ����������ķ���ֵ��DWORD��
	return  t_start;
}

bool utils::deleteSelf()
{
	bool result = true;
	wchar_t FileName[MAX_PATH];
	memset(FileName, 0, MAX_PATH);
	//��ȡ�ļ�·��
	GetModuleFileName(NULL, FileName, MAX_PATH);
	wchar_t *NewFileName;
	NewFileName = new wchar_t[MAX_PATH];
	memset(NewFileName, 0, MAX_PATH);
	//�����ļ�����
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_NORMAL);
	//����ֱ��ɾ��
	if (DeleteFile(FileName))//��ֱ��ɾ�����
	{
		delete[] NewFileName;
		return false;
	}
	//����APIһ�������ن���
	wsprintf(NewFileName, L"C:\\Windows\\%C\0", FileName[0]);
	CreateDirectory(NewFileName, NULL);
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_HIDDEN);
	wsprintf(NewFileName, L"C:\\Windows ����������\0", FileName[0], GetTickCount());
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_NORMAL);
	DeleteFile(NewFileName);
	if (!MoveFileEx(FileName, NewFileName, MOVEFILE_REPLACE_EXISTING))
	{
		delete[] NewFileName;
		//printf("ɾ������ʧ�� Error Code\n");
		return false;//�����˾ͷ���
	}
	MoveFileEx(NewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
	delete[] NewFileName;
	if (result == false)
	{
		printf("deleteSelf Error Code\n");
		system("pause");
		exit(0);
	}
	return result;
}