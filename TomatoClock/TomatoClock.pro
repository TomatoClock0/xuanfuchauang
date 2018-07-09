#-------------------------------------------------
#
# Project created by QtCreator 2018-07-05T22:43:08
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TomatoClock
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        tomatoclock.cpp \
    addtasks.cpp \
    managetasks.cpp \
    form.cpp

HEADERS += \
        tomatoclock.h \
    addtasks.h \
    managetasks.h \
    form.h

FORMS += \
        tomatoclock.ui \
    addtasks.ui \
    managetasks.ui \
    form.ui
INCLUDEPATH +="C:\Qt\5.11.1\msvc2017_64\include\QtSql"
