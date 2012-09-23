/**
 * \file  main.cpp
 * \brief main window
 */


#include <QtGui/QApplication>
#include "CMain.h"

//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
#if defined(Q_WS_WIN)
    const QByteArray codecName = "Windows-1251";
#else
    const QByteArray codecName = "UTF-8";
#endif

    // set codecs
    {
        QTextCodec *codec = QTextCodec::codecForName(codecName);
        Q_ASSERT(NULL != codec);

        QTextCodec::setCodecForTr(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForLocale(codec);
    }

    // application single inststance
    {
        bool bRes = false;

        static QSharedMemory smLocker(CONFIG_GUID);

        bRes = smLocker.attach();
        qCHECK_RET(true == bRes, EXIT_SUCCESS);

        bRes = smLocker.create(1);
        qCHECK_RET(false == bRes, EXIT_SUCCESS);
    }

    QApplication apApplication(argc, argv);

    QCoreApplication::setOrganizationName(CONFIG_ORG_NAME);
    QCoreApplication::setApplicationName(CONFIG_APP_NAME);

    CMain wndMain;
    wndMain.show();

    int iRv = apApplication.exec();

    return iRv;
}
//---------------------------------------------------------------------------
