#include "pch.h"
#include "function.h"



void function::remoteMainThreadCall(byte * shell_code, size_t shell_code_size, LPVOID param, size_t paramSize)
{
	/*int paramAddress = rw4.dwProcessBaseAddress + 1000;
	int callAddress = rw4.dwProcessBaseAddress + 1000 + (int)paramSize;*/
	int paramAddress = __CALL���� + 1000;
	int callAddress = __CALL��ַ + 1000 + (int)paramSize;
	if (param > 0 && paramSize > 0)
	{
		memory.writeVirtualMemory(paramAddress, param, paramSize);
	}
	memory.writeVirtualMemory(callAddress, shell_code, shell_code_size);
	utils::myprintf("paramAddress->:%x\ncallAddress->:%x", RED, paramAddress, callAddress);
	SendMessage(HWND_BROADCAST, MY_MESSAGE_ID, callAddress, 0);
}

//����
int function::decrypt(int address)
{
	int eax, esi, edx, i;
	eax = memory.read<int>(address);
	esi = memory.read<int>(__���ܻ�ַ);
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
//����
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
	OffsetParam = memory.read<int>(memory.read<int>(__���ܻ�ַ) + (EncryptId >> 16) * 4 + 36);
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
	return memory.read<int>(__��Ϸ״̬);
}
POS function::getCurrentRoomPos()
{
	POS CurrentRoomPos;
	if (getGameStatus() == 1)
	{
		CurrentRoomPos.x = memory.readOffset<int>(__����ȡֵ, { __������ƫ�� });
		CurrentRoomPos.y = memory.readOffset<int>(__����ȡֵ, { __С����ƫ�� });
	}
	else {
		DWORD OffsetAddress = memory.readOffset<int>(__������, { __ʱ���ַ ,__����ƫ�� });
		CurrentRoomPos.x = memory.read<int>(OffsetAddress + __��ǰ����X);
		CurrentRoomPos.y = memory.read<int>(OffsetAddress + __��ǰ����Y);
	}

	return CurrentRoomPos;
}

POS function::getBossRoomPos()
{
	POS BossRoomPos;
	DWORD OffsetAddress = memory.readOffset<int>(__������, { __ʱ���ַ ,__����ƫ�� });
	BossRoomPos.x = decrypt(OffsetAddress + __BOSS����X);
	BossRoomPos.y = decrypt(OffsetAddress + __BOSS����Y);
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
	if (decrypt(memory.readOffset<int>(__�����ַ, { __��ͼƫ�� }) + __����ƫ��) == 0)
	{
		return true;
	}
	else {
		return false;
	}
}