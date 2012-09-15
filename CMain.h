/**
 * \file   CMain.h
 * \brief  main widget
 */


#ifndef PickupDb_CMainH
#define PickupDb_CMainH
//---------------------------------------------------------------------------
#include "ui_CMain.h"

#include "QtLib/Common.h"

#include "Config.h"
#include "Classes/CSqlNavigator.h"
//---------------------------------------------------------------------------
class CMain :
    public QMainWindow
{
        Q_OBJECT

    public:
                        CMain         (QWidget *parent = 0, Qt::WFlags flags = 0);
        virtual        ~CMain         ();

        CSqlNavigator   m_navNavigator;

    private:
        Ui::CMainClass  _m_Ui;
        QSqlDatabase    _m_dbDatabase;
        QSqlTableModel *_m_mdModel;

        void            _construct    ();
        void            _destruct     ();
        void            _initModel    ();

    private slots:
        //--------------------------------------------------
        // mnubMain / mnuEdit
        void            slot_OnFirst  ();
        void            slot_OnPrior  ();
        void            slot_OnNext   ();
        void            slot_OnLast   ();
        void            slot_OnInsert ();
        void            slot_OnRemove ();
        void            slot_OnEdit   ();
        void            slot_OnPost   ();
        void            slot_OnCancel ();
        void            slot_OnRefresh();

};
//---------------------------------------------------------------------------
#endif // PickupDb_CMainH
