// CheatAssistantDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Lua.h"

Lua lua;
static  void OnKeyDown(HWND hWnd, UINT wParam, BOOL bCtl, INT lParamL, UINT lParamH)
{
	
}

static  void OnSysKeyDown(HWND hWnd, UINT nChar, BOOL bCtl, UINT nRepCnt, UINT nFlags)
{
	
}

static LRESULT CALLBACK CallWndProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) 
{
	switch (uMsg)
	{
		HANDLE_MSG(hWnd, WM_KEYDOWN, OnKeyDown);
		HANDLE_MSG(hWnd, WM_SYSKEYDOWN, OnSysKeyDown);
	default:
		break;
	}
}

static void initializeThread()
{
	/*while (g_hWnd == NULL)
	{
		g_hWnd = FindWindow(L"", L"");
		Sleep(1000);
	}
	SetWindowLongA(g_hWnd, GWL_WNDPROC, (LONG_PTR)CallWndProc);*/
}

extern "C" __declspec(dllexport)void entryPoint() 
{
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initializeThread, NULL, 0, 0);
}