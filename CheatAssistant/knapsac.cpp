#include "pch.h"
#include "knapsac.h"


#pragma once


static DWORD GetKnapsacAddress()
{
	return memory.read<int>(__������ַ);
}

static DWORD GetKnapsacStartAddress()
{
	return memory.read<int>(GetKnapsacAddress() + 88) + 36;
}

static GOODS_INFO GetGoodsInfo(int GoodsAddress)
{
	GOODS_INFO _GoodsInfo;
	_GoodsInfo.address = GoodsAddress;
	_GoodsInfo.name = memory.readWString(memory.read<int>(GoodsAddress + 36), 52);
	_GoodsInfo.level = memory.read<int>(GoodsAddress + 376);
	return _GoodsInfo;
}

static int GetGoodsIndexByGoodsName(std::wstring GoodsName)
{
	DWORD StartAddress = GetKnapsacStartAddress();
	GOODS_INFO _GoodsInfo;
	DWORD GoodsAddress;
	for (size_t i = 0; i < 279; i++)
	{
		GoodsAddress = memory.read<int>(StartAddress + i * 4);
		if (GoodsAddress == 0 || GoodsAddress == NULL)continue;
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		_GoodsInfo.index = i + 9;
		//output_bebug_wstring(L"%ws --- %ws", _GoodsInfo.name.c_str(), GoodsName.c_str());
		//if (_GoodsInfo.name.c_str() == GoodsName.c_str())equals
		if (wcscmp(_GoodsInfo.name.c_str(), GoodsName.c_str()) == 0)
		{
			return _GoodsInfo.index;
		}
	}
	return -1;
}

static int �������()
{
	DWORD StartAddress = GetKnapsacStartAddress();
	GOODS_INFO _GoodsInfo;
	DWORD GoodsAddress;
	for (size_t i = 0; i < 55; i++)
	{
		GoodsAddress = memory.read<int>(StartAddress + i * 4);
		if (GoodsAddress == 0 || GoodsAddress == NULL)continue;
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		_GoodsInfo.index = i + 9;
		if (
			(_GoodsInfo.name.find(L"����", 0) == -1) &&
			(_GoodsInfo.name.find(L"����", 0) == -1) &&
			(_GoodsInfo.name.find(L"�", 0) == -1)
			)
		{
			if (
				_GoodsInfo.level == 0 ||
				_GoodsInfo.level == 1 ||
				_GoodsInfo.level == 2
				)
			{
				//main_thread_exec_call(Send_�������, { _GoodsInfo.index });
				Sleep(500);
			}
		}
	}
	return -1;
}

static void OutputGoodsInfo()
{
	DWORD StartAddress = GetKnapsacStartAddress();
	GOODS_INFO _GoodsInfo;
	DWORD GoodsAddress;
	for (size_t i = 0; i < 279; i++)
	{
		GoodsAddress = memory.read<int>(StartAddress + i * 4);
		if (!GoodsAddress)
		{
			continue;
		}
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		_GoodsInfo.index = i + 9;
		utils::mywprintf(_T("====================================="));
		utils::mywprintf(_T("��ַ 0x%x"),YELLOW, _GoodsInfo.address);
		utils::mywprintf(_T("�ȼ� %d"), YELLOW, _GoodsInfo.level);
		utils::mywprintf(_T("���� %s"), YELLOW, _GoodsInfo.name.c_str());
		utils::mywprintf(_T("�±� %d"), YELLOW, _GoodsInfo.index);
	}
}

static POS get_goods_pos_by_index(int index)
{
	POS pos;
	int x, y;
	if (index >= 0 and index <= 7)
	{
		x = index * 30;
		y = 0;
	}
	else if (index >= 8 and index <= 15)
	{
		x = (index - 8) * 30;
		y = 30;
	}
	else if (index >= 16 and index <= 23)
	{
		x = (index - 16) * 30;
		y = 60;
	}
	else if (index >= 24 and index <= 31)
	{
		x = (index - 24) * 30;
		y = 90;
	}
	else if (index >= 32 and index <= 39)
	{
		x = (index - 32) * 30;
		y = 120;
	}
	else if (index >= 40 and index <= 47)
	{
		x = (index - 40) * 30;
		y = 150;
	}
	else if (index >= 48 and index <= 55)
	{
		x = (index - 48) * 30;
		y = 180;
	}
	pos.x = gameWindowInfo.left + 623 + x;
	pos.y = gameWindowInfo.top + 301 + y;
	return pos;
}

static int get_goods_count()
{
	DWORD StartAddress = GetKnapsacStartAddress();
	GOODS_INFO _GoodsInfo;
	DWORD GoodsAddress;
	int count = 0;
	for (size_t i = 0; i < 55; i++)
	{
		GoodsAddress = memory.read<int>(StartAddress + i * 4);
		if (GoodsAddress == 0 || GoodsAddress == NULL)continue;
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		_GoodsInfo.index = i + 9;
		if (
			(_GoodsInfo.name.find(L"����", 0) == -1) &&
			(_GoodsInfo.name.find(L"����", 0) == -1) &&
			(_GoodsInfo.name.find(L"�", 0) == -1)
			)
		{
			if (
				_GoodsInfo.level == 0 ||
				_GoodsInfo.level == 1 ||
				_GoodsInfo.level == 2
				)
			{
				count++;
			}
		}
	}
	return count;
}

static void ��������()
{
	if (get_goods_count() < 13) {
		return;
	}
	DWORD StartAddress = GetKnapsacStartAddress();
	GOODS_INFO _GoodsInfo;
	DWORD GoodsAddress;
	POS goods_pos;
	/*game_window_info = get_window_info(g_hWnd);*/
	for (size_t i = 0; i < 55; i++)
	{
		GoodsAddress = memory.read<int>(StartAddress + i * 4);
		if (GoodsAddress == 0 || GoodsAddress == NULL)continue;
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		if (
			(_GoodsInfo.name.find(L"����", 0) == -1) &&
			(_GoodsInfo.name.find(L"����", 0) == -1) &&
			(_GoodsInfo.name.find(L"�", 0) == -1)
			)
		{
			if (
				_GoodsInfo.level == 0 ||
				_GoodsInfo.level == 1 ||
				_GoodsInfo.level == 2
				)
			{
				if (memory.read<int>(__���״̬) != 5)
				{
					key.setMousePos(gameWindowInfo.left + 192, gameWindowInfo.top + 518);
					Sleep(1000);
					key.mouseClick();
					Sleep(1000);
					key.setMousePos(gameWindowInfo.left + 630, gameWindowInfo.top + 278);
					Sleep(100);
					key.mouseClick();
					Sleep(100);
				}
				goods_pos = get_goods_pos_by_index(i);
				key.setMousePos(goods_pos.x, goods_pos.y);
				Sleep(100);
				key.mouseDoubleClick(100);
			}
		}
	}
}