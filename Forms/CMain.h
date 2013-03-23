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

class CMain :
    public QMainWindow
{
    Q_OBJECT

public:
    friend class CSettings;

    Ui::CMainClass     ui;
    QString            sAppName;
    QString            sAppDir;
    QString            sDbDir;
    QString            sDbBackupDir;
    CSqlNavigator      snSqlNavigator;
    CAlbum            *wndAlbum;

    explicit           CMain            (QWidget *parent = NULL,
                                         Qt::WindowFlags flags = NULL);

protected:
    virtual void       closeEvent       (QCloseEvent *event);
    virtual void       keyPressEvent    (QKeyEvent *event);

private:
    CSettings         *_stApp;
    QSqlDatabase       _dbDatabase;
    QSqlTableModel    *_tmModel;
    db_items_t         _hsDbItems;
    QDataWidgetMapper *_dmImage;

    void               _construct       ();
    void               _destruct        ();
    void               _initMain        ();
    void               _initModel       ();
    void               _initActions     ();

    // slots
    // group "Exit"
    void               slot_OnExit      ();

    // group "Edit"
    void               slot_OnFirst     ();
    void               slot_OnPrior     ();
    void               slot_OnNext      ();
    void               slot_OnLast      ();
    void               slot_OnGoTo      ();
    void               slot_OnInsert    ();
    void               slot_OnRemove    ();
    void               slot_OnEdit      ();

    // group "Find"
    void               slot_OnSearch    ();

    // group "View"
    void               slot_OnColumns   ();


    // group "Options"
    void               slot_OnSettings  ();

    // group "Help"
    void               slot_OnFaq       ();
    void               slot_OnAbout     ();

    // photo
    void               slot_OnAlbum     ();
};
//------------------------------------------------------------------------------
#endif // XXXDb_CMainH
