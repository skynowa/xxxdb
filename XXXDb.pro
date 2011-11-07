TEMPLATE = app
TARGET = XXXDb
QT += core gui sql network

INCLUDEPATH += /home/sergey/Coding/xLib/Include/
INCLUDEPATH += /home/sergey/Coding/xLib/Source/

LIBS        += libxlib.a
LIBS        += -lcrypt -lssl -lcrypto



HEADERS += CMain.h \
    Classes/CSqlCryptTableModel.h
SOURCES +=  main.cpp \
    CMain.cpp \
    Classes/CSqlCryptTableModel.cpp


FORMS += CMain.ui
RESOURCES +=
