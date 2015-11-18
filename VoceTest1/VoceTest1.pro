#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T22:14:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VoceTest1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += "C:\Users\Ernest Curioso\Documents\Voce\voce-0.9.1\voce-0.9.1\src\c++" "C:\Program Files\Java\jdk1.8.0_65\include" "C:\Program Files\Java\jdk1.8.0_65\include\win32"
LIBS += "-LC:\Program Files\Java\jdk1.8.0_65\lib" "-LC:\Program Files\Java\jdk1.8.0_65\jre\bin\server" -ljvm

