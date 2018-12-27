#pragma once
namespace function
{
	void remoteMainThreadCall(byte * opcodes, size_t opcodes_size, LPVOID param, size_t paramSize);
	int decrypt(int address);
	void encrypt(INT32 Address, INT32 Value);
	int getGameStatus();
	POS getCurrentRoomPos();
	POS getBossRoomPos();
	bool isBossRoom();
	bool isOpenDoor();
	void hookWindowMessage();
	void unHookWindowMessage();
	void chooseTheAppropriateMap(int taskId = 0);
	bool exception(int exceptionCode);
	bool passStoryFrame();
};

