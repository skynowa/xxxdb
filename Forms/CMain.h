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
class CPhotoAlbum;

class CMain :
    public QMainWindow
{
    Q_OBJECT

public:
    explicit           CMain            (QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual           ~CMain            ();

    Ui::CMainClass     m_Ui;
    QString            m_sAppName;
    QString            m_sAppDir;
    QString            m_sDbDir;
    QString            m_sDbBackupDir;
    CSqlNavigator      m_navNavigator;
    CPhotoAlbum       *m_wndPhotoAlbum;

private:
    typedef QHash<QWidget *, QString> db_controls_t;
    typedef const db_controls_t       cdb_controls_t;

    QSqlDatabase       _m_dbDatabase;
    QSqlTableModel    *_m_tmModel;
    db_controls_t      _m_hsDbControls;
    QDataWidgetMapper *_m_dmMapper;

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
    void               slot_OnTo        ();
    void               slot_OnInsert    ();
    void               slot_OnRemove    ();
    void               slot_OnEdit      ();
    void               slot_OnPost      ();
    void               slot_OnCancel    ();
    void               slot_OnRefresh   ();

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

private:
    // settings
    void               _settingsLoad    ();
    void               _settingsSave    ();

};
//------------------------------------------------------------------------------
#endif // PickupDb_CMainH
