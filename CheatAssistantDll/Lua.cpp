#include "stdafx.h"
#include "Lua.h"


Lua::Lua()
{
	L = luaL_newstate();
	luaL_openlibs(L); //‘ÿ»ÎLuaª˘±æø‚

	registers(L);
}
Lua::~Lua()
{
	lua_close(L);
}
void Lua::registers(lua_State* m_L)
{
	/*lua_pushcfunction(m_L, getForegroundWindow);
	lua_setglobal(m_L,"getForegroundWindow");*/
	// memory
	lua_register(m_L, "readByte", readByte); // 
	lua_register(m_L, "readShort", readShort); // 
	lua_register(m_L, "readInteger", readInteger); // 
	lua_register(m_L, "readFloat", readFloat); // 
	lua_register(m_L, "readDouble", readDouble); // 
	lua_register(m_L, "writeByte", writeByte); // 
	lua_register(m_L, "writeShort", writeShort); // 
	lua_register(m_L, "writeInteger", writeInteger); // 
	lua_register(m_L, "writeFloat", writeFloat); // 
	lua_register(m_L, "writeDouble", writeDouble); // 
	// winapi
	lua_register(m_L, "findWindow", findWindow); // 
	lua_register(m_L, "getForegroundWindow", getForegroundWindow); // 
	lua_register(m_L, "setForegroundWindow", setForegroundWindow); // 
	
}
// memory
int Lua::readByte(lua_State* m_L)
{
	lua_pushinteger(m_L, read<byte>((DWORD_PTR)lua_tointeger(m_L, 1)));
	return 1;
}
int Lua::readShort(lua_State* m_L)
{
	lua_pushinteger(m_L, read<short>((DWORD_PTR)lua_tointeger(m_L, 1)));
	return 1;
}
int Lua::readInteger(lua_State* m_L)
{
	lua_pushinteger(m_L, read<int>((DWORD_PTR)lua_tointeger(m_L, 1)));
	return 1;
}
int Lua::readLong(lua_State* m_L)
{
	lua_pushinteger(m_L, read<LONGLONG>((DWORD_PTR)lua_tointeger(m_L, 1)));
	return 1;
}
int Lua::readFloat(lua_State* m_L)
{
	lua_pushnumber(m_L, read<float>((DWORD_PTR)lua_tonumber(m_L, 1)));
	return 1;
}
int Lua::readDouble(lua_State* m_L)
{
	lua_pushnumber(m_L, read<double>((DWORD_PTR)lua_tonumber(m_L, 1)));
	return 1;
}
int Lua::writeByte(lua_State* m_L)
{
	lua_pushboolean(m_L, write<byte>((DWORD_PTR)lua_tointeger(m_L, 1), (byte)lua_tointeger(m_L, 2)));
	return 1;
}
int Lua::writeShort(lua_State* m_L)
{
	lua_pushboolean(m_L, write<short>((DWORD_PTR)lua_tointeger(m_L, 1), (short)lua_tointeger(m_L, 2)));
	return 1;
}
int Lua::writeInteger(lua_State* m_L)
{
	lua_pushboolean(m_L, write<int>((DWORD_PTR)lua_tointeger(m_L, 1), (int)lua_tointeger(m_L, 2)));
	return 1;
}
int Lua::writeLong(lua_State* m_L)
{
	lua_pushboolean(m_L, write<LONGLONG>((DWORD_PTR)lua_tointeger(m_L, 1), (LONGLONG)lua_tonumber(m_L, 2)));
	return 1;
}
int Lua::writeFloat(lua_State* m_L)
{
	lua_pushboolean(m_L, write<float>((DWORD_PTR)lua_tointeger(m_L, 1), (float)lua_tonumber(m_L, 2)));
	return 1;
}
int Lua::writeDouble(lua_State* m_L)
{
	lua_pushboolean(m_L, write<double>((DWORD_PTR)lua_tointeger(m_L, 1), (double)lua_tonumber(m_L, 2)));
	return 1;
}
// winapi
int Lua::findWindow(lua_State* m_L)
{
	LPCSTR lpClassName = lua_tostring(m_L, 1) ? lua_tostring(m_L, 1) : "";
	LPCSTR lpWindowName = lua_tostring(m_L, 2) ? lua_tostring(m_L, 2) : "";
	HWND hWnd = FindWindowA(lpClassName, lpWindowName);
	if (hWnd == NULL)
	{
		lua_pushnil(m_L);
	}
	else {
		lua_pushinteger(m_L, (lua_Integer)hWnd);
	}
	return 1;
}
int Lua::getForegroundWindow(lua_State* m_L)
{
	lua_pushinteger(m_L, (lua_Integer)GetForegroundWindow());
	return 1;
}
int Lua::setForegroundWindow(lua_State* m_L)
{
	lua_pushboolean(m_L,SetForegroundWindow((HWND)lua_tointeger(m_L,1)));
	return 1;
}