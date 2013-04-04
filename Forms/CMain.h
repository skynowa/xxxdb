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
#include "Classes/CConfig.h"
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

                    CMain(QWidget *parent, Qt::WindowFlags flags);

protected:
    virtual void    keyPressEvent(QKeyEvent *event);
    virtual void    changeEvent(QEvent *event);
    virtual void    closeEvent(QCloseEvent *event);

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

    void            _construct();
    void            _destruct();
    void            _initMain();
    void            _initModel();
    void            _initActions();
    void            _retranslateUi();

    // slots
    // group "Exit"
    void            actFile_onExit();

    // group "Edit"
    void            actEdit_onFirst();
    void            actEdit_onPrior();
    void            actEdit_onNext();
    void            actEdit_onLast();
    void            actEdit_onGoTo();
    void            actEdit_onInsert();
    void            actEdit_onRemove();
    void            actEdit_onEdit();
    void            actEdit_onAlbum();

    // group "Find"
    void            actFind_onSearch();
    void            actFind_onTextClear();

    // group "View"
    void            actView_onMainToolbar();
    void            actView_onQuickFindToolbar();
    void            actView_onColumns();
    void            actView_onStatusbar();
    void            actView_onLanguageEn();
    void            actView_onLanguageRu();

    // group "Options"
    void            actOptions_onSettings();

    // group "Help"
    void            actHelp_onFaq();
    void            actHelp_onAbout();

    //
    void            onQuickFind(cQString &arg);
    void            cboDbFields_onCurrentTextChanged(cQString &arg);
};
//------------------------------------------------------------------------------
#endif // XXXDb_CMainH
