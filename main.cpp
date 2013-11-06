/**
 * \file  main.cpp
 * \brief main window
 */


#include <QApplication>
#include "QtLib/Common.h"
#include "QtLib/CUtils.h"
#include "QtLib/CApplication.h"
#include "Forms/CMain.h"
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
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

        bRv = QDir( CApplication::dbFilePath() ).isReadable();
        if (!bRv) {
            std::wcerr << "Missing database file: "
                       << CApplication::dbFilePath().toStdWString()
                       << std::endl;
            return EXIT_FAILURE;
        }

        apApp.addLibraryPath(".");

        CMain wndMain(NULL, 0);
        wndMain.show();

        iExitCode = apApp.exec();
    }

    return iExitCode;
}
//------------------------------------------------------------------------------
