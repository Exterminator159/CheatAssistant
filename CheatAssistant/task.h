#pragma once
struct TASK_STRUCT
{
	DWORD address = 0;
	std::wstring name;
	DWORD type = 0;
	int copy_id = 0;
	int task_id = 0;
	int materials = 0;
	int task_length = 0;
	std::wstring condition_type;
	int 完成次数 = 0;
};
namespace task
{
	void traverseAllTaskInfo(DWORD & start_address, size_t & task_count);
	void traverseReceivedTaskInfo(DWORD & start_address, DWORD & task_count);
	TASK_STRUCT traverseTaskObject(DWORD ObjectPointer);
	bool taskIsJumpOver();
	bool taskIsReceived();
	void autoMasterTask();
};

