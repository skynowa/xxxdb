#---------------------------------------------------------------------------
#
# \file  PickupDB.pro
# \brief project file
#
#---------------------------------------------------------------------------


TARGET          = PickupDB
TEMPLATE        = app
QT              = core gui sql network xml
CONFIG         += warn_on

win32 {
    INCLUDEPATH =

    CONFIG(debug, debug|release) {
        LIBS    =
    } else {
        LIBS    =
    }

    LIBS       += User32.lib Ole32.lib Advapi32.lib shell32.lib
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
                  Classes/CDelegateDbImage.h \
                  Classes/CDbImage.h \
                  Classes/CImageItem.h \
                  Forms/CMain.h \
                  Forms/CPersonEdit.h \
                  Forms/CPhotoAlbum.h

SOURCES         = main.cpp \
                  QtLib/CUtils.cpp \
                  QtLib/CSqlNavigator.cpp \
                  Classes/CDelegateDbImage.cpp \
                  Classes/CDbImage.cpp \
                  Classes/CImageItem.cpp \
                  Forms/CMain.cpp \
                  Forms/CPersonEdit.cpp \
                  Forms/CPhotoAlbum.cpp

FORMS           = Forms/CMain.ui \
                  Forms/CPersonEdit.ui \
                  Forms/CPhotoAlbum.ui

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
