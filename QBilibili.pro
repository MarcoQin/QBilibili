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


SOURCES += src/main.cpp\
        src/vrenderer.cpp \
        src/popmenu.cpp \
        src/UI/mainwindow.cpp \
        src/UI/mainmenu.cpp

HEADERS  += \
        src/vrenderer.h \
        src/popmenu.h \
        src/UI/mainwindow.h \
        src/UI/mainmenu.h

FORMS    += \
