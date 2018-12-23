#pragma once
typedef struct _MAP_OBJECT_STRUCT
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
}MAP_OBJECT_STRUCT,*PMAP_OBJECT_STRUCT;

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
	bool findMonsterZ_AxisMoreThanThe40();
	bool blurryFindMonsterByString(std::wstring string);
	void sortByDistance(std::vector<MAP_OBJECT_STRUCT>& Objects);
	void follow(std::wstring name = L"");
	void ����_����ħ();
	void ����_������();
	BOOL getObjectInfoByObjectCode(PMAP_OBJECT_STRUCT object, int objectCode);
	bool getTheSpoils();
	DWORD getObjectPointerByCode(int code);
	void ����_����Ů��();
};
