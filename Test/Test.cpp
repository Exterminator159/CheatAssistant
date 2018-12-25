// Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#ifndef __LUA_H__
#include "../lua/Lua.h"
#pragma comment(lib,"../x64/Release/library/Lua.lib")
#endif // !__LUA_H__
Lua lua;

int main()
{
	lua.doFile("./lua/test.lua");
	lua_getglobal(lua.L, "lua_function");   //函数名为ruler
	lua_pushnumber(lua.L, 1);
	lua_pcall(lua.L, 1, 0, 0);          //用保护模式调用lua函数，入参个数为0、出参个数为0、无自定义错误处理
	system("pause");
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
