#include "pch.h"
#include "call.h"
#include "function.h"
#include "role.h"

/*
__asm
{
	jn_call - 60                    - pushad 
	7FFC05E1- 9C                    - pushfd 
	7FFC05E2- B9 E001FC7F           - mov ecx,jn_struct { [600E0000] }
	7FFC05E7- B8 D0BB5002           - mov eax,dnf.exe+210BBD0 { [83EC8B55] }
	7FFC05EC- FF D0                 - call eax
	7FFC05EE- 9D                    - popfd 
	7FFC05EF- 61                    - popad 
	7FFC05F0- C3                    - ret 

}
*/
void call::����Call(int pointer, int code, int damage, int x, int y, int z)
{
	int skill_struct[26] = {};
	skill_struct[0] = pointer;//����ָ��;
	skill_struct[2] = code; //����
	skill_struct[3] = damage; //�˺�
	skill_struct[6] = x;//x
	skill_struct[7] = y;//y
	skill_struct[8] = z;//z
	skill_struct[22] = 0; //��С
	skill_struct[23] = 0;
	skill_struct[24] = 65535;
	skill_struct[25] = 65535;

	byte shell_code[] = {
		0x60,
		0x9c,
		0xb9,0x00,0x00,0x00,0x00,
		0xb8,0x00,0x00,0x00,0x00,
		0xff,0xd0,
		0x9d,
		0x61,
		0xc3
	};
	
	*(int*)(shell_code + 3) = __CALL����;
	*(int*)(shell_code + 8) = __����CALL;

	function::remoteMainThreadCall(shell_code, sizeof(shell_code), skill_struct, sizeof(skill_struct));

}

/*
__asm
{
	push z
	push y
	push x
	push �˺�
	push ����
	push ����ָ��
	mov edi, __�ͷ�CALL
	mov eax, edi
	call eax
	add esp, 24
}
*/
void call::�ͷ�Call(int pointer, int code, int damage, int x, int y, int z)
{
	byte shell_code[] = {
		0x68,0x00,0x00,0x00,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0xBF,0x00,0x00,0x00,0x00,
		0x8B,0xC7,
		0xFF,0xD0,
		0x83,0xC4,0x24,
		0xC3,
	};
	*(int*)(shell_code + 1) = z;
	*(int*)(shell_code + 6) = y;
	*(int*)(shell_code + 11) = x;
	*(int*)(shell_code + 16) = damage;
	*(int*)(shell_code + 21) = code;
	*(int*)(shell_code + 26) = pointer;
	*(int*)(shell_code + 31) = __�ͷ�CALL;
	function::remoteMainThreadCall(shell_code, sizeof(shell_code));
}
/*
__asm
{
	mov esi, object_pointer
	mov edi, dword ptr[esi]
	push z
	push y
	push x
	mov eax, dword ptr[edi + 0xb4]
	mov ecx, esi
	call eax
}
*/
void call::����Call(int pointer, int x, int y, int z)
{
	byte shell_code[] = {
		0xBE,0x00,0x00,0x00,0x00,
		0x8B,0x3E,
		0x68,0x00,0x00,0x00,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0x8B,0x87,0xB4,0x00,0x00,0x00,
		0x8B,0xCE,
		0xFF,0xD0,
		0xC3,
	};
	*(int*)(shell_code + 1) = pointer;
	*(int*)(shell_code + 8) = z;
	*(int*)(shell_code + 13) = y;
	*(int*)(shell_code + 18) = x;
	function::remoteMainThreadCall(shell_code, sizeof(shell_code));
}

/*
__asm {
	mov edx, copy_id
	mov ecx, ����ָ��
	mov eax, 0xf78
	push edx
	push eax
	call __����CALL
}
*/
void call::����Call(PCITY_INFO city_info, int copy_id)
{
	int ����ָ�� = memory.read<int>(__�������);
	byte shell_code[] = {
		0xBA,0x00,0x00,0x00,0x00,
		0xB9,0x00,0x00,0x00,0x00,
		0xB8,0x78,0x0F,0x00,0x00,
		0x52,
		0x50,
		0xE8,0xEA,0xFF,0x66,0xFF,
		0xC3,
	};
	*(int*)(shell_code + 1) = copy_id;
	*(int*)(shell_code + 6) = ����ָ��;
	*(int*)(shell_code + 19) = __����CALL;
	function::remoteMainThreadCall(shell_code, sizeof(shell_code));
	city_info->room.x = memory.read<int>(����ָ�� + __����ƫ��);
	city_info->room.y = memory.read<int>(����ָ�� + __����ƫ�� + 4);
	city_info->x = memory.read<int>(����ָ�� + __����ƫ�� + 8) + utils::createRandom(-2, 2);
	city_info->y = memory.read<int>(����ָ�� + __����ƫ�� + 12) + utils::createRandom(-2, 2);
}
/*
{
	mov ecx, __�̵��ַ
	mov ecx, dword ptr[ecx]
	mov ecx, dword ptr[ecx + 0x50]
	push 0
	push 0
	push 0
	push 0
	push 0
	push 37
	push 0xff0078ff
	push Buffer
	mov eax, __���ȹ���
	call eax
}
*/
void call::����Call(std::wstring buffer, int type, int color)
{
	byte shell_code[] = {
		0xB9,0x00,0x00,0x00,0x00,
		0x8B,0x09,
		0x8B,0x49,0x50,
		0x6A,0x00,
		0x6A,0x00,
		0x6A,0x00,
		0x6A,0x00,
		0x6A,0x00,
		0x6A,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0xB8,0x00,0x00,0x00,0x00,
		0xFF,0xD0,
		0xC3,
	};
	*(int*)(shell_code + 1) = __�̵��ַ;
	*(byte*)(shell_code + 21) = type;
	*(int*)(shell_code + 23) = color;
	*(int*)(shell_code + 28) = __CALL����;
	*(int*)(shell_code + 33) = __���ȹ���;
	utils::mywprintf(buffer.c_str());
	function::remoteMainThreadCall(shell_code, sizeof(shell_code), (LPVOID)buffer.c_str(), buffer.size()*3);
}

/*
__asm
{
	mov esi, �ƶ�ָ��
	mov eax, dword ptr ds : [esi]
	mov edx, dword ptr ds : [eax + __�ƶ�ƫ��_1]
	lea ecx, dword ptr ds : [0x400C00]
	push ecx
	mov ecx, esi
	call edx //call eax
	push Ŀ��y
	push Ŀ��x
	push �ƶ��ٶ�
	push 0x0
	sub esp, 0x8
	lea edx, dword ptr ds : [0x400C00]
	mov ecx, esp
	push edx
	call ������ջCALL
	mov esi, �ƶ�ָ��
	mov eax, dword ptr ds : [esi]
	mov edx, dword ptr ds : [eax + __�ƶ�ƫ��_2]
	lea ecx, dword ptr ds : [0x400C00]
	push ecx
	mov ecx, esi
	call edx
	sub esp, 0x8
	lea eax, dword ptr ds : [0x400C00]
	mov ecx, esp
	push eax
	call ������ջCALL
	push �ƶ�ָ��
	mov ecx, �ƶ�ָ��
	call �ƶ�CALL
}
*/
void call::�ƶ�Call(int pointer,int x,int y,int z) {
	ROLE_POS rolePos = role::getRolePos();
	int moveSpeed = abs(rolePos.x - x) + abs(rolePos.y - y);

	byte shell_code[] = {
		0xBE,0x00,0x00,0x00,0x00,		//mov esi, �ƶ�ָ��
		0x8B,0x06,						//mov eax, dword ptr ds : [esi]
		0x8B,0x10,						//
		0x8D,0x0D,0x00,0x00,0x00,0x00,
		0x51,
		0x8B,0xCE,
		0xFF,0xD2,
		0x68,0x00,0x00,0x00,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0x68,0x00,0x00,0x00,0x00,
		0x83,0xEC,0x08,
		0x8D,0x15,0x00,0x00,0x00,0x00,
		0x8B,0xCC,
		0x52,
		0xB8,0x00,0x00,0x00,0x00,
		0xFF,0xD0,
		0xBE,0x00,0x00,0x00,0x00,
		0x8B,0x06,
		0x8B,0x10,
		0x8D,0x0D,0x00,0x00,0x00,0x00,
		0x51,
		0x8B,0xCE,
		0xFF,0xD2,
		0x83,0xEC,0x08,
		0x8D,0x05,0x00,0x00,0x00,0x00,
		0x8B,0xCC,
		0x50,
		0xB8,0x00,0x00,0x00,0x00,
		0xFF,0xD0,
		0x68,0x00,0x00,0x00,0x00,
		0xB9,0x00,0x00,0x00,0x00,
		0xB8,0x00,0x00,0x00,0x00,
		0xFF,0xD0,
		0xC3
	};
}


void call::����Call(int taskId)
{

}

void call::���Call(int taskId)
{

}

void call::�ύCall(int taskId)
{

}

void call::����Call(int taskId)
{

}

void call::����Call(int taskId) {

}