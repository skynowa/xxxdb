#---------------------------------------------------------------------------
#
# \file  PickupDB.pro
# \brief project file
#
#---------------------------------------------------------------------------


TARGET          = PickupDB
TEMPLATE        = app
QT              = core gui widgets sql network xml
CONFIG         += warn_on

win32 {
    INCLUDEPATH =

    CONFIG(debug, debug|release) {
        LIBS    =
    } else {
        LIBS    =
    }
}
unix {
    INCLUDEPATH =

    CONFIG(debug, debug|release) {
        LIBS    =
    } else {
        LIBS    =
    }

    LIBS       +=
}

HEADERS         = QtLib/Common.h \
                  QtLib/CUtils.h \
                  QtLib/CSqlNavigator.h \
                  Config.h \
                  Classes/CSettings.h \
                  Classes/CDelegateDbImage.h \
                  Classes/CDbImageLabel.h \
                  Forms/CMain.h \
                  Forms/CEditor.h \
                  Forms/CAlbum.h

SOURCES         = main.cpp \
                  QtLib/CUtils.cpp \
                  QtLib/CSqlNavigator.cpp \
                  Classes/CSettings.cpp \
                  Classes/CDelegateDbImage.cpp \
                  Classes/CDbImageLabel.cpp \
                  Forms/CMain.cpp \
                  Forms/CEditor.cpp \
                  Forms/CAlbum.cpp

FORMS           = Forms/CMain.ui \
                  Forms/CEditor.ui \
                  Forms/CAlbum.ui

RESOURCES       = Resources/App.qrc

win32 {
    RC_FILE     = Resources/App_win.rc
}
unix {
    RC_FILE     = # n/a
}

OUT_DIR         =

CONFIG(debug, debug|release) {
    OUT_DIR    = ./Build/Debug
} else {
    OUT_DIR    = ./Build/Release
}

DESTDIR         = "$$OUT_DIR/Distr"
MOC_DIR         = "$$OUT_DIR/Temp"
OBJECTS_DIR     = "$$OUT_DIR/Temp"
RCC_DIR         = "$$OUT_DIR/Temp"
UI_DIR          = "$$OUT_DIR/Ui"
