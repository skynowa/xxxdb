#-------------------------------------------------------------------------------
#
# \file  CDBImage.pro
# \brief project file
#
#-------------------------------------------------------------------------------


TARGET      = $$qtLibraryTarget(CDbImagePlugin)
TEMPLATE    = lib
QT         += designer core gui widgets sql network xml
CONFIG     += plugin debug_and_release
DEFINES    += qTEST_IS_USED=1
CODECFORTR  = UTF-8

HEADERS     = CDbImage.h CDbImagePlugin.h
SOURCES     = CDbImage.cpp CDbImagePlugin.cpp
RESOURCES   = Resource.qrc
LIBS       += -L.

target.path   = /opt/Libs/Qt/5.0.2_x64/Tools/QtCreator/bin/designer
sources.files = $$HEADERS
sources.path  = ../../

INSTALLS   += target sources

