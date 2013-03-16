/**
 * \file   CSettings.cpp
 * \brief  application settings
 */


#include "CSettings.h"

#include "../Forms/CMain.h"
#include "../Forms/CPersonEdit.h"
#include "../Forms/CPhotoAlbum.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CSettings::CSettings(
    CMain       *a_wndMain,
    CPersonEdit *a_wndPersonEdit,
    CPhotoAlbum *a_wndPhotoAlbum
) :
    _m_wndMain      (a_wndMain),
    _m_wndPersonEdit(a_wndPersonEdit),
    _m_wndPhotoAlbum(a_wndPhotoAlbum)
{
    qDebug() << "_read";
    _read(_m_wndMain);
    _read(_m_wndPersonEdit);
    _read(_m_wndPhotoAlbum);
}
//------------------------------------------------------------------------------
CSettings::~CSettings() {
    qDebug() << "_write";
    _write(_m_wndMain);
    _write(_m_wndPersonEdit);
    _write(_m_wndPhotoAlbum);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private, CMain
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CSettings::_read(
    CMain *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    QSize  szSize;
    QPoint pnPosition;

    // read
    {
        QSettings stApp(QCoreApplication::applicationFilePath() + INI_FILE_EXT,
                        QSettings::IniFormat);

        stApp.beginGroup("main");
        szSize     = stApp.value("size",     QSize(APP_WIDTH, APP_HEIGHT)).toSize();
        pnPosition = stApp.value("position", QPoint(200, 200)).toPoint();
        stApp.endGroup();
    }

    // apply
    {
        a_wnd->resize(szSize);
        a_wnd->move(pnPosition);
    }
}
//------------------------------------------------------------------------------
void
CSettings::_write(
    CMain *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    // write
    QSettings stApp(QCoreApplication::applicationFilePath() + INI_FILE_EXT,
                    QSettings::IniFormat);

    stApp.beginGroup("main");
    stApp.setValue("position", a_wnd->pos());
    stApp.setValue("size",     a_wnd->size());
    stApp.endGroup();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private, CPersonEdit
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CSettings::_read(
    CPersonEdit *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    // TODO: CPersonEdit
}
//------------------------------------------------------------------------------
void
CSettings::_write(
    CPersonEdit *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    // TODO: CPersonEdit
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private, CPhotoAlbum
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CSettings::_read(
    CPhotoAlbum *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    // TODO: CPhotoAlbum
}
//------------------------------------------------------------------------------
void
CSettings::_write(
    CPhotoAlbum *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    // TODO: CPhotoAlbum
}
//------------------------------------------------------------------------------
