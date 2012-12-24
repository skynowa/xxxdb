/**
 * \file   CMain.h
 * \brief  main widget
 */


#ifndef PickupDb_CMainH
#define PickupDb_CMainH
//---------------------------------------------------------------------------
#include "ui_CMain.h"

#include <xLib/Common/xCommon.h>
#include "../QtLib/Common.h"

#include "../Config.h"
#include "../Classes/CSqlNavigator.h"
//---------------------------------------------------------------------------
class CMain :
    public QMainWindow
{
        Q_OBJECT

    public:
        explicit                  CMain          (QWidget *parent = 0, Qt::WFlags flags = 0);
        virtual                  ~CMain          ();

        Ui::CMainClass            m_Ui;
        QString                   m_sAppName;
        QString                   m_sAppDir;
        QString                   m_sDbDir;
        QString                   m_sDbBackupDir;
        CSqlNavigator             m_navNavigator;

    private:
        QSqlDatabase              _m_dbDatabase;
        QSqlTableModel           *_m_tmModel;
        QMap<QString, QWidget *>  _m_mapDbControls;
        QDataWidgetMapper        *_m_dmMapper;

        void                      _construct     ();
        void                      _destruct      ();
        void                      _initMain      ();
        void                      _initModel     ();
        void                      _initActions   ();

    private slots:
        // group "Exit"
        void                      slot_OnExit    ();

        // group "Edit"
        void                      slot_OnFirst   ();
        void                      slot_OnPrior   ();
        void                      slot_OnNext    ();
        void                      slot_OnLast    ();
        void                      slot_OnInsert  ();
        void                      slot_OnRemove  ();
        void                      slot_OnEdit    ();
        void                      slot_OnPost    ();
        void                      slot_OnCancel  ();
        void                      slot_OnRefresh ();

        // group "Find"
        void                      slot_OnSearch  ();

        // group "View"


        // group "Options"
        void                      slot_OnSettings();

        // group "Help"
        void                      slot_OnFaq     ();
        void                      slot_OnAbout   ();

    private:
        void                      _settingsLoad  ();
        void                      _settingsSave  ();

};
//---------------------------------------------------------------------------
#endif // PickupDb_CMainH
