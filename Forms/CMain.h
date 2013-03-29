/**
 * \file   CMain.h
 * \brief  main widget
 */


#ifndef XXXDb_CMainH
#define XXXDb_CMainH
//------------------------------------------------------------------------------
#include "ui_CMain.h"

#include "../QtLib/Common.h"
#include "../QtLib/CSqlNavigator.h"
#include "../Config.h"
//------------------------------------------------------------------------------
class CSettings;
class CAlbum;
class CDbImageLabel;

class CMain :
    public QMainWindow
{
    Q_OBJECT

public:
    friend class CSettings;

    Ui::CMainClass  ui;
    CSqlNavigator   snNavigator;
    CAlbum         *wndAlbum;

                    CMain               (QWidget *parent, Qt::WindowFlags flags);

protected:
    virtual void    keyPressEvent       (QKeyEvent *event);
    virtual void    closeEvent          (QCloseEvent *event);

private:
    CSettings      *_stApp;
    QTranslator    *_trTranslator;
    QString         _sTranslatorLang;
    QSqlDatabase    _dbDatabase;
    QSqlTableModel *_tmModel;
    db_items_t      _hsDbItems;
    CDbImageLabel  *_dbImageLabel;

    QComboBox      *_cboFindText;
    QComboBox      *_cboDbFields;

    void            _construct          ();
    void            _destruct           ();
    void            _initMain           ();
    void            _initModel          ();
    void            _initActions        ();

    // slots
    // group "Exit"
    void            slot_OnExit         ();

    // group "Edit"
    void            slot_OnFirst        ();
    void            slot_OnPrior        ();
    void            slot_OnNext         ();
    void            slot_OnLast         ();
    void            slot_OnGoTo         ();
    void            slot_OnInsert       ();
    void            slot_OnRemove       ();
    void            slot_OnEdit         ();

    // group "Find"
    void            slot_OnSearch       ();
    void            slot_OnTextClear    ();

    // group "View"
    void            slot_OnMainToolbar  ();
    void            slot_OnQuickFindToolbar();
    void            slot_OnColumns      ();
    void            slot_OnStatusbar    ();
    void            slot_OnLanguageEn   ();
    void            slot_OnLanguageRu   ();

    // group "Options"
    void            slot_OnSettings     ();

    // group "Help"
    void            slot_OnFaq          ();
    void            slot_OnAbout        ();

    // photo
    void            slot_OnAlbum        ();

    void            slot_OnQuickFind    (cQString &arg);
    void            slot_OnDbFieldChange(cQString &arg);
};
//------------------------------------------------------------------------------
#endif // XXXDb_CMainH
