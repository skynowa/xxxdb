#-------------------------------------------------------------------------------
#
# \file  CDBImage.pro
# \brief project file
#
#-------------------------------------------------------------------------------


QT         += designer core gui widgets sql network xml
CONFIG     += plugin debug_and_release
TARGET      = $$qtLibraryTarget(CDbImagePlugin)
TEMPLATE    = lib

HEADERS     = CDbImagePlugin.h
SOURCES     = CDbImagePlugin.cpp
RESOURCES   = Resource.qrc
LIBS       += -L.

target.path = /opt/Libs/Qt/5.0.2_x64/Tools/QtCreator/bin/designer
INSTALLS   += target

include(CDbImage.pri)
