#include "luamanager.h"
#include "../graphics/dmtext.h"
#include <Qt>
#include <QtCore>


int l_DMText_constuctor(lua_State *L)
{
    const char* text = luaL_checkstring(L, 1);

    // We could actually allocate DMText itself as a user data but
    // since user data can be GC'ed and we gain unity by using CRT's heap
    // all along.
    // Allocate memory for a pointer to to object
    DMText **dmt = (DMText**)lua_newuserdata(L, sizeof(DMText*));
    qDebug() << text;
    QString s(text);
    *dmt = new DMText(s);

    // Usually, we'll just use "DMText" as the second parameter, but I
    // say luaL_DMText here to distinguish the difference:
    //
    // This 2nd parameter here is an _internal label_ for luaL, it is
    // _not_ exposed to Lua by default.
    //
    // Effectively, this metatable is not accessible by Lua by default.
    luaL_getmetatable(L, "luaL_DMText");

    // The Lua stack at this point looks like this:
    //
    //     3| metatable "luaL_DMText"   |-1
    //     2| userdata               |-2
    //     1| string parameter       |-3
    //
    // So the following line sets the metatable for the user data to the luaL_DMText
    // metatable
    //
    // We must set the metatable here because Lua prohibits setting
    // the metatable of a userdata in Lua. The only way to set a metatable
    // of a userdata is to do it in C.
    lua_setmetatable(L, -2);

    // The Lua stack at this point looks like this:
    //
    //     2| userdata               |-1
    //     1| string parameter       |-2
    //
    // We return 1 so Lua callsite will get the user data and
    // Lua will clean the stack after that.

    return 1;
}

DMText *l_CheckDMText(lua_State *L, int n)
{
    // This checks that the argument is a userdata
    // with the metatable "luaL_DMText"
    return *(DMText **)luaL_checkudata(L, n, "luaL_DMText");
}

int l_DMText_destructor(lua_State*L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    delete dmt;
    return 0;
}

int l_DMText_draw(lua_State *L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    QPainter *painter = (QPainter *)lua_touserdata(L, 2);
    dmt->draw(*painter);
    return 0;
}

void RegisterDMText(lua_State *L)
{
    luaL_Reg sDMTextRegs[] =
    {
        { "new", l_DMText_constuctor },
        { "draw", l_DMText_draw },
        { "__gc", l_DMText_destructor },
        { NULL, NULL }
    };

    // Create a luaL metatable. This metatable is not
    // exposed to Lua. The "luaL_DMText" label is used by luaL
    // internally to identity things.
    luaL_newmetatable(L, "luaL_DMText");

    // Register the C functions _into_ the metatable we just created.
    luaL_setfuncs(L, sDMTextRegs, 0);

    // The Lua stack at this point looks like this:
    //
    //     1| metatable "luaL_DMText"   |-1
    lua_pushvalue(L, -1);

    // The Lua stack at this point looks like this:
    //
    //     2| metatable "luaL_DMText"   |-1
    //     1| metatable "luaL_DMText"   |-2

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(L, -1, "__index");

    // The Lua stack at this point looks like this:
    //
    //     1| metatable "luaL_DMText"   |-1

    // The luaL_Foo metatable now has the following fields
    //     - __gc
    //     - __index
    //     - add
    //     - new

    // Now we use setglobal to officially expose the luaL_DMText metatable
    // to Lua. And we use the name "DMText".
    //
    // This allows Lua scripts to _override_ the metatable of Foo.
    // For high security code this may not be called for but
    // we'll do this to get greater flexibility.
    lua_setglobal(L, "DMText");
}


LuaManager *LuaManager::_instance = nullptr;

LuaManager *LuaManager::instance()
{
    return _instance ? _instance : new LuaManager();
}

LuaManager::LuaManager(QObject *parent) : QObject(parent)
{
    _instance = this;
    L = luaL_newstate();
    luaL_openlibs(L);
    RegisterDMText(L);

    int error = luaL_dofile(L, "/Users/marcoqin/Codes/cpp_lua/boot.lua");
    if (error)
        qDebug() << "Lua error: " << luaL_checkstring(L, -1);
}

LuaManager::~LuaManager()
{
    if (L) {
        lua_close(L);
        L = NULL;
    }
    delete _instance;
    _instance = NULL;
}

void LuaManager::callDrawFunc(QPainter &painter)
{
    lua_getglobal(L, "QBDraw");
    lua_pushlightuserdata(L, (void *)&painter);
    lua_call(L, 1, 0);
}
