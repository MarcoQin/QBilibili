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
    -llua \
    -framework IOKit

SOURCES += src/main.cpp\
        src/vrenderer.cpp \
        src/popmenu.cpp \
        src/UI/mainwindow.cpp \
        src/UI/mainmenu.cpp \
        src/UI/processbar.cpp \
        src/UI/floatwidget.cpp \
        src/UI/processbarnew.cpp \
        src/UI/titlebar.cpp \
        src/graphics/dmtext.cpp \
        src/lua/luamanager.cpp

HEADERS  += \
        src/vrenderer.h \
        src/popmenu.h \
        src/UI/mainwindow.h \
        src/UI/mainmenu.h \
        src/UI/processbar.h \
        src/UI/floatwidget.h \
        src/UI/processbarnew.h \
        src/UI/titlebar.h \
        src/graphics/dmtext.h \
        src/lua/luamanager.h

FORMS    += \

RESOURCES += \
    res/res.qrc
