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
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

DISTFILES += \
    map.js \
    map.html
