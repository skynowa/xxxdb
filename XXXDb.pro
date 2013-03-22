#---------------------------------------------------------------------------
#
# \file  XXXDb.pro
# \brief project file
#
#---------------------------------------------------------------------------


TARGET          = XXXDb
TEMPLATE        = app
QT              = core gui widgets sql network xml
CONFIG         += warn_on

HEADERS         = QtLib/Common.h \
                  QtLib/CUtils.h \
                  QtLib/CSqlNavigator.h \
                  Config.h \
                  Classes/CSettings.h \
                  Classes/CDelegateDbImage.h \
                  Classes/CDbImageLabel.h \
                  Forms/CMain.h \
                  Forms/CEditor.h \
                  Forms/CAlbum.h \
                  Forms/CAbout.h \
                  Forms/CColumns.h

SOURCES         = main.cpp \
                  QtLib/CUtils.cpp \
                  QtLib/CSqlNavigator.cpp \
                  Classes/CSettings.cpp \
                  Classes/CDelegateDbImage.cpp \
                  Classes/CDbImageLabel.cpp \
                  Forms/CMain.cpp \
                  Forms/CEditor.cpp \
                  Forms/CAlbum.cpp \
                  Forms/CAbout.cpp \
                  Forms/CColumns.cpp

FORMS           = Forms/CMain.ui \
                  Forms/CEditor.ui \
                  Forms/CAlbum.ui \
                  Forms/CAbout.ui \
                  Forms/CColumns.ui

RESOURCES       = Resources/App.qrc

win32 {
    RC_FILE     = Resources/App_win.rc
}

OUT_DIR         =

CONFIG(debug, debug | release) {
    OUT_DIR    = ./Build/Debug
} else {
    OUT_DIR    = ./Build/Release
}

DESTDIR         = "$$OUT_DIR/Distr"
MOC_DIR         = "$$OUT_DIR/Temp"
OBJECTS_DIR     = "$$OUT_DIR/Temp"
RCC_DIR         = "$$OUT_DIR/Temp"
UI_DIR          = "$$OUT_DIR/Ui"
