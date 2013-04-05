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
CODECFORTR      = UTF-8

CONFIG(debug, debug | release) {
    #CONFIG     += console
}

HEADERS         = QtLib/Common.h \
                  QtLib/CUtils.h \
                  QtLib/CSqlNavigator.h \
                  Classes/CConfig.h \
                  Classes/CIni.h \
                  Classes/CApplication.h \
                  Classes/CDelegateDbImage.h \
                  Classes/CDbImageLabel.h \
                  Forms/CMain.h \
                  Forms/CEditor.h \
                  Forms/CAlbum.h \
                  Forms/CColumns.h \
                  Forms/CAbout.h \
                  Forms/CSettings.h

SOURCES         = main.cpp \
                  QtLib/CUtils.cpp \
                  QtLib/CSqlNavigator.cpp \
                  Classes/CConfig.cpp \
                  Classes/CIni.cpp \
                  Classes/CApplication.cpp \
                  Classes/CDelegateDbImage.cpp \
                  Classes/CDbImageLabel.cpp \
                  Forms/CMain.cpp \
                  Forms/CEditor.cpp \
                  Forms/CAlbum.cpp \
                  Forms/CColumns.cpp \
                  Forms/CAbout.cpp \
                  Forms/CSettings.cpp

FORMS           = Forms/CMain.ui \
                  Forms/CEditor.ui \
                  Forms/CAlbum.ui \
                  Forms/CColumns.ui \
                  Forms/CAbout.ui \
                  Forms/CSettings.ui

RESOURCES       = Resources/App.qrc

win32 {
    RC_FILE     = Resources/App_win.rc
}

CONFIG(debug, debug | release) {
    DISTR_DIR   = Distr/Debug
    OUT_DIR     = Build/Debug
} else {
    DISTR_DIR   = Distr/Release
    OUT_DIR     = Build/Release
}

TRANSLATIONS   += $$DISTR_DIR/Langs/XXXDb_ru_RU.ts

DESTDIR         = $$DISTR_DIR
MOC_DIR         = $$OUT_DIR/Temp
OBJECTS_DIR     = $$OUT_DIR/Temp
RCC_DIR         = $$OUT_DIR/Temp
UI_DIR          = $$OUT_DIR/Ui
