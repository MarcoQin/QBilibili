#include "luamanager.h"
#include "../graphics/dmtext.h"
#include <Qt>
#include <QtCore>
#include "libs/luasocket/luasocket_out.h"
extern "C"{
#include "libs/lpack.h"
#include "libs/lua-cjson/lua_cjson.h"
}
using namespace std;


int l_DMText_constuctor (lua_State *L)
{
    int n = lua_gettop(L); // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments, expected 2 (class, x)", n);
    // First argument is now a table that represent the class to instantiate
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_newtable(L); // Create table to represent instance

    // Set first argument of new to metatable of instance
    lua_pushvalue(L, 1);
    lua_setmetatable(L, -2);

    // Do function lookups in metatable
    lua_pushvalue(L, 1);
    lua_setfield(L, 1, "__index");

    const char* text = luaL_checkstring(L, 2);

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
    lua_setfield(L, -2, "__self");

    // The Lua stack at this point looks like this:
    //
    //     2| userdata               |-1
    //     1| string parameter       |-2
    //
    // We return 1 so Lua callsite will get the user data and
    // Lua will clean the stack after that.

    return 1;
}


int l_DMText_constuctor_old(lua_State *L)
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

DMText *l_CheckDMText_old(lua_State *L, int n)
{
    // This checks that the argument is a userdata
    // with the metatable "luaL_DMText"
    return *(DMText **)luaL_checkudata(L, n, "luaL_DMText");
}

DMText *l_CheckDMText(lua_State *L, int n)
{
    void *ud = 0;
    luaL_checktype(L, n, LUA_TTABLE);
    lua_getfield(L, n, "__self");
    n = -1;
    ud = luaL_checkudata(L, n, "luaL_DMText");
    // This checks that the argument is a userdata
    // with the metatable "luaL_DMText"
    return *((DMText **)ud);
}

int l_DMText_destructor(lua_State*L)
{
    DMText *dmt;
    int luaType = lua_type(L, 1);
    qDebug() << "about to delete dmt";
    qDebug() << "luaType is: " << luaType;
    switch(luaType) {
        case LUA_TUSERDATA:
            qDebug() << "LUA_TUSERDATA";
            dmt = l_CheckDMText_old(L, 1);
            break;
        case LUA_TTABLE:
            qDebug() << "LUA_TTABLE";
            dmt = l_CheckDMText(L, 1);
            break;
    }
    // try {
    // } catch(exception e) {
        // qDebug() << e.what();
        // dmt = l_CheckDMText_old(L, 1);
    // }
    qDebug() << "got dmt";
    qDebug() << "delete dmt";
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

int l_DMText_width(lua_State *L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    int width = dmt->width();
    lua_pushnumber(L, width);
    return 1;
}

int l_DMText_height(lua_State *L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    int height = dmt->height();
    lua_pushnumber(L, height);
    return 1;
}

int l_DMText_getText(lua_State *L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    QString text = dmt->getText();
    lua_pushstring(L, text.toStdString().c_str());
    return 1;
}

int l_DMText_setPosition(lua_State *L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    double x = luaL_checknumber(L, 2);
    double y = luaL_checknumber(L, 3);
    QPointF pos(x, y);
    dmt->setPosition(pos);
    return 0;
}

int l_DMText_getPosition(lua_State *L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    QPointF pos = dmt->getPosition();
    lua_pushnumber(L, pos.x());
    lua_pushnumber(L, pos.y());
    return 2;
}

int l_DMText_setColor(lua_State *L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    int r = luaL_checknumber(L, 2);
    int g = luaL_checknumber(L, 3);
    int b = luaL_checknumber(L, 4);
    QColor color(r, g, b);
    dmt->setColor(color);
    return 0;
}

int l_DMText_getColor(lua_State *L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    QColor color = dmt->getColor();
    lua_pushnumber(L, color.red());
    lua_pushnumber(L, color.green());
    lua_pushnumber(L, color.blue());
    return 3;
}

int l_DMText_setAlpha(lua_State *L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    int a = luaL_checknumber(L, 2);
    dmt->setAlpha(a);
    return 0;
}

int l_DMText_getAlpha(lua_State *L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    int a = dmt->getAlpha();
    lua_pushnumber(L, a);
    return 1;
}

int l_DMText_setFontSize(lua_State *L)
{
    DMText *dmt = l_CheckDMText(L, 1);
    int size = luaL_checknumber(L, 2);
    dmt->setFontSize(size);
    return 0;
}

void RegisterDMText(lua_State *L)
{
    luaL_Reg sDMTextRegs[] =
    {
        { "new", l_DMText_constuctor },
        { "draw", l_DMText_draw },
        { "setPosition", l_DMText_setPosition },
        { "getPosition", l_DMText_getPosition },
        { "setAlpha", l_DMText_setAlpha },
        { "getAlpha", l_DMText_getAlpha },
        { "setColor", l_DMText_setColor },
        { "getColor", l_DMText_getColor },
        { "width", l_DMText_width },
        { "height", l_DMText_height },
        { "getText", l_DMText_getText },
        { "setFontSize", l_DMText_setFontSize },
        // { "__gc", l_DMText_destructor },  // I give up __gc... just fuck
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

int setLuaPath( lua_State* L, const char* path )
{
    lua_getglobal( L, "package" );
    lua_getfield( L, -1, "path" ); // get field "path" from table at top of stack (-1)
    std::string cur_path = lua_tostring( L, -1 ); // grab path string from top of stack
    cur_path.append( ";" ); // do your path magic here
    cur_path.append( path );
    cur_path.append("?.lua;");
    lua_pop( L, 1 ); // get rid of the string on the stack we just pushed on line 5
    lua_pushstring( L, cur_path.c_str() ); // push the new one
    lua_setfield( L, -2, "path" ); // set the field "path" in table at -2 with value at top of stack
    lua_pop( L, 1 ); // get rid of package table from top of stack
    return 0; // all done!
}

extern "C"
int lua_getWindowSize(lua_State *L)
{
    QSize size = LuaManager::instance()->getWindowSize();
    lua_pushnumber(L, size.width());
    lua_pushnumber(L, size.height());
    // Let Lua know how many return values we've passed
    return 2;
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
    love::luasocket::__open(L);  // luasocket
    luaopen_pack(L);             // lpack
    luaopen_cjson(L);            // lua-cjson
    lua_register(L, "getWindowSize", lua_getWindowSize);

    qDebug() << QDir::currentPath();
    qDebug() << QCoreApplication::applicationDirPath();
//    int error = luaL_dofile(L, "/Users/marcoqin/Codes/cpp_lua/boot.lua");
    QString runtimePath = QCoreApplication::applicationDirPath() + "/../Resources/";
    // runtimePath += "/../Resources/boot.lua";
    QString bootFile = runtimePath + "boot.lua";
    setLuaPath(L, runtimePath.toStdString().c_str());

    int error = luaL_dofile(L, bootFile.toStdString().c_str());


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

void LuaManager::callUpdateFunc(double dt)
{
    lua_getglobal(L, "QBUpdate");
    lua_pushnumber(L, dt);
    lua_call(L, 1, 0);
}

const char *LuaManager::callGetAdressFunc(QString &url, int index)
{
    // lua_getglobal(L, "get_live_address");
    lua_getglobal(L, "QBGetLiveAdress");
    lua_pushstring(L, url.toStdString().c_str());
    lua_pushnumber(L, index);
    lua_call(L, 2, 1);
    const char* u = luaL_checkstring(L, -1);
    qDebug() << "get: "<< u;
    lua_pop(L, 1);
    return u;
}

void LuaManager::setWindowSize(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
}

QSize &LuaManager::getWindowSize()
{
    QSize *size = new QSize(windowWidth, windowHeight);
    return *size;
}
