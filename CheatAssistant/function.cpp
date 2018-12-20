#include "pch.h"
#include "function.h"
#include "hook.h"

Hook messageHook;

void function::remoteMainThreadCall(byte * shell_code, size_t shell_code_size, LPVOID param, size_t paramSize)
{
	/*int paramAddress = rw4.dwProcessBaseAddress + 1000;
	int callAddress = rw4.dwProcessBaseAddress + 1000 + (int)paramSize;*/
	int paramAddress = __CALL参数;
	int callAddress = __CALL地址;
	if (param > 0 && paramSize > 0)
	{
		memory.writeVirtualMemory(paramAddress, param, paramSize);
	}
	if (memory.writeVirtualMemory(callAddress, shell_code, shell_code_size) == TRUE) {
		//SendMessageTimeout(g_hWnd, MY_MESSAGE_ID, callAddress, 0, SMTO_BLOCK, 3,NULL);
		SendMessage(g_hWnd, MY_MESSAGE_ID, callAddress, 0);
		/*if (param > 0 && paramSize > 0)
		{
			memory.writeVirtualMemory(callAddress, 0, paramSize);
		}
		memory.writeVirtualMemory(callAddress, 0, shell_code_size);*/
	}
	else {
		printf(VMProtectDecryptStringA("写内存地址失败\n"));
	}
}

//解密
int function::decrypt(int address)
{
	int eax, esi, edx, i;
	eax = memory.read<int>(address);
	esi = memory.read<int>(__解密基址);
	edx = eax >> 16;
	edx = memory.read<int>(esi + edx * 4 + 36);
	eax = eax & 65535;
	eax = memory.read<int>(edx + eax * 4 + 8468);
	edx = eax & 65535;
	esi = edx << 16;
	esi = esi | edx;
	i = memory.read<int>(address + 4);
	esi = esi ^ i;
	return esi;
}
//加密
void function::encrypt(INT32 Address, INT32 Value)
{
	INT32 EncryptId = 0;
	INT32 OffsetParam = 0;
	INT32 OffsetAddress = 0;
	INT32 Data = 0;
	INT32 AddressMask = 0;
	INT16 ax = 0;
	INT16 si = 0;
	EncryptId = memory.read<int>(Address);
	OffsetParam = memory.read<int>(memory.read<int>(__解密基址) + (EncryptId >> 16) * 4 + 36);
	OffsetAddress = OffsetParam + (EncryptId & 0xFFFF) * 4 + 8468;
	OffsetParam = memory.read<int>(OffsetAddress);
	Data = OffsetParam & 0xFFFF;
	Data += Data << 16;
	ax = OffsetParam & 0xFFFF;
	AddressMask = Address & 0xF;
	if (AddressMask == 0x0)
	{
		si = Value >> 16;
		si -= ax;
		si += Value;
	}
	else if (AddressMask == 0x4)
	{
		si = (Value & 0xFFFF) - (Value >> 16);
	}
	else if (AddressMask == 0x8)
	{
		si = Value >> 16;
		si *= Value;
	}
	else if (AddressMask == 0xC)
	{
		si = Value >> 16;
		si += Value;
		si += ax;
	}
	else
	{
		return;
	}
	ax ^= si;
	memory.write<BYTE>(OffsetAddress + 2, (BYTE)ax);
	memory.write<BYTE>(OffsetAddress + 3, (BYTE)(ax >> 8));
	memory.write<int>(Address + 4, Data ^ Value);
}

int function::getGameStatus()
{
	return memory.read<int>(__游戏状态);
}
POS function::getCurrentRoomPos()
{
	POS CurrentRoomPos;
	if (getGameStatus() == 1)
	{
		CurrentRoomPos.x = memory.readOffset<int>(__遍历取值, { __大区域偏移 });
		CurrentRoomPos.y = memory.readOffset<int>(__遍历取值, { __小区域偏移 });
	}
	else {
		DWORD OffsetAddress = memory.readOffset<int>(__房间编号, { __时间基址 ,__门型偏移 });
		CurrentRoomPos.x = memory.read<int>(OffsetAddress + __当前房间X);
		CurrentRoomPos.y = memory.read<int>(OffsetAddress + __当前房间Y);
	}

	return CurrentRoomPos;
}

POS function::getBossRoomPos()
{
	POS BossRoomPos;
	DWORD OffsetAddress = memory.readOffset<int>(__房间编号, { __时间基址 ,__门型偏移 });
	BossRoomPos.x = decrypt(OffsetAddress + __BOSS房间X);
	BossRoomPos.y = decrypt(OffsetAddress + __BOSS房间Y);
	return BossRoomPos;
}

bool function::isBossRoom()
{
	POS current_room_pos;
	POS boss_room_pos;

	current_room_pos = getCurrentRoomPos();
	boss_room_pos = getBossRoomPos();

	if (current_room_pos.x == boss_room_pos.x && current_room_pos.y == boss_room_pos.y)
	{
		return true;
	}
	return false;
}

bool function::isOpenDoor()
{
	if (decrypt(memory.readOffset<int>(__人物基址, { __地图偏移 }) + __开门偏移) == 0)
	{
		return true;
	}
	else {
		return false;
	}
}

void function::hookWindowMessage()
{
	int cross_core = (int)(DWORD_PTR)memory.getModuleHandleByModuleName(VMProtectDecryptStringW(L"cross_core.dll"));
	if (cross_core)
	{
		byte shell_code[] = {
			0x81,0x7d,0x0c,0x0,0x0,0x0,0x0,
			0x0f,0x85,0x0e,0x0,0x0,0x0,
			0x60,
			0x9c,
			0x8b,0x44,0x24,0x34,
			0xff,0xd0,
			0x9d,
			0x61,
			0x8b,0xe5,
			0x5d,
			0xc3,
			0x83,0xec,0x5c,
			0xa1,0x0,0x0,0x0,0x0,//33
			0xe9,0x0,0x0,0x0,0x0//38
		};

		*(int*)(shell_code + 3) = MY_MESSAGE_ID;
		*(int*)(shell_code + 31) = cross_core + 0x163A90;//
		*(int*)(shell_code + 36) = (cross_core + 0x5111E) - (sizeof(shell_code) - 5) - MESSAGE_HOOK_ADDRESS - 5;
		if (memory.writeVirtualMemory(MESSAGE_HOOK_ADDRESS, shell_code, sizeof(shell_code))) {
			/*byte jmp_shell_code[] = {
				0xe9,0x0,0x0,0x0,0x0,
				0x90,
				0x90,
				0x90,
			};

			*(int*)(jmp_shell_code + 1) = (MESSAGE_HOOK_ADDRESS)-(cross_core + 0x51116) - 5;

			memory.writeVirtualMemory((cross_core + 0x51116), jmp_shell_code, sizeof(jmp_shell_code));*/
			messageHook.jmpHook(cross_core + 0x51116, MESSAGE_HOOK_ADDRESS,7);
		}

	}
}

void function::unHookWindowMessage() 
{
	messageHook.unHook();
}

// 升级 自适应角色等级地图
int function::chooseTheAppropriateMapId() {

}