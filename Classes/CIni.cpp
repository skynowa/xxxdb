/**
 * \file   CIni.cpp
 * \brief  application settings
 */


#include "CIni.h"

#include "../QtLib/CApplication.h"
#include "../Forms/CMain.h"
#include "../Forms/CEditor.h"
#include "../Forms/CAlbum.h"


QSettings *CIni::_iniApp                  = NULL;
bool       CIni::_photos_isDeleteFromDisk = false;

/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CIni::CIni()
{
}
//------------------------------------------------------------------------------
CIni::~CIni()
{
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
void
CIni::construct()
{
    qTEST(_iniApp == NULL);

    _iniApp = new QSettings(CApplication::iniFilePath(), QSettings::IniFormat);

    _load();
}
//------------------------------------------------------------------------------
/* static */
void
CIni::destruct()
{
    _save();

    qTEST(_iniApp != NULL);
    qPTR_DELETE(_iniApp);
}
//------------------------------------------------------------------------------
void
CIni::get(
    CEditor *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonGet(a_wnd);
}
//------------------------------------------------------------------------------
void
CIni::set(
    CEditor *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonSet(a_wnd);
}
//------------------------------------------------------------------------------
void
CIni::get(
    CAlbum *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonGet(a_wnd);
}
//------------------------------------------------------------------------------
void
CIni::set(
    CAlbum *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    _commonSet(a_wnd);
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
bool
CIni::photos_isDeleteFromDisk()
{
    return _photos_isDeleteFromDisk;
}
//------------------------------------------------------------------------------
/* static */
void
CIni::setPhotos_isDeleteFromDisk(
    const bool &a_value
)
{
    _photos_isDeleteFromDisk = a_value;
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
void
CIni::_load()
{
    // _photos_isDeleteFromDisk
    {
        _iniApp->beginGroup("data");
        cbool value = _iniApp->value("_photos_isDeleteFromDisk", false).toBool();
        _iniApp->endGroup();

        setPhotos_isDeleteFromDisk(value);
    }
}
//------------------------------------------------------------------------------
/* static */
void
CIni::_save()
{
    // _photos_isDeleteFromDisk
    {
        _iniApp->beginGroup("data");
        _iniApp->setValue("_photos_isDeleteFromDisk", photos_isDeleteFromDisk());
        _iniApp->endGroup();
    }
}
//------------------------------------------------------------------------------
template <typename T>
void
CIni::_commonGet(
    T *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    QSize  szSize;
    QPoint pnPosition;

    // read
    {
        _iniApp->beginGroup( a_wnd->objectName() );
        szSize     = _iniApp->value("size",     APP_SIZE).toSize();
        pnPosition = _iniApp->value("position", QPoint(200, 200)).toPoint();
        _iniApp->endGroup();
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
CIni::_commonSet(
    T *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    // write
    _iniApp->beginGroup( a_wnd->objectName() );
    _iniApp->setValue("position", a_wnd->pos());
    _iniApp->setValue("size",     a_wnd->size());
    _iniApp->endGroup();
}
//------------------------------------------------------------------------------
void
CIni::get(
    CMain *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    // translator
    {
        _iniApp->beginGroup(a_wnd->objectName() + "/view");

        cQString sLanguage = _iniApp->value("language", QString()).toString();

        // apply
        if (LANGS_FILE_NAME_RU == sLanguage) {
            a_wnd->ui.actViewLanguage_Ru->setChecked(true);
            a_wnd->actView_onLanguageRu();
        } else {
            // QString() - default language
            a_wnd->ui.actViewLanguage_En->setChecked(true);
            a_wnd->actView_onLanguageEn();
        }

        _iniApp->endGroup();
    }

    _commonGet(a_wnd);

    // toolbars
    {
        _iniApp->beginGroup(a_wnd->objectName() + "/view");

        // ui.tbMain
        {
            cbool isVisible = _iniApp->value("toolbar_main/visible", true).toBool();

            // apply
            a_wnd->ui.actView_MainToolbar->setChecked(isVisible);
            a_wnd->ui.tbMain->setVisible(isVisible);
        }

        // ui.tbQuickFind
        {
            cbool isVisible = _iniApp->value("toolbar_quickfind/visible", true).toBool();

            // apply
            a_wnd->ui.actView_QuickFindToolbar->setChecked(isVisible);
            a_wnd->ui.tbQuickFind->setVisible(isVisible);
        }

        _iniApp->endGroup();
    }

    // caption for DB fields
    {
        _iniApp->beginGroup(a_wnd->objectName() + "/table");

        for (int i = 0; i < a_wnd->_tmModel->columnCount(); ++ i) {
            cbool isVisible = _iniApp->value(QString("column%1/visible").arg(i), true).toBool();

            // apply
            a_wnd->ui.tvInfo->setColumnHidden(i, !isVisible);
        }

        _iniApp->endGroup();
    }

    // ui.sbInfo
    {
        _iniApp->beginGroup(a_wnd->objectName() + "/view");

        // ui.splitter
        {
            cQByteArray state = _iniApp->value("spliter/state", "").toByteArray();

            // apply
            a_wnd->ui.splitter->restoreState(state);
        }

        // ui.tabInfo
        {
            cint tabIndex = _iniApp->value("tab_index", 0).toInt();
            a_wnd->ui.tabInfo->setCurrentIndex(tabIndex);
        }

        // ui.sbInfo
        {
            cbool isVisible = _iniApp->value("statusbar/visible", true).toBool();

            // apply
            a_wnd->ui.actView_Statusbar->setChecked(isVisible);
            a_wnd->ui.sbInfo->setVisible(isVisible);
        }

        _iniApp->endGroup();
    }
}
//------------------------------------------------------------------------------
void
CIni::set(
    CMain *a_wnd
)
{
    qCHECK_DO(a_wnd == NULL, return);

    // translator
    {
        _iniApp->beginGroup(a_wnd->objectName() + "/view");

        cQString sLanguage = a_wnd->_sTranslatorLang;
        _iniApp->setValue("language", sLanguage);

        _iniApp->endGroup();
    }

    _commonSet(a_wnd);

    // toolbars
    {
        _iniApp->beginGroup(a_wnd->objectName() + "/view");

        // ui.tbMain
        {
            cbool isVisible = a_wnd->ui.tbMain->isVisible();

            _iniApp->setValue("toolbar_main/visible", isVisible);
        }

        // ui.tbQuickFind
        {
            cbool isVisible = a_wnd->ui.tbQuickFind->isVisible();

            _iniApp->setValue("toolbar_quickfind/visible", isVisible);
        }

        _iniApp->endGroup();
    }

    // caption for DB fields
    {
        _iniApp->beginGroup(a_wnd->objectName() + "/table");

        for (int i = 0; i < a_wnd->_tmModel->columnCount(); ++ i) {
            cbool isVisible = !a_wnd->ui.tvInfo->isColumnHidden(i);

            _iniApp->setValue(QString("column%1/visible").arg(i), isVisible);
        }

        _iniApp->endGroup();
    }

    // ui.sbInfo
    {
        _iniApp->beginGroup(a_wnd->objectName() + "/view");

        cQByteArray state = a_wnd->ui.splitter->saveState();
        _iniApp->setValue("spliter/state", state);

        cint tabIndex = a_wnd->ui.tabInfo->currentIndex();
        _iniApp->setValue("tab_index", tabIndex);

        cbool isVisible = a_wnd->ui.sbInfo->isVisible();
        _iniApp->setValue("statusbar/visible", isVisible);

        _iniApp->endGroup();
    }
}
//------------------------------------------------------------------------------
