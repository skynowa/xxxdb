/**
 * \file   main.cpp
 * \brief  main module
 */



#include "CMain.h"
#include <QtGui/QApplication>
//---------------------------------------------------------------------------
int
main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    CMain w;
    w.show();

    return a.exec();
}
//---------------------------------------------------------------------------
