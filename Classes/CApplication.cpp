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
    // set codecs
    {
        QTextCodec *codec = QTextCodec::codecForName(APP_LOCALE_CODEC);
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
QString
CApplication::iniFilePath() {
    return applicationFilePath() + INI_FILE_EXT;
}
//------------------------------------------------------------------------------
/* static */
QString
CApplication::langsDirPath() {
    return applicationDirPath() + QDir::separator() + LANGS_DIR_NAME;
}
//------------------------------------------------------------------------------
/* static */
QString
CApplication::dbDirPath() {
    return applicationDirPath() + QDir::separator() + DB_DIR_NAME;
}
//------------------------------------------------------------------------------
/* static */
QString
CApplication::dbFilePath() {
    return dbDirPath() + QDir::separator() + applicationName() + DB_FILE_EXT;
}
//------------------------------------------------------------------------------
/* static */
QString
CApplication::dbBackupDirPath() {
    return dbDirPath() + QDir::separator() + BACKUP_DIR_NAME;
}
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
