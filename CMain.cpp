/**
 * \file   CMain.cpp
 * \brief  main widget
 */


#include "CMain.h"


//---------------------------------------------------------------------------
CMain::CMain(
    QWidget    *parent,
    Qt::WFlags  flags
)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);

    _setupModel();

    QImage imgPhoto;
    imgPhoto.load("./image.png");

    QImage img1 = imgPhoto.scaled(QSize(120 * 2, 90 * 2), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui.lblPhoto->setPixmap(QPixmap::fromImage(img1));
    //ui.lblPhoto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
//---------------------------------------------------------------------------
CMain::~CMain()
{
    _m_dbDatabse.close();
}
//---------------------------------------------------------------------------
void
CMain::_setupModel() {
    bool bRes = false;

    _m_dbDatabse = QSqlDatabase::addDatabase("QSQLITE");

    _m_dbDatabse.setDatabaseName("./base.db");
    if (!_m_dbDatabse.open()) {
        QMessageBox::critical(0, tr(""), _m_dbDatabse.lastError().text(), QMessageBox::Cancel);
        return;
    }

    //Set up the main table
    QSqlQuery query;

    bRes = query.exec("CREATE TABLE T_PERSON (F_ID INT PRIMARY KEY, F_NAME BLOB, F_ADGE INT)");
    if (false == bRes) {
        //QMessageBox::critical(0, tr(""), tr("Can't create table."), QMessageBox::Cancel);
    }

#if 0
    bRes = query.exec("INSERT INTO T_PERSON VALUES(1, 'Alice',  20)");
    if (false == bRes) {
        //QMessageBox::critical(0, tr(""), tr("Can't insert record."), QMessageBox::Cancel);
    }

    bRes = query.exec("INSERT INTO T_PERSON VALUES(2, 'Bob',    30)");
    bRes = query.exec("INSERT INTO T_PERSON VALUES(3, 'Carol',  19)");
    bRes = query.exec("INSERT INTO T_PERSON VALUES(4, 'Donald', 40)");
    bRes = query.exec("INSERT INTO T_PERSON VALUES(5, 'Emma',   25)");
#endif

    //CSqlCryptTableModel
    _m_mdModel = new CSqlCryptTableModel(this, _m_dbDatabse);
    _m_mdModel->setKey(xT("0123456789"));
    _m_mdModel->setTable("T_PERSON");
    _m_mdModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    _m_mdModel->select();
    //_m_mdModel->removeColumn(0); // don't show the ID

    _m_mdModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
    _m_mdModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    _m_mdModel->setHeaderData(2, Qt::Horizontal, tr("Address"));

    ui.tabvInfo->setModel(_m_mdModel);
    ui.tabvInfo->show();

    _m_mdModel->select();
}
//---------------------------------------------------------------------------

