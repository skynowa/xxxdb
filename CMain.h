/**
 * \file   CMain.h
 * \brief  main widget
 */


#ifndef CMAIN_H
#define CMAIN_H
//---------------------------------------------------------------------------
#include "ui_CMain.h"

#include "Classes/Common.h"
#include "Classes/CSqlCryptTableModel.h"
#include "Classes/CSqlNavigator.h"
//---------------------------------------------------------------------------
class CMain :
    public QMainWindow
{
        Q_OBJECT

    public:
                             CMain      (QWidget *parent = 0, Qt::WFlags flags = 0);
        virtual             ~CMain      ();

        CSqlNavigator        m_navNavigator;

    private:
        Ui::CMainClass       _m_Ui;
        QSqlDatabase         _m_dbDatabase;
        CSqlCryptTableModel *_m_mdModel;


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
#endif // CMAIN_H
