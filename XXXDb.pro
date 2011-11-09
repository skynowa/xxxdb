TEMPLATE    = app
TARGET      = XXXDb
QT          = core gui sql network
CONFIG      += warn_on

unix: INCLUDEPATH = "/home/sergey/Coding/xLib/Include/" "/home/sergey/Coding/xLib/Source/"
win32:INCLUDEPATH = "D:/xLib/Include/" "D:/xLib/Source/" "D:/Libs/OpenSSL/OpenSSL-Win32/include/"

unix: LIBS        = ./Libs/libxlib.a -lcrypto
win32:LIBS        = "D:\Libs\OpenSSL\OpenSSL-Win32\lib\libeay32.lib" "D:\Libs\OpenSSL\OpenSSL-Win32\lib\ssleay32.lib"

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
