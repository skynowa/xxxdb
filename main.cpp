#include "CMain.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMain w;
    w.show();
    return a.exec();
}
