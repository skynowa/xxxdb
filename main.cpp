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

    int iExitCode = EXIT_FAILURE;

    CApplication::windowActivate(APP_WINDOW_CLASS, APP_NAME);

    bool bRv = CApplication::isRunnig(APP_GUID);
    qCHECK_RET(!bRv, EXIT_SUCCESS);

#if 0
    bRv = CApplication::selfCheck();
    qCHECK_RET(!bRv, EXIT_FAILURE);
#endif

    CApplication::setOrganizationName(APP_ORG);
    CApplication::setApplicationName(APP_NAME);
    CApplication::setApplicationVersion(APP_VERSION);

    // start application
    {
        CApplication apApp(argc, argv);
        apApp.addLibraryPath( apApp.applicationDirPath() + "/" + APP_PLUGINS_DIR_NAME);

        bRv = QDir( apApp.dbFilePath() ).isReadable();
        if (!bRv) {
            std::wcerr << "Missing database file: "
                       << apApp.dbFilePath().toStdWString()
                       << std::endl;
            return EXIT_FAILURE;
        }



        CMain wndMain(NULL, 0);
        wndMain.show();

        iExitCode = apApp.exec();
    }

    return iExitCode;
}
//-------------------------------------------------------------------------------------------------
