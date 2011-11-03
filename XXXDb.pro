TEMPLATE    = app

TARGET      = XXXDb

QT          += core gui sql

HEADERS     += CMain.h \
               Classes/CSqlCryptTableModel.h

SOURCES     += main.cpp \
               CMain.cpp \
               Classes/CSqlCryptTableModel.cpp

INCLUDEPATH += /home/sergey/Coding/xLib/
#LIBS        += libxlib.a
    
FORMS       += CMain.ui

RESOURCES   +=
