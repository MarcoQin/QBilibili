#ifndef __QLUALOADER_H
#define __QLUALOADER_H

#ifdef __cplusplus
#include <lua5.2/lua.hpp>
#else
#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>
#endif

extern "C"
{
    extern int q_lua_loader(lua_State *L);
}


#endif
