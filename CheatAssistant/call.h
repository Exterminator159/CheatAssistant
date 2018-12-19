#pragma once
namespace call
{
	void 技能Call(int pointer, int code, int damage, int x, int y, int z);
	void 释放Call(int pointer, int code, int damage, int x, int y, int z);
	void 坐标Call(int pointer, int x, int y, int z);
	void 区域Call(PCITY_INFO city_info, int copy_id);
	void 公告Call(std::wstring buffer, int type = 37, int color = 0xff0078ff);
	void 移动Call(int pointer, int x, int y, int z = 0);
	void 接受Call(int taskId);
	void 完成Call(int taskId);
	void 提交Call(int taskId);
	void 放弃Call(int taskId);
	void 跳过Call(int taskId); 
};

