#include "pch.h"
#include "role.h"
#include "function.h"


int role::getRoleLevel()
{
	return memory.read<int>(__��ɫ�ȼ�);
}
std::wstring role::getRoleJobName()
{
	return memory.readWString(memory.read<DWORD>(__ְҵ����) + 0x0, 100);
}
int role::getCurrentRoleFatigueValue()
{
	return function::decrypt(__���ƣ��) - function::decrypt(__��ǰƣ��);
}
ROLE_POS role::getRolePos()
{
	ROLE_POS RolePos;
	RolePos.room = function::getCurrentRoomPos();
	RolePos.x = (int)memory.read<float>(__��ɫ����);
	RolePos.y = (int)memory.read<float>(__��ɫ���� + 4);
	RolePos.z = (int)memory.read<float>(__��ɫ���� + 8);
	return RolePos;
}
int role::getRoleStatus()
{
	return memory.read<int>(memory.read<int>(__��ɫ״̬) + __��ɫ״̬ƫ��);
}
void role::releaseSkillByKey(int keyCode, int s)
{
	if (function::isOpenDoor() == false)
	{
		key.doKeyPress(keyCode, s);
		// �ͷż��ܵ���ʱ
		while (getRoleStatus() != 0)
		{
			Sleep(100);
		}
	}
}


void role::moveRoleToPos(ROLE_POS targetPos)
{
	// ʱ�����
	DWORD t1, t2 = utils::getTime();
	// ��Ϸ״̬
	int gameStatus = function::getGameStatus();
	utils::myprintf("gameStatus->%d", GREEN, gameStatus);
	// �����б�
	//std::map<const char*,bool> cardPointList;
	// λ�ñ���
	ROLE_POS currentPos, cardPointPos = getRolePos();
	utils::myprintf("Ŀ��λ�� ����x->:%d,����y->:%d | x->:%d,y->:%d", RED, targetPos.room.x, targetPos.room.y, targetPos.x, targetPos.y);
	while (true)
	{
		currentPos = getRolePos();
		t1 = utils::getTime();
		utils::myprintf("��ǰλ�� ����x->:%d,����y->:%d | x->:%d,y->:%d", YELLOW, currentPos.room.x, currentPos.room.y, currentPos.x, currentPos.y);
		if (
			currentPos.room.x != targetPos.room.x ||
			currentPos.room.y != targetPos.room.y ||
			(abs(currentPos.x - targetPos.x) < 50 && abs(currentPos.y - targetPos.y) < 30)
			)
		{
			key.upAllKey();//��ԭ���а���
			utils::myprintf("�ɹ�����ָ��λ��");
			break;
		}

		if ((currentPos.y - targetPos.y) >= 30 && key.getKeyState(VK_NUMPAD5) == 0)
		{
			key.keyDown(VK_NUMPAD5);
		}

		if ((targetPos.y - currentPos.y) >= 30 && key.getKeyState(VK_NUMPAD2) == 0)
		{
			key.keyDown(VK_NUMPAD2);
		}

		if ((currentPos.x - targetPos.x) >= 50 && key.getKeyState(VK_NUMPAD1) == 0)
		{
			printf("��\n");
			if (gameStatus == 3)
			{
				key.keyDown(VK_NUMPAD1);
				Sleep(100);
				key.keyUp(VK_NUMPAD1);
				Sleep(100);
				key.keyDown(VK_NUMPAD1);
			}
			else {
				key.keyDown(VK_NUMPAD1);
			}
		}

		if ((targetPos.x - currentPos.x) >= 50 && key.getKeyState(VK_NUMPAD3) == 0)
		{
			printf("��\n");
			if (gameStatus == 3)
			{
				key.keyDown(VK_NUMPAD3);
				Sleep(100);
				key.keyUp(VK_NUMPAD3);
				Sleep(100);
				key.keyDown(VK_NUMPAD3);
			}
			else {
				key.keyDown(VK_NUMPAD3);
			}
		}




		if (abs(currentPos.y - targetPos.y) < 30)
		{
			if (key.getKeyState(VK_NUMPAD5) == 1) {
				key.keyUp(VK_NUMPAD5);
				utils::myprintf("keyUp ��");
			}
			if (key.getKeyState(VK_NUMPAD2) == 1)
			{
				key.keyUp(VK_NUMPAD2);
				utils::myprintf("keyUp ��");
			}

		}

		if (abs(currentPos.x - targetPos.x) < 50)
		{
			if (key.getKeyState(VK_NUMPAD1) == 1) {
				key.keyUp(VK_NUMPAD1);
			}
			if (key.getKeyState(VK_NUMPAD3) == 1)
			{
				key.keyUp(VK_NUMPAD3);
			}
			utils::myprintf("keyUp ����");
		}

		// ���㴦��
		if ((t1 - t2) > 3)
		{
			t2 = utils::getTime();
			if (
				abs(currentPos.x - cardPointPos.x) < 3 &&
				abs(currentPos.y - cardPointPos.y) < 3
				)
			{

				if (key.getKeyState(VK_NUMPAD1) == 1)
				{
					key.keyUp(VK_NUMPAD1);
					key.doKeyPress(VK_NUMPAD3, 500);
				}

				if (key.getKeyState(VK_NUMPAD2) == 1)
				{
					key.keyUp(VK_NUMPAD2);
					key.doKeyPress(VK_NUMPAD5, 500);
				}

				if (key.getKeyState(VK_NUMPAD3) == 1)
				{
					key.keyUp(VK_NUMPAD3);
					key.doKeyPress(VK_NUMPAD1, 500);
				}

				if (key.getKeyState(VK_NUMPAD5) == 1)
				{
					key.keyUp(VK_NUMPAD5);
					key.doKeyPress(VK_NUMPAD2, 500);
				}
			}
			cardPointPos = getRolePos();
		}
	}
}