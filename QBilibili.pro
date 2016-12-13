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
    src/luasocket/libluasocket/auxiliar.c \
    src/luasocket/libluasocket/buffer.c \
    src/luasocket/libluasocket/compat.c \
    src/luasocket/libluasocket/except.c \
    src/luasocket/libluasocket/inet.c \
    src/luasocket/libluasocket/io.c \
    src/luasocket/libluasocket/luasocket.c \
    src/luasocket/libluasocket/mime.c \
    src/luasocket/libluasocket/options.c \
    src/luasocket/libluasocket/select.c \
    src/luasocket/libluasocket/tcp.c \
    src/luasocket/libluasocket/timeout.c \
    src/luasocket/libluasocket/udp.c \
    src/luasocket/luasocket_out.cpp \
    src/lua/lpack.c \
    src/UI/contextmenu.cpp

HEADERS  += \
    src/vrenderer.h \
    src/UI/mainwindow.h \
    src/UI/mainmenu.h \
    src/UI/floatwidget.h \
    src/UI/processbarnew.h \
    src/UI/titlebar.h \
    src/graphics/dmtext.h \
    src/lua/luamanager.h \
    src/luasocket/libluasocket/auxiliar.h \
    src/luasocket/libluasocket/buffer.h \
    src/luasocket/libluasocket/compat.h \
    src/luasocket/libluasocket/except.h \
    src/luasocket/libluasocket/ftp.lua.h \
    src/luasocket/libluasocket/headers.lua.h \
    src/luasocket/libluasocket/http.lua.h \
    src/luasocket/libluasocket/inet.h \
    src/luasocket/libluasocket/io.h \
    src/luasocket/libluasocket/ltn12.lua.h \
    src/luasocket/libluasocket/luasocket.h \
    src/luasocket/libluasocket/mbox.lua.h \
    src/luasocket/libluasocket/mime.h \
    src/luasocket/libluasocket/mime.lua.h \
    src/luasocket/libluasocket/options.h \
    src/luasocket/libluasocket/pierror.h \
    src/luasocket/libluasocket/select.h \
    src/luasocket/libluasocket/smtp.lua.h \
    src/luasocket/libluasocket/socket.h \
    src/luasocket/libluasocket/socket.lua.h \
    src/luasocket/libluasocket/tcp.h \
    src/luasocket/libluasocket/timeout.h \
    src/luasocket/libluasocket/tp.lua.h \
    src/luasocket/libluasocket/udp.h \
    src/luasocket/luasocket_out.h \
    src/lua/lpack.h \
    src/UI/contextmenu.h
    src/luasocket/libluasocket/usocket.h \


win32{
    HEADERS += src/luasocket/libluasocket/wsocket.h
    SOURCES += src/luasocket/libluasocket/wsocket.c
} else {
    HEADERS += \
        src/luasocket/libluasocket/unix.h \
        src/luasocket/libluasocket/unixtcp.h \
        src/luasocket/libluasocket/unixudp.h \
        src/luasocket/libluasocket/url.lua.h

    SOURCES += \
        src/luasocket/libluasocket/unix.c \
        src/luasocket/libluasocket/unixtcp.c \
        src/luasocket/libluasocket/unixudp.c \
        src/luasocket/libluasocket/usocket.c \
        src/luasocket/libluasocket/serial.c \
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
