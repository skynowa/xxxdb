/**
 * \file   main.cpp
 * \brief  main module
 */


#include "CMain.h"

#include <QtGui>
#include <QApplication>
//---------------------------------------------------------------------------
int 
main(
    int   argc, 
    char *argv[]
)
{
    QApplication apApplication(argc, argv);
    CMain        wdgMain;

    (void)wdgMain.show();

    int iRes = apApplication.exec();

    return iRes;
}
//---------------------------------------------------------------------------
