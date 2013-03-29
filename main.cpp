/**
 * \file  main.cpp
 * \brief main window
 */


#include <QApplication>
#include "QtLib/Common.h"
#include "QtLib/CUtils.h"
#include "Forms/CMain.h"
//------------------------------------------------------------------------------
bool applicationSelfCheck();
    ///< application self check
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

    CUtils::applicationActivate(APP_WINDOW_CLASS, APP_NAME);

    bool bRv = CUtils::setApplicationSingle(APP_GUID);
    qCHECK_RET(!bRv, EXIT_SUCCESS);

#if 0
    // BUG: applicationSelfCheck()
    bRv = applicationSelfCheck();
    qCHECK_RET(!bRv, EXIT_FAILURE);
#endif

    // start application
    {
        QApplication apApp(argc, argv);

        apApp.setOrganizationName(APP_ORG);
        apApp.setApplicationName(APP_NAME);
        apApp.setApplicationVersion(APP_VERSION);

        // QTranslator
        {
            QTranslator *translator = new QTranslator;
            QString      alias      = QLocale::system().name();

            bool bRv = translator->load(":/Langs/" + alias);
            Q_ASSERT(bRv);

            apApp.installTranslator(translator);
        }

        CMain wndMain(NULL, 0);
        wndMain.show();

        iExitCode = apApp.exec();
    }

    return iExitCode;
}
//------------------------------------------------------------------------------
bool
applicationSelfCheck() {
    bool bRv = false;

    bRv = QDir(APP_DIR_PLUGIN_PLATFORMS).isReadable();
    if (!bRv) {
        QMessageBox::warning(
            NULL,
            APP_NAME,
            QObject::tr("Plugin directory %1 not exists")
                            .arg(APP_DIR_PLUGIN_PLATFORMS));

        return false;
    }

    bRv = QDir(APP_DIR_PLUGIN_SQLDRIVERS).isReadable();
    if (!bRv) {
        QMessageBox::warning(
            NULL,
            APP_NAME,
            QObject::tr("Plugin directory %1 not exists")
                            .arg(APP_DIR_PLUGIN_SQLDRIVERS));

        return false;
    }

    bRv = QDir(APP_DIR_PLUGIN_IMAGEFORMATS).isReadable();
    if (!bRv) {
        QMessageBox::warning(
            NULL,
            APP_NAME,
            QObject::tr("Plugin directory %1 not exists")
                            .arg(APP_DIR_PLUGIN_IMAGEFORMATS));

        return false;
    }

    return true;
}
//------------------------------------------------------------------------------
