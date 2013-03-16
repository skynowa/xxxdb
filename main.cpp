/**
 * \file  main.cpp
 * \brief main window
 */


#include <QApplication>
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "Forms/CMain.h"

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    int iExitCode = EXIT_FAILURE;

#if defined(Q_WS_WIN)
    cQByteArray codecName = "Windows-1251";
#else
    cQByteArray codecName = "UTF-8";
#endif

    // set codecs
    {
        QTextCodec *codec = QTextCodec::codecForName(codecName);
        Q_ASSERT(NULL != codec);

        QTextCodec::setCodecForLocale(codec);
    }

    // activation application window
    CUtils::applicationActivate(APP_WINDOW_CLASS, APP_NAME);

    // set application single inststance
    {
        bool bRv = CUtils::setApplicationSingle(APP_GUID);
        qCHECK_RET(!bRv, EXIT_SUCCESS);
    }

    // start application
    {
        QApplication apApplication(argc, argv);

        QCoreApplication::setOrganizationName(APP_ORG);
        QCoreApplication::setApplicationName(APP_NAME);

        CMain wndMain;
        wndMain.show();

        iExitCode = apApplication.exec();
    }

    return iExitCode;
}
//------------------------------------------------------------------------------
