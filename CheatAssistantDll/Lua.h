#pragma once
#ifdef __cplusplus
extern "C" {
#include "../lua53/lua.h"
#include "../lua53/lualib.h"  
#include "../lua53/lauxlib.h" 
#pragma comment(lib,"../Release/library/lua53.lib")

}
#else  
#include "../lua53/lua.hpp"
#include "../lua53/lualib.h"  
#include "../lua53/lauxlib.h"  
#pragma comment(lib,"../Release/library/lua53.lib")
#endif

class Lua
{
public:
	lua_State * L = NULL;
	Lua();
	~Lua();
	void registers(lua_State * m_L);
	bool check(int result);
	bool doFile(const char * filePath);
	void getGlobal(const char * name);
	static int readByte(lua_State * m_L);
	static int readShort(lua_State * m_L);
	static int readInteger(lua_State * m_L);
	static int readLong(lua_State * m_L);
	static int readFloat(lua_State * m_L);
	static int readDouble(lua_State * m_L);
	static int writeByte(lua_State * m_L);
	static int writeShort(lua_State * m_L);
	static int writeInteger(lua_State * m_L);
	static int writeLong(lua_State * m_L);
	static int writeFloat(lua_State * m_L);
	static int writeDouble(lua_State * m_L);
	static int findWindow(lua_State * m_L);
	static int getForegroundWindow(lua_State * m_L);
	static int setForegroundWindow(lua_State * m_L);
	static int setWindowLong(lua_State * m_L);
	static int outputDebugString(lua_State * m_L);
};

