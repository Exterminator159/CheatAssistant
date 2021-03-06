// CheatAssistantDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Lua.h"

#define MY_MESSAGE_ID 10024

Lua lua;
WNDPROC g_orgProc;
bool g_initLua = false;
bool g_luaStatus = false;
bool g_threadLook = false;
int g_threadStatus = 0;

HANDLE hMutex;

static void mainThread()
{
	
	while (true)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (g_luaStatus) {
			lua_getglobal(lua.L, "main");
			lua.check(lua_pcall(lua.L, 0, 0, 0));
		}
		ReleaseMutex(hMutex);
	}
}

static  void OnKeyDown(HWND hWnd, UINT wParam, BOOL bCtl, INT lParamL, UINT lParamH)
{
	switch (wParam)
	{
	case VK_F5:
		if (g_luaStatus == false)
		{
			g_initLua = g_luaStatus = lua.doFile("C:\\lua\\main.lua");
		}
		else {
			g_luaStatus = false;
		}
		break;
	default:
		lua_pushboolean(lua.L, false);
		lua_setglobal(lua.L, "g_switch");
		WaitForSingleObject(hMutex, INFINITE);
		if (g_initLua)
		{
			lua_getglobal(lua.L, "onKeyDown");
			lua_pushinteger(lua.L, (lua_Integer)hWnd);
			lua_pushinteger(lua.L, (lua_Integer)wParam);
			lua_pushinteger(lua.L, (lua_Integer)bCtl);
			lua_pushinteger(lua.L, (lua_Integer)lParamL);
			lua_pushinteger(lua.L, (lua_Integer)lParamH);
			lua.check(lua_pcall(lua.L, 5, 0, 0));          //用保护模式调用lua函数，入参个数为0、出参个数为0、无自定义错误处理
		}
		lua_pushboolean(lua.L, true);
		lua_setglobal(lua.L, "g_switch");
		ReleaseMutex(hMutex);
		break;
	}
}

static  void OnSysKeyDown(HWND hWnd, UINT nChar, BOOL bCtl, UINT nRepCnt, UINT nFlags)
{
	lua_pushboolean(lua.L, false);
	lua_setglobal(lua.L, "g_switch");
	WaitForSingleObject(hMutex, INFINITE);
	if (g_initLua)
	{
		lua_getglobal(lua.L, "onSysKeyDown");
		lua_pushinteger(lua.L, (lua_Integer)hWnd);
		lua_pushinteger(lua.L, (lua_Integer)nChar);
		lua_pushinteger(lua.L, (lua_Integer)bCtl);
		lua_pushinteger(lua.L, (lua_Integer)nRepCnt);
		lua_pushinteger(lua.L, (lua_Integer)nFlags);
		lua.check(lua_pcall(lua.L, 5, 0, 0));          //用保护模式调用lua函数，入参个数为0、出参个数为0、无自定义错误处理
	}
	lua_pushboolean(lua.L, true);
	lua_setglobal(lua.L, "g_switch");
	ReleaseMutex(hMutex);
}

static LRESULT CALLBACK CallWndProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) 
{
	switch (uMsg)
	{
		HANDLE_MSG(hWnd, WM_KEYDOWN, OnKeyDown);
		HANDLE_MSG(hWnd, WM_SYSKEYDOWN, OnSysKeyDown);
	default:
		if (uMsg == MY_MESSAGE_ID)
		{
			lua_pushboolean(lua.L, false);
			lua_setglobal(lua.L, "g_switch");
			WaitForSingleObject(hMutex, INFINITE);
			if (g_initLua)
			{
				lua_getglobal(lua.L, "CallWndProc");
				lua_pushinteger(lua.L, (lua_Integer)hWnd);
				lua_pushinteger(lua.L, (lua_Integer)uMsg);
				lua_pushinteger(lua.L, (lua_Integer)wParam);
				lua_pushinteger(lua.L, (lua_Integer)lParam);
				lua.check(lua_pcall(lua.L, 4, 0, 0));          //用保护模式调用lua函数，入参个数为0、出参个数为0、无自定义错误处理
			}
			lua_pushboolean(lua.L, true);
			lua_setglobal(lua.L, "g_switch");
			ReleaseMutex(hMutex);
		}
		break;
	}
	
	return CallWindowProc(g_orgProc, hWnd, uMsg, wParam, lParam);
}

static void initializeThread()
{
	while (g_hWnd == NULL)
	{
		OutputDebugString(L"Lua initializeThread");
		g_hWnd = FindWindow(L"YodaoMainWndClass", L"网易有道词典");
		Sleep(1000);
	}
	g_orgProc = (WNDPROC)SetWindowLongA(g_hWnd, GWL_WNDPROC, (LONG_PTR)CallWndProc);

	lua_pushinteger(lua.L, (lua_Integer)g_hWnd);
	lua_setglobal(lua.L,"g_hWnd");

	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mainThread, NULL, 0, 0);
	wchar_t buffer[0x100];
	swprintf_s(buffer,L"mochv354y0XrTzy8%d",GetCurrentThreadId());
	hMutex = CreateMutex(NULL, FALSE, buffer);
	CloseHandle(hThread);
}

extern "C" __declspec(dllexport)void entryPoint() 
{
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initializeThread, NULL, 0, 0);
}