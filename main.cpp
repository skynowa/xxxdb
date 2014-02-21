/**
 * \file  main.cpp
 * \brief main window
 */


#include <QApplication>
#include "QtLib/Common.h"
#include "QtLib/CUtils.h"
#include <xLib/xLib.h>
#include "QtLib/CApplication.h"
#include "Forms/CMain.h"
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
#if !defined(Q_OS_WIN)
    CxSystemInfo info;
    xCHECK_MSG_RET(info.isUserAdmin(), xT(APP_NAME) xT(": Can't run as root"), EXIT_FAILURE);
#endif

    int exitCode = EXIT_FAILURE;

    CApplication::windowActivate(APP_WINDOW_CLASS, APP_NAME);

    bool bRv = CApplication::isRunnig(APP_GUID);
    if (bRv) {
        std::wcerr << "Application is already running." << std::endl;
        return EXIT_SUCCESS;
    }

#if 1
    bRv = CApplication::selfCheck();
    qCHECK_RET(!bRv, EXIT_FAILURE);
#endif

    CApplication::setOrganizationName(APP_ORG);
    CApplication::setApplicationName(APP_NAME);
    CApplication::setApplicationVersion(APP_VERSION);

    // start application
    {
        CApplication app(argc, argv);
        app.addLibraryPath( app.applicationDirPath() + "/" + APP_PLUGINS_DIR_NAME);

        bRv = QDir( app.dbFilePath() ).isReadable();
        if (!bRv) {
            std::wcerr << "Missing database file: "
                       << app.dbFilePath().toStdWString()
                       << std::endl;
            return EXIT_FAILURE;
        }

        CMain wndMain(NULL, 0);
        wndMain.show();

        exitCode = app.exec();
    }

    return exitCode;
}
//-------------------------------------------------------------------------------------------------
