/**
 * \file   CSettings.cpp
 * \brief  application settings
 */


#include "CSettings.h"

#include "../Forms/CMain.h"
#include "../Forms/CEditor.h"
#include "../Forms/CAlbum.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CSettings::CSettings(
    CMain   *a_wndMain,
    CEditor *a_wndEditor,
    CAlbum  *a_wndAlbum
) :
    _m_wndMain  (a_wndMain),
    _m_wndEditor(a_wndEditor),
    _m_wndAlbum (a_wndAlbum)
{
    qDebug() << "_read";

    _read(_m_wndMain);
    _read(_m_wndEditor);
    _read(_m_wndAlbum);
}
//------------------------------------------------------------------------------
CSettings::~CSettings() {
    qDebug() << "_write";

    _write(_m_wndMain);
    _write(_m_wndEditor);
    _write(_m_wndAlbum);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private, CMain
*
*******************************************************************************/

//------------------------------------------------------------------------------
template <typename T>
void
CSettings::_commonRead(
    T *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    QSize  szSize;
    QPoint pnPosition;

    // read
    {
        QSettings stApp(INI_FILE_PATH, QSettings::IniFormat);

        stApp.beginGroup( a_wnd->objectName() );
        szSize     = stApp.value("size",     APP_SIZE).toSize();
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
template <typename T>
void
CSettings::_commonWrite(
    T *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    // write
    QSettings stApp(INI_FILE_PATH, QSettings::IniFormat);

    stApp.beginGroup( a_wnd->objectName() );
    stApp.setValue("position", a_wnd->pos());
    stApp.setValue("size",     a_wnd->size());
    stApp.endGroup();
}
//------------------------------------------------------------------------------
void
CSettings::_read(
    CMain *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonRead(a_wnd);

    // TODO: CMain
}
//------------------------------------------------------------------------------
void
CSettings::_write(
    CMain *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonWrite(a_wnd);

    // TODO: CMain
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private, CEditor
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CSettings::_read(
    CEditor *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonRead(a_wnd);

    // TODO: CEditor
}
//------------------------------------------------------------------------------
void
CSettings::_write(
    CEditor *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonWrite(a_wnd);

    // TODO: CEditor
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private, CAlbum
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CSettings::_read(
    CAlbum *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonRead(a_wnd);

    // TODO: CAlbum
}
//------------------------------------------------------------------------------
void
CSettings::_write(
    CAlbum *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonWrite(a_wnd);

    // TODO: CAlbum
}
//------------------------------------------------------------------------------
