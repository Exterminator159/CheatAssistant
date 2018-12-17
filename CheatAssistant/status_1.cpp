#include "pch.h"
#include "status_1.h"
#include "function.h"
#include "role.h"

void status_1::manage()
{

	if (role::getCurrentRoleFatigueValue() <= g_预留疲劳 && g_自动模式 != 练习)
	{
		returnToRole();
	}
	else {
		if (g_自动模式 == 搬砖)
		{
			enterIntoCopy(g_副本编号);
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

void status_1::enterIntoCopy(int copy_id)
{
	ROLE_POS rolePos = role::getRolePos();
	if (copy_id == 格蓝迪)
	{
		if (rolePos.room.x == 14 && rolePos.room.y == 2)
		{
			key.keyDown(VK_NUMPAD3);
			while (true)
			{
				if (function::getGameStatus() == 2)
				{
					key.keyUp(VK_NUMPAD3);
					break;
				}
				Sleep(500);
			}
		}
		else {
			rolePos.room.x = 14;
			rolePos.room.x = 2;
			rolePos.x = 705;
			rolePos.y = 288;
			role::moveRoleToPos(rolePos);
		}
	}
}
