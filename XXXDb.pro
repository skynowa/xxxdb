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
win32:INCLUDEPATH  =

unix: LIBS         =
win32:LIBS         =

HEADERS            = CMain.h \
                     Classes/Common.h \
                     Classes/CSqlNavigator.h

SOURCES            = main.cpp \
                     CMain.cpp \
                     Classes/CSqlNavigator.cpp

FORMS              = Forms/CMain.ui
RESOURCES          =

DESTDIR            = ./Distr
MOC_DIR            = ./Temp
OBJECTS_DIR        = ./Temp
RCC_DIR            = ./Resources
UI_DIR             = ./Ui
