#-------------------------------------------------------------------------------
#
# \file  XXXDb.pro
# \brief project file
#
#-------------------------------------------------------------------------------


TARGET           = XXXDb
VERSION          = 1.0.0
TEMPLATE         = app
QT               = core gui widgets sql network xml
CONFIG          += release warn_on no_keywords
DEFINES         += qTEST_IS_USED=1
CODECFORTR       = UTF-8

CONFIG(debug, debug | release) {
    #CONFIG      += console
}

win32 {
    QT_DIR       = D:/Libs/Qt/5.1.0_mingw_48_x32
}
unix {
    QT_DIR       = /opt/Libs/Qt/5.2.0_x64
}

# libs
# suppress the default RPATH if you wish
# QMAKE_LFLAGS_RPATH=
# add your own with quoting gyrations to make sure $ORIGIN gets to the command line unexpanded
QMAKE_LFLAGS    += "-Wl,-rpath,\'\$$ORIGIN\'"
# or for a subdir of your install
QMAKE_LFLAGS    += "-Wl,-rpath,\'\$$ORIGIN/Plugins\'"

INCLUDEPATH     += . Widgets xLib/Include

CONFIG(debug, debug | release) {
    LIBS        += -L./Distr/Debug/Plugins -lCDbImagePlugin
} else {
    LIBS        += -L./Distr/Release/Plugins -lCDbImagePlugin
}

# project
HEADERS          = QtLib/Common.h \
                   QtLib/CUtils.h \
                   QtLib/CSqlNavigator.h \
                   QtLib/CApplication.h \
                   Classes/CConfig.h \
                   Classes/CIni.h \
                   Forms/CMain.h \
                   Forms/CAlbum.h \
                   Forms/CColumns.h \
                   Forms/CAbout.h \
                   Forms/CSettings.h

SOURCES          = main.cpp \
                   QtLib/CUtils.cpp \
                   QtLib/CSqlNavigator.cpp \
                   QtLib/CApplication.cpp \
                   Classes/CConfig.cpp \
                   Classes/CIni.cpp \
                   Forms/CMain.cpp \
                   Forms/CAlbum.cpp \
                   Forms/CColumns.cpp \
                   Forms/CAbout.cpp \
                   Forms/CSettings.cpp

FORMS            = Forms/CMain.ui \
                   Forms/CAlbum.ui \
                   Forms/CColumns.ui \
                   Forms/CAbout.ui \
                   Forms/CSettings.ui

RESOURCES        = Resources/App.qrc

win32 {
    RC_FILE      = Resources/App_win.rc
}

CONFIG(debug, debug | release) {
    DISTR_DIR    = Distr/Debug
    OUT_DIR      = Build/Debug
} else {
    DISTR_DIR    = Distr/Release
    OUT_DIR      = Build/Release
}

TRANSLATIONS    += $$DISTR_DIR/Langs/XXXDb_ru_RU.ts

DESTDIR          = $$DISTR_DIR
MOC_DIR          = $$OUT_DIR/Temp
OBJECTS_DIR      = $$OUT_DIR/Temp
RCC_DIR          = $$OUT_DIR/Temp
UI_DIR           = $$OUT_DIR/Ui
