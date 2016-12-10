#ifndef LUAMANAGER_H
#define LUAMANAGER_H

#include <QObject>

class LuaManager : public QObject
{
    Q_OBJECT
public:
    explicit LuaManager(QObject *parent = 0);

signals:

public slots:
};

#endif // LUAMANAGER_H