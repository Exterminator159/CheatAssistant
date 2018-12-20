#include "pch.h"
#include "function.h"
#include "status_3.h"
#include "role.h"
#include "astar.hpp"
#include "knapsac.h"



void status_3::manage()
{
	int gameStatus = function::getGameStatus();
	if (function::isOpenDoor() && getMonsterCount() == 0)
	{
		utils::myprintf(VMProtectDecryptStringA("门已开"));
		if (getTheSpoils() == true)
		{
			return;
		}
		utils::myprintf(VMProtectDecryptStringA("物品拾取完毕"));
		if (function::isBossRoom() == true && getMonsterCount() == 0)
		{
			switch (g_自动模式)
			{
			case 练习:
				while (true)
				{
					if (gameStatus != function::getGameStatus() || function::isBossRoom() == false)
					{
						g_刷图次数++;
						g_过图时间 = utils::getTime() - g_过图时间;
						g_首图标记 = true;
						utils::mywprintf(VMProtectDecryptStringW(L"练习第 %d 次 耗时 %d s "), CYAN, g_刷图次数, (int)(g_过图时间 / 1000));
						Sleep(1000);
						break;
					}
					key.doKeyPress(VK_F10);
					Sleep(1000);
				}
				break;
			case 搬砖:
				while (true)
				{
					if (getObjectPointerByCode(Code_通关营火) == NULL)
					{
						Sleep(2000);
						key.doKeyPress(VK_ESCAPE);
						continue;
					}
					//按键卖物();
					knapsac::keyPadSellThings();
					key.doKeyPress(VK_ESCAPE);
					while (true)
					{
						if (gameStatus != function::getGameStatus() || function::isBossRoom() == false)
						{
							g_刷图次数++;
							g_过图时间 = utils::getTime() - g_过图时间;
							g_首图标记 = true;
							utils::mywprintf(VMProtectDecryptStringW(L"搬砖第 %d 次 耗时 %d 秒 "), CYAN, g_刷图次数, (int)(g_过图时间 / 1000));
							Sleep(1000);
							break;
						}
						if (role::getCurrentRoleFatigueValue() <= 0) {
							key.doKeyPress(VK_F12);
						}
						else {
							key.doKeyPress(VK_F10);
						}
						Sleep(1000);
					}
					break;
				}
				break;
			case 剧情:

				break;
			default:
				break;
			}
		}
		else {
			moveToNextRoom();
		}
	}
	else {
		utils::myprintf(VMProtectDecryptStringA("开始打怪"));
		if (g_首图标记 == true)
		{
			g_过图时间 = utils::getTime();
			g_首图标记 = false;
		}

		std::wstring role_job_name = role::getRoleJobName();
		if (wcscmp(role_job_name.c_str(), VMProtectDecryptStringW(L"破晓女神")) == 0)
		{
			按键_破晓女神();
		}
		/*else if (wcscmp(role_job_name.c_str(), L"帝血弑天") == 0) {
			按键_帝血弑天();
		}
		else if (wcscmp(role_job_name.c_str(), L"天帝") == 0) {
			按键_天帝();
		}
		else if (wcscmp(role_job_name.c_str(), L"剑神") == 0) {
			按键_剑神();
		}
		else if (wcscmp(role_job_name.c_str(), L"风神") == 0) {
			按键_风神();
		}*/
	}
}



void status_3::moveToNextRoom()
{
	DWORD temp_data;
	DWORD coordinate_struct;
	ROLE_POS rolePos;
	AStarMapInfo map_info;
	int direction = getDirection(1);//GetDirection(1);//下个房间反向
	//utils::myprintf("direction->:%x", RED, direction);
	int x, y, xf, yf, cx, cy = 0;
	temp_data = memory.read<DWORD>(__商店基址 - 8);
	temp_data = memory.read<DWORD>(temp_data + __时间基址);
	temp_data = memory.read<DWORD>(temp_data + __坐标结构偏移1);
	coordinate_struct = temp_data + (direction + direction * 8) * 4 + __坐标结构偏移2 + (direction * 4);
	//utils::myprintf("coordinate_struct->:%x",RED, coordinate_struct);
	x = memory.read<int>(coordinate_struct + 0x0);
	y = memory.read<int>(coordinate_struct + 0x4);
	xf = memory.read<int>(coordinate_struct + 0x8);
	yf = memory.read<int>(coordinate_struct + 0xc);
	if (direction == 0)
	{
		cx = x + xf + 20;
		cy = y + yf / 2;
	}
	else if (direction == 1)
	{
		cx = x - 20;
		cy = y + yf / 2;
	}
	else if (direction == 2)
	{
		cx = x + xf / 2;
		cy = y + yf + 20;
	}
	else if (direction == 3)
	{
		cx = x + xf / 2;
		cy = y - 20;
	}
	Sleep(200);
	rolePos = role::getRolePos();
	rolePos.x = cx;
	rolePos.y = cy;
	//utils::myprintf("门坐标 x->:%d,y->:%d",YELLOW, cx, cy);
	//utils::myprintf("门坐标 rolePos.x->:%d,rolePos.y->:%d", YELLOW, rolePos.x, rolePos.y);
	//Sleep(1000);
	role::moveRoleToPos(rolePos);
	if (direction == 0) {
		key.doKeyPress(VK_NUMPAD1, 500);
	}
	else if (direction == 1) {
		key.doKeyPress(VK_NUMPAD3, 500);
	}
	else if (direction == 2)
	{
		key.doKeyPress(VK_NUMPAD5, 500);
	}
	else if (direction == 3) {
		key.doKeyPress(VK_NUMPAD2, 500);
	}
}

DWORD status_3::getMapAddress()
{

	return memory.readOffset<int>(__人物基址, { __地图偏移 });
}

DWORD status_3::getMapStartAddress()
{
	return  memory.read<int>(getMapAddress() + __首地址);
}

int status_3::getMapObjectCount(DWORD map_start_address)
{
	return  (memory.read<int>(getMapAddress() + __尾地址) - map_start_address) / 4;
}
// 获取对象信息
MAP_OBJECT_STRUCT status_3::getObjectInfo(DWORD object_pointer)
{
	MAP_OBJECT_STRUCT object;
	DWORD pos_pointer;
	object.address = object_pointer;
	object.type = memory.read<DWORD>(object_pointer + __类型偏移);
	object.camp = memory.read<DWORD>(object_pointer + __阵营偏移);
	object.health_point = memory.read<DWORD>(object_pointer + __血量偏移);
	object.code = memory.read<DWORD>(object_pointer + __代码偏移);
	if (object.type == 289 && object.camp == 200)
	{
		object.name = memory.readWString(memory.read<DWORD>(memory.read<DWORD>(object_pointer + __地面物品名称偏移) + 0x24) + 0, 100);
	}
	else {
		object.name = memory.readWString(memory.read<DWORD>(object_pointer + __名称偏移), 100);
	}
	if (object.type == 273)
	{
		pos_pointer = memory.read<int>(object_pointer + __人物坐标偏移);
		object.x = (int)memory.read<float>(__角色坐标 + 0);
		object.y = (int)memory.read<float>(__角色坐标 + 4);
		object.z = (int)memory.read<float>(__角色坐标 + 8);
	}
	else {
		pos_pointer = memory.read<int>(object_pointer + __坐标偏移);
		object.x = (int)memory.read<float>(pos_pointer + 0x10);
		object.y = (int)memory.read<float>(pos_pointer + 0x14);
		object.z = (int)memory.read<float>(pos_pointer + 0x18);
	}
	return object;
}
// 打印副本对象信息
void status_3::outputMapObjectInfo()
{
	DWORD mapStartAddress = getMapStartAddress();
	utils::myprintf(VMProtectDecryptStringA("map_start_address %x\n"), RED, mapStartAddress);
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	utils::myprintf(VMProtectDecryptStringA("map_object_count %d\n"), RED, mapObjectCount);
	MAP_OBJECT_STRUCT _ObjectInfo;
	DWORD objectAddress;
	for (size_t i = 0; i < mapObjectCount; i++)
	{
		objectAddress = memory.read<int>((ULONG)(mapStartAddress + i * 4));
		if (objectAddress <= 0)continue;
		_ObjectInfo = getObjectInfo(objectAddress);
		utils::myprintf(VMProtectDecryptStringA("address 0x%x"), RED, _ObjectInfo.address);
		utils::myprintf(VMProtectDecryptStringA("code %d"), RED, _ObjectInfo.code);
		utils::myprintf(VMProtectDecryptStringA("type %d"), RED, _ObjectInfo.type);
		utils::myprintf(VMProtectDecryptStringA("camp %d"), RED, _ObjectInfo.camp);
		utils::myprintf(VMProtectDecryptStringA("health_point %d"), RED, _ObjectInfo.health_point);
		utils::myprintf(VMProtectDecryptStringA("pos %d,%d,%d"), RED, _ObjectInfo.x, _ObjectInfo.y, _ObjectInfo.z);
		utils::mywprintf(VMProtectDecryptStringW(L"name %s"), RED, _ObjectInfo.name.c_str());
		utils::myprintf(VMProtectDecryptStringA("====================================="));
	}
}
// 获取副本内怪物数量
int status_3::getMonsterCount()
{
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	DWORD objectAddress;
	int monsterCount = 0;
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<DWORD>((ULONG)(mapStartAddress + i * 4));
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (object.code == 258 || object.code == 818 || object.code == 63821)
		{
			continue;
		}
		if (object.type == 529 || object.type == 273 || object.type == 545)
		{
			if (object.camp > 0)
			{
				if (object.health_point > 0 || object.code == 8104 || object.code == 817)
				{
					monsterCount++;
				}
			}
		}

	}
	return monsterCount;
}
// 按角色最近距离排序
void status_3::sortByDistance(std::vector<MAP_OBJECT_STRUCT> &Objects)
{
	MAP_OBJECT_STRUCT temp_var;
	ROLE_POS RolePos = role::getRolePos();
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (size_t j = 0; j < Objects.size() - i; j++)
		{
			if (abs(Objects[j].x - RolePos.x) + abs(Objects[j].y - RolePos.y) > abs(Objects[j + 1].x - RolePos.x) + abs(Objects[j + 1].y - RolePos.y))
			{
				temp_var = Objects[j];
				Objects[j + 1] = Objects[j];
				Objects[j] = temp_var;
			}
		}
	}
}
// 跟随
void status_3::follow(std::wstring name)
{
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	MAP_OBJECT_STRUCT object;
	ROLE_POS rolePos = role::getRolePos();
	DWORD objectAddress;
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<int>((ULONG)(mapStartAddress + i * 4));
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (object.code == 258 || object.code == 818 || object.code == 63821)
			continue;
		if (!(object.health_point > 0 || object.code == 8104 || object.code == 817))
			continue;
		if (!name.empty() && wcscmp(object.name.c_str(), name.c_str()) != 0)
			continue;
		if (!(object.type == 529 || object.type == 273 || object.type == 545))
			continue;
		if (!(object.camp > 0))
			continue;
		if (rolePos.x > object.x)
			key.doKeyPress(VK_NUMPAD1);
		if (rolePos.x < object.x)
			key.doKeyPress(VK_NUMPAD3);
		Sleep(200);
		if (abs(rolePos.x - object.x) > 200 || abs(rolePos.y - object.y) > 50)
		{
			if (rolePos.x > object.x)
			{
				//移动到角色指定位置(object.x + createRandom(-10, 10) + 200, object.y + createRandom(-10, 10));
				key.doKeyPress(VK_NUMPAD1);
			}
			else {
				//移动到角色指定位置(object.x + createRandom(-10, 10) - 200, object.y + createRandom(-10, 10));
				key.doKeyPress(VK_NUMPAD3);
			}
			Sleep(200);
			break;
		}
	}
}
// 获取战利品
bool status_3::getTheSpoils() {
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	DWORD objectAddress;
	ROLE_POS rolePos = role::getRolePos();
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<DWORD>((ULONG)(mapStartAddress + i * 4));
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (object.code == Code_鸡腿 || object.code == Code_肉块 || object.code == Code_成长之泉水)
			continue;
		if (
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"碎布片")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"最下级硬化剂")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"最下级砥石")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"风化的碎骨")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"钢铁片")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"生锈的铁片")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"破旧的皮革")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"丢失的圣诞袜")) == 0
			)
			continue;

		if (object.type == 289 && object.camp == 200)
		{
			if (object.z > 0)
			{
				Sleep(1000);
				return true;
			}
			if (abs(rolePos.x - object.x) > 2 || abs(rolePos.y - object.y) > 2)
			{
				rolePos.x = object.x;
				rolePos.y = object.y;
				role::moveRoleToPos(rolePos);
			}
			if (wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"金币")) != 0)
			{
				key.doKeyPress(VK_X);
				Sleep(100);
			}
			return true;
		}
	}
	return false;
}

// 获取通关商店 营火
DWORD status_3::getObjectPointerByCode(int code)
{
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	MAP_OBJECT_STRUCT object;
	DWORD objectAddress;
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<int>(ULONG(mapStartAddress + i * 4));
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (object.code == code)
		{
			return objectAddress;
		}
	}
	return NULL;
}

void status_3::按键_破晓女神()
{
	POS currentRoom = function::getCurrentRoomPos();
	ROLE_POS rolePos;
	//DWORD 副本ID = read<int>(__图内副本ID);
	if (g_副本编号 == 格蓝迪)
	{
		if (currentRoom.x == 0 && currentRoom.y == 0)
		{
			Sleep(1000);
			role::releaseSkillByKey(VK_F);
			rolePos.x = 468;
			rolePos.y = 239;
			role::moveRoleToPos(rolePos);
			Sleep(300);
			role::releaseSkillByKey(VK_G);
		}
		else if (currentRoom.x == 1 && currentRoom.y == 0) {
			Sleep(500);
			key.doKeyPress(VK_Y);
			Sleep(3000);
		}
		else if (currentRoom.x == 2 && currentRoom.y == 0) {
			rolePos.x = 582;
			rolePos.y = 241;
			role::moveRoleToPos(rolePos);
			Sleep(300);
			role::releaseSkillByKey(VK_A, 300);
		}
		else if (currentRoom.x == 2 && currentRoom.y == 1) {
			rolePos.x = 521;
			rolePos.y = 200;
			role::moveRoleToPos(rolePos);
			//移动到角色指定位置(521, 200);
			Sleep(300);
			key.doKeyPress(VK_NUMPAD1);
			Sleep(100);
			role::releaseSkillByKey(VK_R);
		}
		else if (currentRoom.x == 2 && currentRoom.y == 2) {
			rolePos.x = 331;
			rolePos.y = 329;
			role::moveRoleToPos(rolePos);
			//移动到角色指定位置(331, 329);
			Sleep(200);
			key.doKeyPress(VK_NUMPAD3);
			role::releaseSkillByKey(VK_A);
			rolePos.x = 611;
			rolePos.y = 201;
			role::moveRoleToPos(rolePos);
			//移动到角色指定位置(611, 201);
			Sleep(300);
			role::releaseSkillByKey(VK_T);
			Sleep(300);
			follow(VMProtectDecryptStringW(L"巨人波图拉"));
			role::releaseSkillByKey(VK_Q);
		}
		else if (currentRoom.x == 3 && currentRoom.y == 2) {
			rolePos.x = 343;
			rolePos.y = 290;
			role::moveRoleToPos(rolePos);
			//移动到角色指定位置(343, 290);
			Sleep(300);
			role::releaseSkillByKey(VK_A, 300);
		}
		else if (currentRoom.x == 3 && currentRoom.y == 1) {
			key.doKeyPress(VK_NUMPAD3);
			/*移动到角色指定位置(333, 216);
			按键释放技能(VK_H);
			if (is_open_door() == true)
			{
				return;
			}*/
			key.doKeyPress(VK_W);
			Sleep(4000);
		}
		if (function::isOpenDoor() == true)
		{

			return;
		}
		follow();
		role::releaseSkillByKey(VK_S);
		if (function::isOpenDoor() == true)
		{
			return;
		}
		follow();
		role::releaseSkillByKey(VK_E);
		if (function::isOpenDoor() == true)
		{
			return;
		}
		follow();
		role::releaseSkillByKey(VK_G);
		if (function::isOpenDoor() == true)
		{
			return;
		}
		follow();
		role::releaseSkillByKey(VK_H);
		if (function::isOpenDoor() == true)
		{
			return;
		}
		follow();
		role::releaseSkillByKey(VK_D);
		if (function::isOpenDoor() == true)
		{
			return;
		}
		follow();
		role::releaseSkillByKey(VK_S);
		if (function::isOpenDoor() == true)
		{
			return;
		}
		int i = 0;
		while (function::isOpenDoor() == false)
		{
			if (memory.read<int>(__对话基址) == 1)
			{
				key.doKeyPress(VK_RETURN);
				continue;
			}
			follow();
			key.doKeyPress(VK_X, 1500);
			if (i > 3)
			{
				follow();
				role::releaseSkillByKey(VK_S, 1500);
			}
			if (i > 20)
			{
				follow();
				role::releaseSkillByKey(VK_G);
			}
			if (i > 50) {
				g_自动开关 = false;
				return;
			}
			i++;
		}
	}
}