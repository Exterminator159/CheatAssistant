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
	int ��ɴ��� = 0;
	bool is_received = false; //�����Ƿ��Ѿ�����
	int done_level = 0;//�������ɵȼ�
	//int received_level = 0;// ����ɽ��ܵȼ�
};
namespace task
{
	void traverseAllTaskInfo(DWORD & start_address, size_t & task_count);
	void traverseReceivedTaskInfo(DWORD & start_address, size_t & task_count);
	bool taskIsReceived(int task_id);
	TASK_STRUCT traverseTaskObject(DWORD ObjectPointer);
	bool taskIsJumpOver(DWORD task_address);
	bool taskIsReceived();
	void autoMasterTask();
};

