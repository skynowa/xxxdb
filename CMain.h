/**
 * \file   CMain.h
 * \brief  main widget
 */


#ifndef CMAIN_H
#define CMAIN_H
//---------------------------------------------------------------------------
#include <QtGui/QWidget>
#include <QtGui/QMessageBox>
#include <QtSql>
#include <QImage>

#include "ui_CMain.h"

#include "Classes/CSqlCryptTableModel.h"
//---------------------------------------------------------------------------
class CMain :
    public QWidget
{
        Q_OBJECT

    public:
        CMain(QWidget *parent = 0);
        ~CMain();

    private:
        Ui::CMainClass  ui;

        CSqlCryptTableModel *model;

        QSqlDatabase    _m_dbDatabse;

        void            setupModel();
};
//---------------------------------------------------------------------------
#endif // CMAIN_H
