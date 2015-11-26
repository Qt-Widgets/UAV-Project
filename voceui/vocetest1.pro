<<<<<<< HEAD

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
=======
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

>>>>>>> b267b5cbb4059e92fcbe23f36f8a1a4b83f8a287
