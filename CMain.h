/**
 * \file   CMain.h
 * \brief  main widget
 */


#ifndef CMAIN_H
#define CMAIN_H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#include "../Common.h"
#include "ui_CMain.h"
#include "Classes/CSqlCryptTableModel.h"
//---------------------------------------------------------------------------
class CMain :
    public QMainWindow
{
        Q_OBJECT

    public:
                             CMain      (QWidget *parent = 0, Qt::WFlags flags = 0);
                            ~CMain      ();

    private:
        Ui::CMainClass       ui;
        QSqlDatabase         _m_dbDatabse;
        CSqlCryptTableModel *_m_mdModel;

        void                 _setupModel();
};
//---------------------------------------------------------------------------
#endif // CMAIN_H
