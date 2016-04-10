#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T18:59:50
#
#-------------------------------------------------

QT       += core gui serialport webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UAVProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calculate.cpp \
    uav.cpp

HEADERS  += mainwindow.h \
    calculate.h \
    uav.h

FORMS    += mainwindow.ui

DISTFILES += \
    map.js \
    map.html

INCLUDEPATH += "C:\Users\Ernest Curioso\Documents\Voce\voce-0.9.1\voce-0.9.1\src\c++" "C:\Program Files\Java\jdk1.8.0_65\include" "C:\Program Files\Java\jdk1.8.0_65\include\win32"
LIBS += "-LC:\Program Files\Java\jdk1.8.0_65\lib" "-LC:\Program Files\Java\jdk1.8.0_65\jre\bin\server" -ljvm
