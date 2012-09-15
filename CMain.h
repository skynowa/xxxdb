/**
 * \file   CMain.h
 * \brief  main widget
 */


#ifndef PickupDb_CMainH
#define PickupDb_CMainH
//---------------------------------------------------------------------------
#include "ui_CMain.h"

#include "Config.h"
#include "QtLib/Common.h"
#include "Classes/CSqlNavigator.h"
//---------------------------------------------------------------------------
class CMain :
    public QMainWindow
{
        Q_OBJECT

    public:
                             CMain     (QWidget *parent = 0, Qt::WFlags flags = 0);
        virtual             ~CMain     ();

        CSqlNavigator        m_navNavigator;

    private:
        Ui::CMainClass       _m_Ui;
        QSqlDatabase         _m_dbDatabase;
        QSqlTableModel      *_m_mdModel;


        void                 _initModel();

    private slots:
        /****************************************************************************
        *   mnubMain - main toolbar
        *
        *****************************************************************************/

        //--------------------------------------------------
        // mnuEdit
        void                 first     ();
        void                 prior     ();
        void                 next      ();
        void                 last      ();
        void                 insert    ();
        void                 remove    ();
        void                 edit      ();
        void                 post      ();
        void                 cancel    ();
        void                 refresh   ();

};
//---------------------------------------------------------------------------
#endif // PickupDb_CMainH
