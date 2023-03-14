#-------------------------------------------------
#
# Project created by QtCreator 2020-10-10T19:53:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = realwork
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainscene.cpp \
    map.cpp \
    room.cpp \
    hero.cpp \
    bullet.cpp \
    bomb.cpp \
    enemy.cpp \
    miniroom.cpp \
    weapon.cpp \
    props.cpp \
    portal.cpp \
    chest.cpp \
    startpage.cpp \
    introduce.cpp \
    boos.cpp \
    deathpage.cpp

HEADERS += \
        mainscene.h \
    map.h \
    room.h \
    config.h \
    hero.h \
    bullet.h \
    bomb.h \
    enemy.h \
    miniroom.h \
    weapon.h \
    props.h \
    portal.h \
    chest.h \
    startpage.h \
    introduce.h \
    boos.h \
    deathpage.h


CONFIG += C++11


QT += multimedia

RESOURCES += \
    source.qrc
CONFIG += resources_big











