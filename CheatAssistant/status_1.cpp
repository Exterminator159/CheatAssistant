#include "pch.h"
#include "status_1.h"
#include "function.h"
#include "role.h"
#include "task.h"
#include "send_packet.h"
#include "knapsac.h"

void status_1::manage()
{

	if (role::getCurrentRoleFatigueValue() <= g_预留疲劳 && g_自动模式 != 练习)
	{
		returnToRole();
	}
	else {
		if (g_自动模式 == 搬砖)
		{
			enterIntoCopy(g_副本编号,1);
		}
		else if(g_自动模式 == 剧情) {
			task::autoMasterTask();
		}
		else if (g_自动模式 == 练习) {
			enterIntoCopy(g_副本编号, 1);
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
	utils::myprintf(VMProtectDecryptStringA("进入副本区域 副本ID %d"), PINK, copy_id);
	if (copy_id == 格蓝迪)
	{
		if (rolePos.room.x == 14 && rolePos.room.y == 2)
		{
			key.keyDown(VK_NUMPAD3);
			while (g_自动开关)
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
		SendPacket().城镇瞬移(rolePos, knapsac::getGoodsIndexByGoodsName(VMProtectDecryptStringW(L"瞬间移动药剂")));
		Sleep(1000);
	}
}
