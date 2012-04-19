#---------------------------------------------------------------------------
#
# \file  XXXDb.pro
# \brief project file
#
#---------------------------------------------------------------------------


TARGET             = XXXDb
TEMPLATE           = app
QT                 = core gui sql network
CONFIG            += warn_on

unix: INCLUDEPATH  =
win32:INCLUDEPATH  = "$(XLIB)/Include" "D:/Libs/OpenSSL/OpenSSL-Win32/include/"

unix: LIBS         = -lxlib -lcrypto
win32:LIBS         = "D:\Libs\OpenSSL\OpenSSL-Win32\lib\libeay32.lib" "D:\Libs\OpenSSL\OpenSSL-Win32\lib\ssleay32.lib"

HEADERS            = CMain.h \
                     Classes/Common.h \
                     Classes/CSqlCryptTableModel.h \
                     Classes/CSqlNavigator.h

SOURCES            = main.cpp \
                     CMain.cpp \
                     Classes/CSqlCryptTableModel.cpp \
                     Classes/CSqlNavigator.cpp

FORMS              = Forms/CMain.ui
RESOURCES          =

DESTDIR            = ./Distr
MOC_DIR            = ./Temp
OBJECTS_DIR        = ./Temp
RCC_DIR            = ./Resources
UI_DIR             = ./Ui
