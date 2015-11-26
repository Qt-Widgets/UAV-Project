
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VoceTest1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += "C:\voce-0.9.1\src\c++" "C:\Program Files\Java\jdk1.8.0_11\include" "C:\Program Files\Java\jdk1.8.0_11\include\win32"
LIBS += "-LC:\Program Files\Java\jdk1.8.0_11\jre\bin\server" "-LC:\Program Files\Java\jdk1.8.0_11\lib" -ljvm

DISTFILES += \
    lib/voce.config.xml \
    lib/digits.gram
