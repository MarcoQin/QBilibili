#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T16:13:49
#
#-------------------------------------------------

QT       += core gui \
            avwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBilibili
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += \
    /usr/local/Cellar/lua/5.2.4_4/include

LIBS += \
    -L/usr/local/Cellar/lua/5.2.4_4/lib \
    -llua

macx{
    LIBS += -framework IOKit
}


SOURCES += \
    src/main.cpp\
    src/vrenderer.cpp \
    src/UI/mainwindow.cpp \
    src/UI/mainmenu.cpp \
    src/UI/floatwidget.cpp \
    src/UI/processbarnew.cpp \
    src/UI/titlebar.cpp \
    src/graphics/dmtext.cpp \
    src/lua/luamanager.cpp \
    src/lua/libs/luasocket/libluasocket/auxiliar.c \
    src/lua/libs/luasocket/libluasocket/buffer.c \
    src/lua/libs/luasocket/libluasocket/compat.c \
    src/lua/libs/luasocket/libluasocket/except.c \
    src/lua/libs/luasocket/libluasocket/inet.c \
    src/lua/libs/luasocket/libluasocket/io.c \
    src/lua/libs/luasocket/libluasocket/luasocket.c \
    src/lua/libs/luasocket/libluasocket/mime.c \
    src/lua/libs/luasocket/libluasocket/options.c \
    src/lua/libs/luasocket/libluasocket/select.c \
    src/lua/libs/luasocket/libluasocket/tcp.c \
    src/lua/libs/luasocket/libluasocket/timeout.c \
    src/lua/libs/luasocket/libluasocket/udp.c \
    src/lua/libs/luasocket/luasocket_out.cpp \
    src/lua/libs/lpack.c \
    src/UI/contextmenu.cpp \
    src/lua/libs/lua-cjson/dtoa.c \
    src/lua/libs/lua-cjson/fpconv.c \
    src/lua/libs/lua-cjson/g_fmt.c \
    src/lua/libs/lua-cjson/lua_cjson.c \
    src/lua/libs/lua-cjson/strbuf.c

HEADERS  += \
    src/vrenderer.h \
    src/UI/mainwindow.h \
    src/UI/mainmenu.h \
    src/UI/floatwidget.h \
    src/UI/processbarnew.h \
    src/UI/titlebar.h \
    src/graphics/dmtext.h \
    src/lua/luamanager.h \
    src/lua/libs/luasocket/libluasocket/auxiliar.h \
    src/lua/libs/luasocket/libluasocket/buffer.h \
    src/lua/libs/luasocket/libluasocket/compat.h \
    src/lua/libs/luasocket/libluasocket/except.h \
    src/lua/libs/luasocket/libluasocket/ftp.lua.h \
    src/lua/libs/luasocket/libluasocket/headers.lua.h \
    src/lua/libs/luasocket/libluasocket/http.lua.h \
    src/lua/libs/luasocket/libluasocket/inet.h \
    src/lua/libs/luasocket/libluasocket/io.h \
    src/lua/libs/luasocket/libluasocket/ltn12.lua.h \
    src/lua/libs/luasocket/libluasocket/luasocket.h \
    src/lua/libs/luasocket/libluasocket/mbox.lua.h \
    src/lua/libs/luasocket/libluasocket/mime.h \
    src/lua/libs/luasocket/libluasocket/mime.lua.h \
    src/lua/libs/luasocket/libluasocket/options.h \
    src/lua/libs/luasocket/libluasocket/pierror.h \
    src/lua/libs/luasocket/libluasocket/select.h \
    src/lua/libs/luasocket/libluasocket/smtp.lua.h \
    src/lua/libs/luasocket/libluasocket/socket.h \
    src/lua/libs/luasocket/libluasocket/socket.lua.h \
    src/lua/libs/luasocket/libluasocket/tcp.h \
    src/lua/libs/luasocket/libluasocket/timeout.h \
    src/lua/libs/luasocket/libluasocket/tp.lua.h \
    src/lua/libs/luasocket/libluasocket/udp.h \
    src/lua/libs/luasocket/luasocket_out.h \
    src/lua/libs/lpack.h \
    src/UI/contextmenu.h \
    src/lua/libs/lua-cjson/dtoa_config.h \
    src/lua/libs/lua-cjson/fpconv.h \
    src/lua/libs/lua-cjson/lua_cjson.h \
    src/lua/libs/lua-cjson/strbuf.h
    src/lua/libs/luasocket/libluasocket/usocket.h \


win32{
    HEADERS += src/lua/libs/luasocket/libluasocket/wsocket.h
    SOURCES += src/lua/libs/luasocket/libluasocket/wsocket.c
} else {
    HEADERS += \
        src/lua/libs/luasocket/libluasocket/unix.h \
        src/lua/libs/luasocket/libluasocket/unixtcp.h \
        src/lua/libs/luasocket/libluasocket/unixudp.h \
        src/lua/libs/luasocket/libluasocket/url.lua.h

    SOURCES += \
        src/lua/libs/luasocket/libluasocket/unix.c \
        src/lua/libs/luasocket/libluasocket/unixtcp.c \
        src/lua/libs/luasocket/libluasocket/unixudp.c \
        src/lua/libs/luasocket/libluasocket/usocket.c \
        src/lua/libs/luasocket/libluasocket/serial.c \
}

FORMS    += \

RESOURCES += \
    res/res.qrc

#DISTFILES += \
#    src/luasocket/libluasocket/ftp.lua \
#    src/luasocket/libluasocket/headers.lua \
#    src/luasocket/libluasocket/http.lua \
#    src/luasocket/libluasocket/ltn12.lua \
#    src/luasocket/libluasocket/mbox.lua \
#    src/luasocket/libluasocket/mime.lua \
#    src/luasocket/libluasocket/smtp.lua \
#    src/luasocket/libluasocket/socket.lua \
#    src/luasocket/libluasocket/tp.lua \
#    src/luasocket/libluasocket/url.lua
