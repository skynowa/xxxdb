TEMPLATE    = app
TARGET      = XXXDb
QT          = core gui sql network
CONFIG      += warn_on

INCLUDEPATH = "/home/sergey/Coding/xLib/Include/" "/home/sergey/Coding/xLib/Source/"

LIBS        = ./Libs/libxlib.a -lcrypto

HEADERS     = CMain.h \
              Classes/CSqlCryptTableModel.h \
              Classes/CSqlNavigator.h

SOURCES     = main.cpp \
              CMain.cpp \
              Classes/CSqlCryptTableModel.cpp \
              Classes/CSqlNavigator.cpp

FORMS       = Forms/CMain.ui
RESOURCES   =

DESTDIR     = ./Distr
MOC_DIR     = ./Temp
OBJECTS_DIR = ./Temp
RCC_DIR     = ./Resources
UI_DIR      = ./Ui
