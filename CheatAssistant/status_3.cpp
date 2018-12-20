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
		utils::myprintf(VMProtectDecryptStringA("���ѿ�"));
		if (getTheSpoils() == true)
		{
			return;
		}
		utils::myprintf(VMProtectDecryptStringA("��Ʒʰȡ���"));
		if (function::isBossRoom() == true && getMonsterCount() == 0)
		{
			switch (g_�Զ�ģʽ)
			{
			case ��ϰ:
				while (true)
				{
					if (gameStatus != function::getGameStatus() || function::isBossRoom() == false)
					{
						g_ˢͼ����++;
						g_��ͼʱ�� = utils::getTime() - g_��ͼʱ��;
						g_��ͼ��� = true;
						utils::mywprintf(VMProtectDecryptStringW(L"��ϰ�� %d �� ��ʱ %d s "), CYAN, g_ˢͼ����, (int)(g_��ͼʱ�� / 1000));
						Sleep(1000);
						break;
					}
					key.doKeyPress(VK_F10);
					Sleep(1000);
				}
				break;
			case ��ש:
				while (true)
				{
					if (getObjectPointerByCode(Code_ͨ��Ӫ��) == NULL)
					{
						Sleep(2000);
						key.doKeyPress(VK_ESCAPE);
						continue;
					}
					//��������();
					knapsac::keyPadSellThings();
					key.doKeyPress(VK_ESCAPE);
					while (true)
					{
						if (gameStatus != function::getGameStatus() || function::isBossRoom() == false)
						{
							g_ˢͼ����++;
							g_��ͼʱ�� = utils::getTime() - g_��ͼʱ��;
							g_��ͼ��� = true;
							utils::mywprintf(VMProtectDecryptStringW(L"��ש�� %d �� ��ʱ %d �� "), CYAN, g_ˢͼ����, (int)(g_��ͼʱ�� / 1000));
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
			case ����:

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
		utils::myprintf(VMProtectDecryptStringA("��ʼ���"));
		if (g_��ͼ��� == true)
		{
			g_��ͼʱ�� = utils::getTime();
			g_��ͼ��� = false;
		}

		std::wstring role_job_name = role::getRoleJobName();
		if (wcscmp(role_job_name.c_str(), VMProtectDecryptStringW(L"����Ů��")) == 0)
		{
			����_����Ů��();
		}
		/*else if (wcscmp(role_job_name.c_str(), L"��Ѫ߱��") == 0) {
			����_��Ѫ߱��();
		}
		else if (wcscmp(role_job_name.c_str(), L"���") == 0) {
			����_���();
		}
		else if (wcscmp(role_job_name.c_str(), L"����") == 0) {
			����_����();
		}
		else if (wcscmp(role_job_name.c_str(), L"����") == 0) {
			����_����();
		}*/
	}
}



void status_3::moveToNextRoom()
{
	DWORD temp_data;
	DWORD coordinate_struct;
	ROLE_POS rolePos;
	AStarMapInfo map_info;
	int direction = getDirection(1);//GetDirection(1);//�¸����䷴��
	//utils::myprintf("direction->:%x", RED, direction);
	int x, y, xf, yf, cx, cy = 0;
	temp_data = memory.read<DWORD>(__�̵��ַ - 8);
	temp_data = memory.read<DWORD>(temp_data + __ʱ���ַ);
	temp_data = memory.read<DWORD>(temp_data + __����ṹƫ��1);
	coordinate_struct = temp_data + (direction + direction * 8) * 4 + __����ṹƫ��2 + (direction * 4);
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
	//utils::myprintf("������ x->:%d,y->:%d",YELLOW, cx, cy);
	//utils::myprintf("������ rolePos.x->:%d,rolePos.y->:%d", YELLOW, rolePos.x, rolePos.y);
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

	return memory.readOffset<int>(__�����ַ, { __��ͼƫ�� });
}

DWORD status_3::getMapStartAddress()
{
	return  memory.read<int>(getMapAddress() + __�׵�ַ);
}

int status_3::getMapObjectCount(DWORD map_start_address)
{
	return  (memory.read<int>(getMapAddress() + __β��ַ) - map_start_address) / 4;
}
// ��ȡ������Ϣ
MAP_OBJECT_STRUCT status_3::getObjectInfo(DWORD object_pointer)
{
	MAP_OBJECT_STRUCT object;
	DWORD pos_pointer;
	object.address = object_pointer;
	object.type = memory.read<DWORD>(object_pointer + __����ƫ��);
	object.camp = memory.read<DWORD>(object_pointer + __��Ӫƫ��);
	object.health_point = memory.read<DWORD>(object_pointer + __Ѫ��ƫ��);
	object.code = memory.read<DWORD>(object_pointer + __����ƫ��);
	if (object.type == 289 && object.camp == 200)
	{
		object.name = memory.readWString(memory.read<DWORD>(memory.read<DWORD>(object_pointer + __������Ʒ����ƫ��) + 0x24) + 0, 100);
	}
	else {
		object.name = memory.readWString(memory.read<DWORD>(object_pointer + __����ƫ��), 100);
	}
	if (object.type == 273)
	{
		pos_pointer = memory.read<int>(object_pointer + __��������ƫ��);
		object.x = (int)memory.read<float>(__��ɫ���� + 0);
		object.y = (int)memory.read<float>(__��ɫ���� + 4);
		object.z = (int)memory.read<float>(__��ɫ���� + 8);
	}
	else {
		pos_pointer = memory.read<int>(object_pointer + __����ƫ��);
		object.x = (int)memory.read<float>(pos_pointer + 0x10);
		object.y = (int)memory.read<float>(pos_pointer + 0x14);
		object.z = (int)memory.read<float>(pos_pointer + 0x18);
	}
	return object;
}
// ��ӡ����������Ϣ
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
// ��ȡ�����ڹ�������
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
// ����ɫ�����������
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
// ����
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
				//�ƶ�����ɫָ��λ��(object.x + createRandom(-10, 10) + 200, object.y + createRandom(-10, 10));
				key.doKeyPress(VK_NUMPAD1);
			}
			else {
				//�ƶ�����ɫָ��λ��(object.x + createRandom(-10, 10) - 200, object.y + createRandom(-10, 10));
				key.doKeyPress(VK_NUMPAD3);
			}
			Sleep(200);
			break;
		}
	}
}
// ��ȡս��Ʒ
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
		if (object.code == Code_���� || object.code == Code_��� || object.code == Code_�ɳ�֮Ȫˮ)
			continue;
		if (
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"�鲼Ƭ")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"���¼�Ӳ����")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"���¼���ʯ")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"�绯�����")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"����Ƭ")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"�������Ƭ")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"�ƾɵ�Ƥ��")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"��ʧ��ʥ����")) == 0
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
			if (wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"���")) != 0)
			{
				key.doKeyPress(VK_X);
				Sleep(100);
			}
			return true;
		}
	}
	return false;
}

// ��ȡͨ���̵� Ӫ��
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

void status_3::����_����Ů��()
{
	POS currentRoom = function::getCurrentRoomPos();
	ROLE_POS rolePos;
	//DWORD ����ID = read<int>(__ͼ�ڸ���ID);
	if (g_������� == ������)
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
			//�ƶ�����ɫָ��λ��(521, 200);
			Sleep(300);
			key.doKeyPress(VK_NUMPAD1);
			Sleep(100);
			role::releaseSkillByKey(VK_R);
		}
		else if (currentRoom.x == 2 && currentRoom.y == 2) {
			rolePos.x = 331;
			rolePos.y = 329;
			role::moveRoleToPos(rolePos);
			//�ƶ�����ɫָ��λ��(331, 329);
			Sleep(200);
			key.doKeyPress(VK_NUMPAD3);
			role::releaseSkillByKey(VK_A);
			rolePos.x = 611;
			rolePos.y = 201;
			role::moveRoleToPos(rolePos);
			//�ƶ�����ɫָ��λ��(611, 201);
			Sleep(300);
			role::releaseSkillByKey(VK_T);
			Sleep(300);
			follow(VMProtectDecryptStringW(L"���˲�ͼ��"));
			role::releaseSkillByKey(VK_Q);
		}
		else if (currentRoom.x == 3 && currentRoom.y == 2) {
			rolePos.x = 343;
			rolePos.y = 290;
			role::moveRoleToPos(rolePos);
			//�ƶ�����ɫָ��λ��(343, 290);
			Sleep(300);
			role::releaseSkillByKey(VK_A, 300);
		}
		else if (currentRoom.x == 3 && currentRoom.y == 1) {
			key.doKeyPress(VK_NUMPAD3);
			/*�ƶ�����ɫָ��λ��(333, 216);
			�����ͷż���(VK_H);
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
			if (memory.read<int>(__�Ի���ַ) == 1)
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
				g_�Զ����� = false;
				return;
			}
			i++;
		}
	}
}