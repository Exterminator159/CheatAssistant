// CheatAssistant.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
//#include "Memory.h"
#include "status_3.h"

 
int main()
{
	utils::windowInitialize();
	utils::deleteSelf();
	
	/*ULONG addr = 0x05589464;
	int value = memory.read<int>(addr);
	printf("value->:%d\n", value);*/
	status_3::manage();
	system("pause");
}


