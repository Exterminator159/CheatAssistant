// pch.cpp: 与预编译标头对应的源文件；编译成功所必需的

#include "pch.h"

// 一般情况下，忽略此文件，但如果你使用的是预编译标头，请保留它。
WINDOW_INFO gameWindowInfo;
HWND g_hWnd = NULL;
Memory<Kca> memory;
Key<Msdk> key;
bool g_首图标记 = true;
int g_过图时间 = 0;
int g_副本编号 = 104;
bool g_自动开关 = false;
int g_自动模式 = 练习;
int g_刷图次数 = 0;
int g_预留疲劳 = 0;
int g_移动方式 = 0;