#ifndef __LUA_H__
#define __LUA_H__
#ifdef __cplusplus
extern "C" {
#include "../lua53/lua.h"
#include "../lua53/lualib.h"  
#include "../lua53/lauxlib.h" 
#pragma comment(lib,"../x64/Release/library/lua53.lib")

}
#else  
#include "../lua53/lua.hpp"
#include "../lua53/lualib.h"  
#include "../lua53/lauxlib.h"  
#pragma comment(lib,"../x64/Release/library/lua53.lib")
#endif

#ifndef __MEMORY_H__
#include "../memory.hpp"
#endif // !__MEMORY_H__

#ifndef __KCA_H__
#include "../Kca/Kca.h"
#pragma comment(lib,"../x64/Release/library/Kca.lib")
#endif // !__UTILS_H__

class Lua
{
public:
	lua_State* L = NULL;
	Lua();
	~Lua();
	void doFile(const char * filePath);
	/*static int readByte(lua_State * m_L);
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
	static int writeDouble(lua_State * m_L);*/
private:
	
};

#endif // !__LUA_H__



