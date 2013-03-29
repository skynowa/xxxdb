/**
 * \file   CApplication.cpp
 * \brief  application
 */


#include "CApplication.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CApplication::CApplication(
    int &a_argc, char **a_argv
) :
    QApplication(a_argc, a_argv)
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

        QTextCodec::setCodecForLocale(codec);
    }
}
//------------------------------------------------------------------------------
/* virtual */
CApplication::~CApplication() {

}
//------------------------------------------------------------------------------


/*******************************************************************************
*   public, static
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
void
CApplication::windowActivate(
    cQString &a_appWndClass,
    cQString &a_appName
)
{
    CUtils::applicationActivate(a_appWndClass, a_appName);
}
//------------------------------------------------------------------------------
/* static */
bool
CApplication::isRunnig(
    cQString &a_appGuid
)
{
    return CUtils::setApplicationSingle(a_appGuid);
}
//------------------------------------------------------------------------------
// BUG: CApplication::selfCheck()
/* static */
bool
CApplication::selfCheck() {
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
