/**
 * \file   CMain.h
 * \brief  main widget
 */


#ifndef PickupDb_CMainH
#define PickupDb_CMainH
//---------------------------------------------------------------------------
#include "ui_CMain.h"

#include "../QtLib/Common.h"

#include "../Config.h"
#include "../Classes/CSqlNavigator.h"
//---------------------------------------------------------------------------
class CMain :
    public QMainWindow
{
        Q_OBJECT

    public:
                        CMain             (QWidget *parent = 0, Qt::WFlags flags = 0);
        virtual        ~CMain             ();

        Ui::CMainClass  m_Ui;
        CSqlNavigator   m_navNavigator;

    private:
        QSqlDatabase    _m_dbDatabase;
        QSqlTableModel *_m_tmModel;

        void            _construct        ();
        void            _destruct         ();
        void            _initMain         ();
        void            _initModel        ();
        void            _initActions      ();
        void            _initMenus        ();


        // group "File"
        QAction         actFile_Exit;

        // group "Edit"
        QAction         actEdit_MovetoFirst;
        QAction         actEdit_MovetoPrior;
        QAction         actEdit_MovetoNext;
        QAction         actEdit_MovetoLast;
        QAction         actEdit_Insert;
        QAction         actEdit_Delete;
        QAction         actEdit_Edit;
        QAction         actEdit_Post;
        QAction         actEdit_Cancel;
        QAction         actEdit_Refresh;

        // group "Find"
        QAction         actFind_Search;

        // group "View"

        // group "Options"
        QAction         actOptions_Settings;

        // group "Help"
        QAction         actHelp_Faq;
        QAction         actHelp_About;


        // menu
        QMenu           mnuFile;
        QMenu           mnuEdit;
        QMenu           mnuFind;
        QMenu           mnuView;
        QMenu           mnuOptions;
        QMenu           mnuHelp;

    private slots:
        // group "Exit"
        void            slot_OnExit       ();

        // group "Edit"
        void            slot_OnFirst      ();
        void            slot_OnPrior      ();
        void            slot_OnNext       ();
        void            slot_OnLast       ();
        void            slot_OnInsert     ();
        void            slot_OnRemove     ();
        void            slot_OnEdit       ();
        void            slot_OnPost       ();
        void            slot_OnCancel     ();
        void            slot_OnRefresh    ();

        // group "Find"
        void            slot_OnSearch     ();

        // group "View"


        // group "Options"
        void            slot_OnSettings   ();

        // group "Help"
        void            slot_OnFaq        ();
        void            slot_OnAbout      ();

        void            slot_tabvInfo_OnSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
        void            slot_tabvInfo_OnDoubleClicked   (const QModelIndex &index);

    private:

};
//---------------------------------------------------------------------------
#endif // PickupDb_CMainH
