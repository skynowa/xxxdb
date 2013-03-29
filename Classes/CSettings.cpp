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
    _get(_wndMain);
    _get(_wndEditor);
    _get(_wndAlbum);
}
//------------------------------------------------------------------------------
CSettings::~CSettings() {
    _set(_wndMain);
    _set(_wndEditor);
    _set(_wndAlbum);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private, CMain
*
*******************************************************************************/

//------------------------------------------------------------------------------
template <typename T>
void
CSettings::_commonGet(
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
CSettings::_commonSet(
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
CSettings::_get(
    CMain *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    // translator
    {
        _stApp.beginGroup(a_wnd->objectName() + "/view");

        cQString sLanguage = _stApp.value("language", QString()).toString();

        // apply
        if (LANGS_FILE_NAME_RU == sLanguage) {
            a_wnd->ui.actViewLanguage_Ru->setChecked(true);
            a_wnd->slot_OnLanguageRu();
        } else {
            // QString() - default language
            a_wnd->ui.actViewLanguage_En->setChecked(true);
            a_wnd->slot_OnLanguageEn();
        }

        _stApp.endGroup();
    }

    _commonGet(a_wnd);

    // toolbars
    {
        _stApp.beginGroup(a_wnd->objectName() + "/view");

        // ui.tbMain
        {
            cbool isVisible = _stApp.value("toolbar_main/visible", true).toBool();

            // apply
            a_wnd->ui.actView_MainToolbar->setChecked(isVisible);
            a_wnd->ui.tbMain->setVisible(isVisible);
        }

        // ui.tbQuickFind
        {
            cbool isVisible = _stApp.value("toolbar_quickfind/visible", true).toBool();

            // apply
            a_wnd->ui.actView_QuickFindToolbar->setChecked(isVisible);
            a_wnd->ui.tbQuickFind->setVisible(isVisible);
        }

        _stApp.endGroup();
    }

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

    // ui.sbInfo
    {
        _stApp.beginGroup(a_wnd->objectName() + "/view");

        cbool isVisible = _stApp.value("statusbar/visible", true).toBool();

        // apply
        a_wnd->ui.actView_Statusbar->setChecked(isVisible);
        a_wnd->ui.sbInfo->setVisible(isVisible);

        _stApp.endGroup();
    }
}
//------------------------------------------------------------------------------
void
CSettings::_set(
    CMain *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    // translator
    {
        _stApp.beginGroup(a_wnd->objectName() + "/view");

        cQString sLanguage = a_wnd->_sTranslatorLang;
        _stApp.setValue("language", sLanguage);

        _stApp.endGroup();
    }

    _commonSet(a_wnd);

    // toolbars
    {
        _stApp.beginGroup(a_wnd->objectName() + "/view");

        // ui.tbMain
        {
            cbool isVisible = a_wnd->ui.tbMain->isVisible();

            _stApp.setValue("toolbar_main/visible", isVisible);
        }

        // ui.tbQuickFind
        {
            cbool isVisible = a_wnd->ui.tbQuickFind->isVisible();

            _stApp.setValue("toolbar_quickfind/visible", isVisible);
        }

        _stApp.endGroup();
    }

    // caption for DB fields
    {
        _stApp.beginGroup(a_wnd->objectName() + "/table");

        for (int i = 0; i < a_wnd->_tmModel->columnCount(); ++ i) {
            cbool isVisible = !a_wnd->ui.tvInfo->isColumnHidden(i);

            _stApp.setValue(QString("column%1/visible").arg(i), isVisible);
        }

        _stApp.endGroup();
    }

    // ui.sbInfo
    {
        _stApp.beginGroup(a_wnd->objectName() + "/view");

        cbool isVisible = a_wnd->ui.sbInfo->isVisible();
        _stApp.setValue("statusbar/visible", isVisible);

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
CSettings::_get(
    CEditor *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonGet(a_wnd);
}
//------------------------------------------------------------------------------
void
CSettings::_set(
    CEditor *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonSet(a_wnd);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private, CAlbum
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CSettings::_get(
    CAlbum *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonGet(a_wnd);
}
//------------------------------------------------------------------------------
void
CSettings::_set(
    CAlbum *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonSet(a_wnd);
}
//------------------------------------------------------------------------------
