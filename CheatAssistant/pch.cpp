// pch.cpp: 与预编译标头对应的源文件；编译成功所必需的

#include "pch.h"

// 一般情况下，忽略此文件，但如果你使用的是预编译标头，请保留它。
WINDOW_INFO gameWindowInfo;
Lua lua;
HWND g_hWnd = NULL;
Memory<Kca> memory;
Key<Msdk> key;
int g_异常计数 = 0;
bool g_首图标记 = true;
int g_过图时间 = 0;
int g_副本编号 = 104;
int g_副本难度 = 1;
bool g_自动开关 = false;
int g_自动模式 = 剧情;
int g_刷图次数 = 0;
int g_预留疲劳 = 0;
int g_移动方式 = 1;
int g_剧情功能 = 0; //0-变身
int g_变身代码 = 107000902; //当剧情功能=变身此代码生效 107000902-吞噬魔 110525-蔡依林