// CheatAssistant.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "function.h"
#include "status_3.h"
#include "role.h"
#include "call.h"

#ifndef KCA_API_H
#include "../KernelCheatAssistant/kca_api.h"
#endif // !KCA_API_H

#ifndef DRIVER_CONTROL_H
#include "../driver_control/drictl.h"
#pragma comment(lib,"../x64/Release/library/driver_control.lib")
#endif // !DRIVER_CONTROL_H

int HotKeyId_END = 0;
int HotKeyId_HOME = 0;
int HotKeyId_F1 = 0;
int HotKeyId_F2 = 0;
int HotKeyId_F3 = 0;

void startAuto()
{
	
	while (g_自动开关)
	{
		//utils::mywprintf(L"function::getGameStatus->:%d", RED, function::getGameStatus());//
		while (g_hWnd == NULL)
		{
			g_hWnd = utils::getWindowHandle();
			Sleep(1000);
			
		}
		//if (GetActiveWindow() != g_hWnd)
		if (GetForegroundWindow() != g_hWnd)
		{
			//SetActiveWindow(g_hWnd);
			SetForegroundWindow(g_hWnd);
			Sleep(1000);
			return;
		}
		if (memory.read<int>(__对话基址) == 1)
		{
			key.doKeyPress(VK_RETURN);
			Sleep(1000);
			continue;
		}
		switch (function::getGameStatus())
		{
		case 0:

			break;
		case 1:
			break;
		case 2:

			break;
		case 3:

			
			status_3::manage();
			break;
		default:
			utils::mywprintf(L"get_status_error");//
			break;
		}
	}
}

void exitProcess()
{

	UnregisterHotKey(NULL, HotKeyId_END);
	UnregisterHotKey(NULL, HotKeyId_HOME);
	UnregisterHotKey(NULL, HotKeyId_F1);
	UnregisterHotKey(NULL, HotKeyId_F2);
	UnregisterHotKey(NULL, HotKeyId_F3);
	key.upAllKey();
	key.closeHandle();
	utils::printString("handle close ...");
	memory.close();
	utils::printString("kca close ...");
	//UN_PROTECT_FILE();
	int s = 1;
	while (s > 0) {
		utils::printString("程序将在 %d 秒后结束...", RED, s);
		s--;
		Sleep(1000);
	}
	TerminateProcess(GetCurrentProcess(), 0);
}

void test()
{
	Sleep(2000);
	utils::myprintf("开始移动");
	ROLE_POS pos = role::getRolePos();
	pos.x += 600;
	pos.y += 50;
	role::moveRoleToPos(pos);
	return;
}


VOID ThreadMessage(
	MSG* msg
)
{
	switch (msg->message)
	{
	case WM_HOTKEY:
		if (msg->wParam == HotKeyId_END)
		{
			utils::printString("HotKeyId_END");
			if (g_自动开关 == true)
			{
				g_自动开关 = false;
				utils::myprintf("请等待自动线程停止");
			}
			else {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)exitProcess, NULL, 0, 0);
			}
		}
		else if (msg->wParam == HotKeyId_HOME) {
			utils::printString("HotKeyId_HOME");
		}
		else if (msg->wParam == HotKeyId_F1) {
			utils::printString("HotKeyId_F1");
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)test, 0, 0, 0);
		}
		else if (msg->wParam == HotKeyId_F2) {
			utils::printString("HotKeyId_F2");
			g_自动开关 = true;
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startAuto, 0, 0, 0);
		}
		else if (msg->wParam == HotKeyId_F3) {
			utils::printString("HotKeyId_F3");
			//call::技能Call(0,70023,113,200,200,0);
			//call::坐标Call(memory.read<int>(__人物基址), 300, 300, 0);
			//call::公告CALL(L"aaaa啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊是");
		}
	default:
		break;
	}
}

void RegHotKeys()
{
	HotKeyId_END = GlobalAddAtom(L"HotKeyId_END");
	HotKeyId_HOME = GlobalAddAtom(L"HotKeyId_HOME");
	HotKeyId_F1 = GlobalAddAtom(L"HotKeyId_F1");
	HotKeyId_F2 = GlobalAddAtom(L"HotKeyId_F2");
	HotKeyId_F3 = GlobalAddAtom(L"HotKeyId_F3");
	if (!RegisterHotKey(NULL, HotKeyId_END, NULL, VK_END))
		utils::myprintf("END 注册失败 HotKeyId_END->:%d", RED, HotKeyId_END);

	if (!RegisterHotKey(NULL, HotKeyId_HOME, NULL, VK_HOME))
		utils::myprintf("HOME 注册失败 HotKeyId_HOME->:%d", RED, HotKeyId_HOME);

	if (!RegisterHotKey(NULL, HotKeyId_F1, NULL, VK_F1))
		utils::myprintf("F1 注册失败 HotKeyId_F1->:%d", RED, HotKeyId_F1);

	if (!RegisterHotKey(NULL, HotKeyId_F2, NULL, VK_F2))
		utils::myprintf("F2 注册失败 HotKeyId_F2->:%d", RED, HotKeyId_F2);

	if (!RegisterHotKey(NULL, HotKeyId_F3, NULL, VK_F3))
		utils::myprintf("F3 注册失败 HotKeyId_F3->:%d", RED, HotKeyId_F3);
}
 
int main()
{
	utils::windowInitialize();
	utils::deleteSelf();

	RegHotKeys();

	
	

	printf("hProcess->:%p\n", memory.getProcessHandle());

	printf("value->:%d\n", memory.read<int>(0x00ADB570));
	printf("value->:%d\n", memory.write<int>(0x00ADB570, 200));

	printf("value->:%d\n", memory.read<int>(0x00297354));
	printf("value->:%d\n", memory.write<int>(0x00297354, 300));
	

	MSG msg = { 0 };//消息指针
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//等待信号
		DispatchMessage(&msg);//处理信号
		ThreadMessage(&msg);//线程消息处理
	}
}


