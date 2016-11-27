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
        src/testwidget.cpp \
        src/popmenu.cpp

HEADERS  += \
        src/vrenderer.h \
        src/testwidget.h \
        src/popmenu.h

FORMS    += \
