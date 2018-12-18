#include "pch.h"
#include "task.h"


#pragma once

 void task::traverseAllTaskInfo(DWORD &start_address, size_t &task_count)
{
	start_address = memory.readOffset<DWORD>((ULONG)__任务基址, { 104 });
	task_count = (memory.readOffset<size_t>(__任务基址, { 108 }) - (ULONG)start_address) / 4;
}

 void task::traverseReceivedTaskInfo(DWORD &start_address, DWORD &task_count)
{
	start_address = memory.readOffset<DWORD>((ULONG)__任务基址, { 8 });
	task_count = (memory.readOffset<DWORD>((ULONG)__任务基址, { 12 }) - start_address) / 12;
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
	}

	return task;
}


 bool task::taskIsJumpOver()
{
	 return true;
}

 bool task::taskIsReceived()
{
	 return true;
}

 void task::autoMasterTask()
{
	DWORD task_start_address;
	size_t task_count;
	TASK_STRUCT task;
	traverseAllTaskInfo(task_start_address, task_count);
	for (size_t i = 0; i < task_count; i++)
	{
		task = traverseTaskObject(memory.read<DWORD>(ULONG(task_start_address + i * 4)));

		if (
			task.copy_id > 0 &&
			task.完成次数 > 0 &&
			task.condition_type != L"[quest clear]"
			)
		{

		}
	}
}
