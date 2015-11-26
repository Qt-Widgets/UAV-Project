#-------------------------------------------------
#  Copyright 2015 ESRI
#
#  All rights reserved under the copyright laws of the United States
#  and applicable international laws, treaties, and conventions.
#
#  You may freely redistribute and use this sample code, with or
#  without modification, provided you include the original copyright
#  notice and use restrictions.
#
#  See the Sample code usage restrictions document for further information.
#-------------------------------------------------

TARGET = untitled3 
TEMPLATE = app

QT += positioning core gui opengl xml network widgets sensors

# After installing the Runtime SDK for Qt you'll need to copy the
# esri_runtime_qt.prf file from your qt10.2.6/sdk/ideintegration folder
# to your Qt SDK's mkspecs/features folder in order for Qt Creator to locate 
# the ArcGIS Runtime SDK for Qt header files and libraries.
#
CONFIG += c++11 esri_runtime_qt10_2_6
win32:CONFIG += \
  embed_manifest_exe


SOURCES += \
	main.cpp \
        untitled3.cpp 

HEADERS += \
	untitled3.h

