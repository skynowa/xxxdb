/**
 * \file  main.cpp
 * \brief main window
 */


#include <QtGui/QApplication>
#include "Forms/CMain.h"

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
#if defined(Q_WS_WIN)
    cQByteArray codecName = "Windows-1251";
#else
    cQByteArray codecName = "UTF-8";
#endif

    // set codecs
    {
        QTextCodec *codec = QTextCodec::codecForName(codecName);
        Q_ASSERT(NULL != codec);

        QTextCodec::setCodecForTr(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForLocale(codec);
    }

    // application single instance
    {
        bool bRes = false;

        static QSharedMemory smLocker(GUID);

        bRes = smLocker.attach();
        qCHECK_RET(true == bRes, EXIT_SUCCESS);

        bRes = smLocker.create(1);
        qCHECK_RET(false == bRes, EXIT_SUCCESS);
    }

    QApplication apApplication(argc, argv);

    QCoreApplication::setOrganizationName(ORG_NAME);
    QCoreApplication::setApplicationName(APP_NAME);

    CMain wndMain;
    wndMain.show();

    int iRv = apApplication.exec();

    return iRv;
}
//------------------------------------------------------------------------------
