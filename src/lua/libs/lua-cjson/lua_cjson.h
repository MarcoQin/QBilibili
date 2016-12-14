#ifndef CJSON_HEAD
#define CJSON_HEAD
#include <lua.h>
#include <lauxlib.h>

#ifdef _MSC_VER
#define CJSON_EXPORT    __declspec(dllexport)
#else
#define CJSON_EXPORT    extern
#endif

CJSON_EXPORT int luaopen_cjson(lua_State *l);

#endif
