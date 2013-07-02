#-------------------------------------------------------------------------------
#
# \file  CDBImage.pro
# \brief project file
#
#-------------------------------------------------------------------------------


QT         += designer
CONFIG     += plugin debug_and_release
TARGET      = $$qtLibraryTarget(CDbImagePlugin)
TEMPLATE    = lib

HEADERS     = CDbImagePlugin.h
SOURCES     = CDbImagePlugin.cpp
RESOURCES   = Resource.qrc
LIBS       += -L.

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS   += target

include(CDbImage.pri)
