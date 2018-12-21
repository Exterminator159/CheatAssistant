#pragma once
struct MAP_OBJECT_STRUCT
{
	DWORD address;
	std::wstring name;
	DWORD type;
	DWORD camp;
	DWORD health_point;
	DWORD code;
	int x;
	int y;
	int z;
};

namespace status_3
{
	void manage();
	void moveToNextRoom();
	DWORD getMapAddress();
	DWORD getMapStartAddress();
	int getMapObjectCount(DWORD map_start_address);
	void moveRoleToPos(int x, int y);
	MAP_OBJECT_STRUCT getObjectInfo(DWORD object_pointer);
	void outputMapObjectInfo();
	int getMonsterCount();
	void sortByDistance(std::vector<MAP_OBJECT_STRUCT>& Objects);
	void follow(std::wstring name = L"");
	bool getTheSpoils();
	DWORD getObjectPointerByCode(int code);
	void °´¼ü_ÆÆÏþÅ®Éñ();
};
