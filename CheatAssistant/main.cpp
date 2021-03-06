// CheatAssistant.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "function.h"
#include "status_0.h"
#include "status_1.h"
#include "status_2.h"
#include "status_3.h"
#include "role.h"
#include "call.h"
#include "hook.h"
#include "task.h"
#include "send_packet.h"
#include "astar.hpp"
#include "knapsac.h"

#ifndef KCA_API_H
#include "../KernelCheatAssistant/kca_api.h"
#endif // !KCA_API_H

#ifndef DRIVER_CONTROL_H
#include "../driver_control/drictl.h"
#pragma comment(lib,"../x64/Release/library/driver_control.lib")
#endif // !DRIVER_CONTROL_H

Hook hookTest;

//SendPacket sendPacket;

int HotKeyId_END = 0;
int HotKeyId_HOME = 0;
int HotKeyId_F1 = 0;
int HotKeyId_F2 = 0;
int HotKeyId_F3 = 0;
int HotKeyId_F4 = 0;

void startAuto()
{
	
	while (g_自动开关)
	{
		//utils::mywprintf(L"fun::getGameStatus->:%d", RED, fun::getGameStatus());//
		while (g_hWnd == NULL && g_自动开关 == true)
		{
			g_hWnd = utils::getWindowHandle();
			Sleep(1000);
			printf(VMProtectDecryptStringA("startAuto 0\n"));
		}
		if (GetForegroundWindow() != g_hWnd)
		{
			g_hWnd = utils::getWindowHandle();
			if (g_hWnd)
			{
				SetForegroundWindow(g_hWnd);
				Sleep(1000);
				printf(VMProtectDecryptStringA("恢复窗口置顶"));
			}
			else {
				printf(VMProtectDecryptStringA("游戏已掉线"));
				g_自动开关 = false;
			}
			
			
			continue;
		}
		if (fun::passStoryFrame() == false)
		{
			/*key.doKeyPress(VK_ESCAPE);
			Sleep(100);
			if (memory.read<int>(__对话基址) == 1)
			{
				key.doKeyPress(VK_RETURN);
			}
			printf("startAuto 2\n");*/
			continue;
		}
		switch (fun::getGameStatus())
		{
		case 0:
			status_0::manage();
			break;
		case 1:
			status_1::manage();
			break;
		case 2:
			status_2::manage();
			break;
		case 3:
			status_3::manage();
			break;
		default:
			utils::mywprintf(VMProtectDecryptStringW(L"get_status_error"));//
			break;
		}
	}
	utils::mywprintf(VMProtectDecryptStringW(L"自动已经关闭"));//
}

void exitProcess()
{

	UnregisterHotKey(NULL, HotKeyId_END);
	UnregisterHotKey(NULL, HotKeyId_HOME);
	UnregisterHotKey(NULL, HotKeyId_F1);
	UnregisterHotKey(NULL, HotKeyId_F2);
	UnregisterHotKey(NULL, HotKeyId_F3);
	UnregisterHotKey(NULL, HotKeyId_F4);
	key.upAllKey();
	key.closeHandle();
	utils::printString(VMProtectDecryptStringA("handle close ..."));
	memory.close();
	utils::printString(VMProtectDecryptStringA("kca close ..."));
	//UN_PROTECT_FILE();
	memory.unProtectCurrentProcessFile();
	int s = 1;
	while (s > 0) {
		utils::printString(VMProtectDecryptStringA("程序将在 %d 秒后结束..."), RED, s);
		s--;
		Sleep(1000);
	}
	TerminateProcess(GetCurrentProcess(), 0);
}

void test()
{
	/*Sleep(2000);
	utils::myprintf(VMProtectDecryptStringA("开始移动"));
	ROLE_POS pos = role::getRolePos();
	pos.x += 600;
	pos.y += 50;
	role::moveRoleToPos(pos);*/
	utils::printString(VMProtectDecryptStringA("便利已接任务"));
	task::outputTaskInfo(1);
	/*utils::printString(VMProtectDecryptStringA("便利所有任务"));
	task::outputTaskInfo(0);*/
	utils::printString(VMProtectDecryptStringA("便利主线任务"));
	task::outputTaskInfo(2);
	
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
			utils::printString(VMProtectDecryptStringA("HotKeyId_END"));
			if (g_自动开关 == true)
			{
				g_自动开关 = false;
				utils::myprintf(VMProtectDecryptStringA("请等待自动线程停止"));
			}
			else {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)exitProcess, NULL, 0, 0);
			}
		}
		else if (msg->wParam == HotKeyId_HOME) {
			system("ipconfig/flushdns");
			utils::printString(VMProtectDecryptStringA("HotKeyId_HOME"));
			g_hWnd = utils::getWindowHandle();
			if (g_hWnd)
			{
				gameWindowInfo = utils::getWindowInfo(g_hWnd);
				fun::hookWindowMessage();
				g_自动开关 = true;
				if(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startAuto, 0, 0, 0) == NULL)
					utils::myprintf(VMProtectDecryptStringA("自动线程创建失败"));
			}
			else {
				utils::myprintf(VMProtectDecryptStringA("未找到游戏窗口"));
			}
		}
		else if (msg->wParam == HotKeyId_F1) {
			status_3::outputMapObjectInfo();
		}
		else if (msg->wParam == HotKeyId_F2) {
			//key.setMousePos(500,500);
			utils::myprintf(VMProtectDecryptStringA("status_3::getTheSpoilsCount()->:%d"),PINK,status_3::getTheSpoilsCount());
		}
		else if (msg->wParam == HotKeyId_F3) {
			utils::printString(VMProtectDecryptStringA("HotKeyId_F3"));
			//knapsac::keyPadSellThings();
			utils::printString(VMProtectDecryptStringA("__对话基址1->:%d"), PINK, memory.read<int>(__对话基址1));
			utils::printString(VMProtectDecryptStringA("__对话基址2->:%d"), PINK, memory.read<int>(__对话基址2));
			utils::printString(VMProtectDecryptStringA("__任务对话->:%d"), PINK, memory.read<int>(__任务对话));
		}
		else if (msg->wParam == HotKeyId_F4) {
			//utils::printString(VMProtectDecryptStringA("HotKeyId_F4"));
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)test, 0, 0, 0);
			//lua.doFile("lua/test.lua");
			//lua_getglobal(lua.L, "lua_function");   //函数名为ruler
			//lua_pushnumber(lua.L, 1);
			//lua_pcall(lua.L, 1, 0, 0);          //用保护模式调用lua函数，入参个数为0、出参个数为0、无自定义错误处理
			status_3::getTheSpoils();
		}
	default:
		break;
	}
}

void RegHotKeys()
{
	HotKeyId_END = GlobalAddAtom(VMProtectDecryptStringW(L"HotKeyId_END"));
	HotKeyId_HOME = GlobalAddAtom(VMProtectDecryptStringW(L"HotKeyId_HOME"));
	HotKeyId_F1 = GlobalAddAtom(VMProtectDecryptStringW(L"HotKeyId_F1"));
	HotKeyId_F2 = GlobalAddAtom(VMProtectDecryptStringW(L"HotKeyId_F2"));
	HotKeyId_F3 = GlobalAddAtom(VMProtectDecryptStringW(L"HotKeyId_F3"));
	HotKeyId_F4 = GlobalAddAtom(VMProtectDecryptStringW(L"HotKeyId_F4"));
	if (!RegisterHotKey(NULL, HotKeyId_END, NULL, VK_END))
		utils::myprintf(VMProtectDecryptStringA("END 注册失败 HotKeyId_END->:%d"), RED, HotKeyId_END);

	if (!RegisterHotKey(NULL, HotKeyId_HOME, NULL, VK_HOME))
		utils::myprintf(VMProtectDecryptStringA("HOME 注册失败 HotKeyId_HOME->:%d"), RED, HotKeyId_HOME);

	if (!RegisterHotKey(NULL, HotKeyId_F1, NULL, VK_F1))
		utils::myprintf(VMProtectDecryptStringA("F1 注册失败 HotKeyId_F1->:%d"), RED, HotKeyId_F1);

	if (!RegisterHotKey(NULL, HotKeyId_F2, NULL, VK_F2))
		utils::myprintf(VMProtectDecryptStringA("F2 注册失败 HotKeyId_F2->:%d"), RED, HotKeyId_F2);

	if (!RegisterHotKey(NULL, HotKeyId_F3, NULL, VK_F3))
		utils::myprintf(VMProtectDecryptStringA("F3 注册失败 HotKeyId_F3->:%d"), RED, HotKeyId_F3);

	if (!RegisterHotKey(NULL, HotKeyId_F4, NULL, VK_F4))
		utils::myprintf(VMProtectDecryptStringA("F4 注册失败 HotKeyId_F4->:%d"), RED, HotKeyId_F4);
}
 
int main()
{
	utils::windowInitialize();
	utils::deleteSelf();

	RegHotKeys();

	/*CHttpClient Http;
	CString Data;
	wstring RetData;

	Http.HttpPost(L"http://127.0.0.1/test.php", L"", RetData);

	std::wcout << RetData.c_str() << std::endl;*/

	system("ipconfig/flushdns");

	MSG msg = { 0 };//消息指针
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//等待信号
		DispatchMessage(&msg);//处理信号
		ThreadMessage(&msg);//线程消息处理
	}
}


