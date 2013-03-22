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
    _stApp    (INI_FILE_PATH, QSettings::IniFormat),
    _wndMain  (a_wndMain),
    _wndEditor(a_wndEditor),
    _wndAlbum (a_wndAlbum)
{
    _read(_wndMain);
    _read(_wndEditor);
    _read(_wndAlbum);
}
//------------------------------------------------------------------------------
CSettings::~CSettings() {
    _write(_wndMain);
    _write(_wndEditor);
    _write(_wndAlbum);
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
        _stApp.beginGroup( a_wnd->objectName() );
        szSize     = _stApp.value("size",     APP_SIZE).toSize();
        pnPosition = _stApp.value("position", QPoint(200, 200)).toPoint();
        _stApp.endGroup();
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
    _stApp.beginGroup( a_wnd->objectName() );
    _stApp.setValue("position", a_wnd->pos());
    _stApp.setValue("size",     a_wnd->size());
    _stApp.endGroup();
}
//------------------------------------------------------------------------------
void
CSettings::_read(
    CMain *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonRead(a_wnd);

    // caption for DB fields
    {
        _stApp.beginGroup(a_wnd->objectName() + "/table");

        for (int i = 0; i < a_wnd->_tmModel->columnCount(); ++ i) {
            cbool isVisible = _stApp.value(QString("column%1/visible").arg(i), true).toBool();

            // apply
            a_wnd->ui.tvInfo->setColumnHidden(i, !isVisible);
        }

        _stApp.endGroup();
    }
}
//------------------------------------------------------------------------------
void
CSettings::_write(
    CMain *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonWrite(a_wnd);

    // caption for DB fields
    {
        _stApp.beginGroup(a_wnd->objectName() + "/table");

        for (int i = 0; i < a_wnd->_tmModel->columnCount(); ++ i) {
            cbool isVisible = !a_wnd->ui.tvInfo->isColumnHidden(i);

            _stApp.setValue(QString("column%1/visible").arg(i), isVisible);
        }

        _stApp.endGroup();
    }
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
}
//------------------------------------------------------------------------------
void
CSettings::_write(
    CEditor *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonWrite(a_wnd);
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
}
//------------------------------------------------------------------------------
void
CSettings::_write(
    CAlbum *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonWrite(a_wnd);
}
//------------------------------------------------------------------------------
