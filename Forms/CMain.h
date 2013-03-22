/**
 * \file   CMain.h
 * \brief  main widget
 */


#ifndef PickupDb_CMainH
#define PickupDb_CMainH
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
    Ui::CMainClass     m_Ui;
    QString            m_sAppName;
    QString            m_sAppDir;
    QString            m_sDbDir;
    QString            m_sDbBackupDir;
    CSqlNavigator      m_snSqlNavigator;
    CAlbum            *m_wndAlbum;

    explicit           CMain            (QWidget *parent = 0,
                                         Qt::WindowFlags flags = 0);
    virtual           ~CMain            ();

protected:
    virtual void       closeEvent       (QCloseEvent *event);

private:
    CSettings         *_m_stApp;
    QSqlDatabase       _m_dbDatabase;
    QSqlTableModel    *_m_tmModel;
    db_items_t         _m_hsDbItems;
    QDataWidgetMapper *_m_dmImage;

    void               _construct       ();
    void               _destruct        ();
    void               _initMain        ();
    void               _initModel       ();
    void               _initActions     ();

private Q_SLOTS:
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


    // group "Options"
    void               slot_OnSettings  ();

    // group "Help"
    void               slot_OnFaq       ();
    void               slot_OnAbout     ();

    // photo
    void               slot_OnPhotoAlbum();
};
//------------------------------------------------------------------------------
#endif // PickupDb_CMainH
