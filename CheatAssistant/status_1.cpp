#include "pch.h"
#include "status_1.h"
#include "function.h"
#include "role.h"
#include "task.h"
#include "send_packet.h"
#include "knapsac.h"

void status_1::manage()
{

	if (role::getCurrentRoleFatigueValue() <= g_Ԥ��ƣ�� && g_�Զ�ģʽ != ��ϰ)
	{
		returnToRole();
	}
	else {
		if (g_�Զ�ģʽ == ��ש)
		{
			enterIntoCopy(g_�������,1);
		}
		else if(g_�Զ�ģʽ == ����) {
			task::autoMasterTask();
		}
		else if (g_�Զ�ģʽ == ��ϰ) {
			enterIntoCopy(g_�������, 1);
		}
	}
}

void status_1::returnToRole()
{
	while (function::getGameStatus() == 1)
	{
		key.doKeyPress(VK_ESCAPE);
		Sleep(1000);
		key.setMousePos(gameWindowInfo.left + 518, gameWindowInfo.top + 449);
		Sleep(1000);
		key.mouseClick();
		Sleep(3000);
	}
}

void status_1::enterIntoCopy(int copy_id,int model)
{
	ROLE_POS rolePos = role::getRolePos();
	POS room;
	utils::myprintf(VMProtectDecryptStringA("���븱������ ����ID %d"), PINK, copy_id);
	if (copy_id == ������)
	{
		if (rolePos.room.x == 14 && rolePos.room.y == 2)
		{
			key.keyDown(VK_NUMPAD3);
			while (g_�Զ�����)
			{
				if (function::getGameStatus() == 2)
				{
					key.keyUp(VK_NUMPAD3);
					return;
				}
				Sleep(500);
			}
		}
		else {
			room = {14,2};
			rolePos.room = room;
			rolePos.x = 705;
			rolePos.y = 288;
		}
	}
	utils::myprintf(VMProtectDecryptStringA("model %d rolePos.room.x %d rolePos.room.y %d rolePos.x %d rolePos.y %d"), PINK, model, rolePos.room.x , rolePos.room.y , rolePos.x , rolePos.y);
	if (model == 0)
	{
		role::moveRoleToPos(rolePos);
	}
	else if (model == 1) {
		SendPacket().����˲��(rolePos, knapsac::getGoodsIndexByGoodsName(VMProtectDecryptStringW(L"˲���ƶ�ҩ��")));
		Sleep(1000);
	}
}
