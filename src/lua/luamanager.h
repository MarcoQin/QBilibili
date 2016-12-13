#ifndef LUAMANAGER_H
#define LUAMANAGER_H

#include <QObject>
#ifdef __cplusplus
#include <lua5.2/lua.hpp>
#else
#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>
#endif
#include <QPainter>

class LuaManager : public QObject
{
    Q_OBJECT
public:
    static LuaManager *instance();
    ~LuaManager();
    void callDrawFunc(QPainter &painter);
    void callUpdateFunc(double dt);
    const char *callGetAdressFunc(QString &url, int index);
private:
    static LuaManager *_instance;
    explicit LuaManager(QObject *parent = 0);
    lua_State *L;

signals:

public slots:
};

#endif // LUAMANAGER_H
