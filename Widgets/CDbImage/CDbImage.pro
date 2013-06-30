CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(CDbImagePlugin)
TEMPLATE    = lib

HEADERS     = CDbImagePlugin.h
SOURCES     = CDbImagePlugin.cpp
RESOURCES   = Resource.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(CDbImage.pri)
