#include "pch.h"
#include "task.h"
#include "role.h"
#include "call.h"
#include "function.h"

// 遍历所有任务
 void task::traverseAllTaskInfo(DWORD &start_address, size_t &task_count)
{
	start_address = memory.readOffset<DWORD>(__任务基址, { 104 });
	task_count = (memory.readOffset<size_t>(__任务基址, { 108 }) - start_address) / 4;
}
 // 遍历已接任务
 void task::traverseReceivedTaskInfo(DWORD &start_address, size_t &task_count)
{
	start_address = memory.readOffset<DWORD>(__任务基址, { 8 });
	task_count = (memory.readOffset<size_t>(__任务基址, { 12 }) - start_address) / 12;
}

 bool task::taskIsReceived(int task_id) {
	 DWORD task_start_address;
	 size_t task_count;
	 TASK_STRUCT task;
	 traverseReceivedTaskInfo(task_start_address, task_count);
	 for (size_t i = 0; i < task_count; i++)
	 {
		 if (memory.read<int>(memory.read<DWORD>(task_start_address + i * 12)) == task_id)
		 {
			 return true;
		 }
	 }
	 return false;
 }


 TASK_STRUCT task::traverseTaskObject(DWORD ObjectPointer)
{
	TASK_STRUCT task;
	if (ObjectPointer != 0)
	{
		task.address = ObjectPointer;
		task.task_id = memory.read<int>(ObjectPointer);
		task.type = memory.read<DWORD>(ObjectPointer + 308);
		task.copy_id = memory.read<int>(memory.read<DWORD>(ObjectPointer + 0x2B8));
		task.materials = memory.read<int>(ObjectPointer + 1428); //材料
		task.task_length = memory.read<int>(ObjectPointer + 28);
		task.condition_type = memory.readWString(memory.read<DWORD>(ObjectPointer + 720), 100);
		if (task.task_length > 7)
		{
			task.name = memory.readWString(memory.read<DWORD>(ObjectPointer + 8), 100);
		}
		else {

			task.name = memory.readWString(ObjectPointer + 8, 100);
		}
		task.done_level = memory.read<int>(ObjectPointer + 0x1c4);
		task.is_received = taskIsReceived(task.task_id);
	}

	return task;
}

 void task::autoMasterTask()
{
	DWORD task_start_address;
	size_t task_count;
	TASK_STRUCT task;
	traverseAllTaskInfo(task_start_address, task_count);
	for (size_t i = 0; i < task_count; i++)
	{
		task = traverseTaskObject(memory.read<DWORD>(task_start_address + i * 4));
		if (task.type != 0)
		{
			continue;
		}
		if (task.is_received == false)
		{
			call::接受Call(task.task_id);
			Sleep(1000);
			return;
		}

		if (task.copy_id > 0)
		{

		}
		else if (task.done_level < role::getRoleLevel()) {
			call::跳过Call(task.task_id);
			Sleep(1000);
			return;
		}
		else {
			function::chooseTheAppropriateMapId();
		}
	}
}
