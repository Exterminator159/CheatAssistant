#include "Lua.h"

//Memory<Kca> mem;

Lua::Lua()
{
	L = luaL_newstate();
	luaL_openlibs(L); //‘ÿ»ÎLuaª˘±æø‚
	//lua_register(L, "readByte", readByte); // 
	//lua_register(L, "readShort", readShort); // 
	//lua_register(L, "readInteger", readInteger); // 
	//lua_register(L, "readFloat", readFloat); // 
	//lua_register(L, "readDouble", readDouble); // 
	////lua_register(L, "readString", readString); // 
	//lua_register(L, "writeByte", writeByte); // 
	//lua_register(L, "writeShort", writeShort); // 
	//lua_register(L, "writeInteger", writeInteger); // 
	//lua_register(L, "writeFloat", writeFloat); // 
	//lua_register(L, "writeDouble", writeDouble); // 
}

Lua::~Lua()
{
	lua_close(L);
}

void Lua::doFile(const char *filePath) {
	luaL_dofile(L,filePath);
}

//int Lua::readByte(lua_State* m_L)
//{
//	lua_pushinteger(m_L, mem.read<byte>((DWORD_PTR)lua_tointeger(m_L, 1)));
//	return 1;
//}
//
//int Lua::readShort(lua_State* m_L)
//{
//	lua_pushinteger(m_L, mem.read<short>((DWORD_PTR)lua_tointeger(m_L, 1)));
//	return 1;
//}
//
//int Lua::readInteger(lua_State* m_L)
//{
//	lua_pushinteger(m_L, mem.read<int>((DWORD_PTR)lua_tointeger(m_L, 1)));
//	return 1;
//}
//
//int Lua::readLong(lua_State* m_L)
//{
//	lua_pushinteger(m_L, mem.read<LONGLONG>((DWORD_PTR)lua_tointeger(m_L, 1)));
//	return 1;
//}
//
//int Lua::readFloat(lua_State* m_L)
//{
//	lua_pushnumber(m_L, mem.read<float>((DWORD_PTR)lua_tonumber(m_L, 1)));
//	return 1;
//}
//int Lua::readDouble(lua_State* m_L)
//{
//	lua_pushnumber(m_L, mem.read<double>((DWORD_PTR)lua_tonumber(m_L, 1)));
//	return 1;
//}
//
//int Lua::writeByte(lua_State* m_L)
//{
//	lua_pushinteger(m_L, mem.write<byte>((DWORD_PTR)lua_tointeger(m_L, 1), (byte)lua_tointeger(m_L, 2)));
//	return 1;
//}
//int Lua::writeShort(lua_State* m_L)
//{
//	lua_pushinteger(m_L, mem.write<short>((DWORD_PTR)lua_tointeger(m_L, 1), (short)lua_tointeger(m_L, 2)));
//	return 1;
//}
//int Lua::writeInteger(lua_State* m_L)
//{
//	lua_pushinteger(m_L, mem.write<int>((DWORD_PTR)lua_tointeger(m_L, 1), (int)lua_tointeger(m_L, 2)));
//	return 1;
//}
//int Lua::writeLong(lua_State* m_L)
//{
//	lua_pushinteger(m_L, mem.write<LONGLONG>((DWORD_PTR)lua_tointeger(m_L, 1), (LONGLONG)lua_tointeger(m_L, 2)));
//	return 1;
//}
//int Lua::writeFloat(lua_State* m_L)
//{
//	lua_pushinteger(m_L, mem.write<float>((DWORD_PTR)lua_tointeger(m_L, 1), (float)lua_tointeger(m_L, 2)));
//	return 1;
//}
//int Lua::writeDouble(lua_State* m_L)
//{
//	lua_pushinteger(m_L, mem.write<double>((DWORD_PTR)lua_tointeger(m_L, 1), (double)lua_tointeger(m_L, 2)));
//	return 1;
//}