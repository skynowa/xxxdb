#---------------------------------------------------------------------------
#
# \file  XXXDb.pro
# \brief project file
#
#---------------------------------------------------------------------------


TARGET          = XXXDb
TEMPLATE        = app
QT              = core gui widgets sql network xml
CONFIG         += warn_on no_keywords
#CODEC           = UTF-8

CONFIG(debug, debug | release) {
    #CONFIG     += console
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
                  Forms/CColumns.cpp \
                  Forms/CAbout.cpp

FORMS           = Forms/CMain.ui \
                  Forms/CEditor.ui \
                  Forms/CAlbum.ui \
                  Forms/CColumns.ui \
                  Forms/CAbout.ui

RESOURCES       = Resources/App.qrc \
                  #Langs/Langs.qrc

win32 {
    RC_FILE     = Resources/App_win.rc
}

TRANSLATIONS   += Langs/XXXDb_ru_RU.ts

CONFIG(debug, debug | release) {
    DISTR_DIR   = ./Distr/Debug
    OUT_DIR     = ./Build/Debug
} else {
    DISTR_DIR   = ./Distr/Release
    OUT_DIR     = ./Build/Release
}

DESTDIR         = "$$DISTR_DIR"
MOC_DIR         = "$$OUT_DIR/Temp"
OBJECTS_DIR     = "$$OUT_DIR/Temp"
RCC_DIR         = "$$OUT_DIR/Temp"
UI_DIR          = "$$OUT_DIR/Ui"
