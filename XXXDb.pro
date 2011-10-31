TEMPLATE = app
TARGET = XXXDb

QT        += core gui sql

HEADERS   += CMain.h \
    Classes/CSqlCryptTableModel.h


SOURCES   += main.cpp \
    CMain.cpp \
    Classes/CSqlCryptTableModel.cpp


FORMS     += CMain.ui
RESOURCES +=
