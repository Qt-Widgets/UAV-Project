#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T22:14:17
#
#-------------------------------------------------

QT       += core gui positioning opengl xml network widgets sensors

TARGET = VoceTest1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    place.cpp

HEADERS  += mainwindow.h \
    place.h

FORMS    += mainwindow.ui

INCLUDEPATH += "C:\Users\Ernest Curioso\Documents\Voce\voce-0.9.1\voce-0.9.1\src\c++" "C:\Program Files\Java\jdk1.8.0_65\include" "C:\Program Files\Java\jdk1.8.0_65\include\win32"
LIBS += "-LC:\Program Files\Java\jdk1.8.0_65\lib" "-LC:\Program Files\Java\jdk1.8.0_65\jre\bin\server" -ljvm

CONFIG += c++11 esri_runtime_qt10_2_6
win32:CONFIG += \
  embed_manifest_exe
