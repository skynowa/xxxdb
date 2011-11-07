/**
 * \file   CMain.cpp
 * \brief  main widget
 */


#include "CMain.h"


//---------------------------------------------------------------------------
CMain::CMain(
    QWidget    *parent,
    Qt::WFlags  flags
) :
    QMainWindow(parent, flags)
{
    _m_Ui.setupUi(this);

    _setupModel();

    /****************************************************************************
    *   setup slots
    *
    *****************************************************************************/

    //--------------------------------------------------
    // mnuEdit
    QObject::connect(_m_Ui.actMovetoFirst, SIGNAL( triggered() ), this, SLOT( First()   ));
    QObject::connect(_m_Ui.actMovetoPrior, SIGNAL( triggered() ), this, SLOT( Prior()   ));
    QObject::connect(_m_Ui.actMovetoNext,  SIGNAL( triggered() ), this, SLOT( Next()    ));
    QObject::connect(_m_Ui.actMovetoLast,  SIGNAL( triggered() ), this, SLOT( Last()    ));
    QObject::connect(_m_Ui.actInsert,      SIGNAL( triggered() ), this, SLOT( Insert()  ));
    QObject::connect(_m_Ui.actDelete,      SIGNAL( triggered() ), this, SLOT( Delete()  ));
    QObject::connect(_m_Ui.actEdit,        SIGNAL( triggered() ), this, SLOT( Edit()    ));
    QObject::connect(_m_Ui.actPost,        SIGNAL( triggered() ), this, SLOT( Post()    ));
    QObject::connect(_m_Ui.actCancel,      SIGNAL( triggered() ), this, SLOT( Cancel()  ));
    QObject::connect(_m_Ui.actRefresh,     SIGNAL( triggered() ), this, SLOT( Refresh() ));

    {
        QImage imgPhoto;
        imgPhoto.load("./image.png");

        QImage img1 = imgPhoto.scaled(QSize(120 * 2, 90 * 2), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        _m_Ui.lblPhoto->setPixmap(QPixmap::fromImage(img1));
        //ui.lblPhoto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
}
//---------------------------------------------------------------------------
CMain::~CMain()
{
    _m_dbDatabase.close();
}
//---------------------------------------------------------------------------
void
CMain::_setupModel() {
    bool bRes = false;

    _m_dbDatabase = QSqlDatabase::addDatabase("QSQLITE");

    _m_dbDatabase.setDatabaseName("./base.db");

    bRes = _m_dbDatabase.open();
    if (false == bRes) {
        QMessageBox::critical(0, tr(""), _m_dbDatabase.lastError().text(), QMessageBox::Cancel);
        return;
    }

    //Set up the main table
    QSqlQuery qryInfo(_m_dbDatabase);

    bRes = qryInfo.exec("create table T_PERSON (F_ID int primary key, F_NAME varchar(64), F_ADGE int);");
    if (false == bRes) {
        QMessageBox::critical(0, tr(""), qryInfo.lastError().text(), QMessageBox::Cancel);
    }

    //CSqlCryptTableModel
    _m_mdModel = new CSqlCryptTableModel(this, _m_dbDatabase);
    _m_mdModel->setKey(xT("0123456789"));
    _m_mdModel->setTable("T_PERSON");
    _m_mdModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    _m_mdModel->select();
    //_m_mdModel->removeColumn(0); // don't show the ID

    _m_mdModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
    _m_mdModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    _m_mdModel->setHeaderData(2, Qt::Horizontal, tr("Address"));

    _m_Ui.tabvInfo->setModel(_m_mdModel);
    _m_Ui.tabvInfo->show();

    ///_m_mdModel->select();
}
//---------------------------------------------------------------------------



/****************************************************************************
*   mnuEdit
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::Cancel() {

}
//---------------------------------------------------------------------------
void
CMain::Delete() {

}
//---------------------------------------------------------------------------
void
CMain::Edit() {

}
//---------------------------------------------------------------------------
void
CMain::First() {

}
//---------------------------------------------------------------------------
void
CMain::Insert() {
    QSqlQuery qryInfo;

    bool bRes = qryInfo.exec("insert into T_PERSON values(102, 'Christine', 20)");
    if (false == bRes) {
        QMessageBox::critical(0, tr(""), qryInfo.lastError().text(), QMessageBox::Cancel);
    }
}
//---------------------------------------------------------------------------
void
CMain::Last() {

}
//---------------------------------------------------------------------------
void
CMain::Next() {

}
//---------------------------------------------------------------------------
void
CMain::Post() {

}
//---------------------------------------------------------------------------
void
CMain::Prior() {

}
//---------------------------------------------------------------------------
void
CMain::Refresh() {
    QSqlQuery qryInfo(_m_dbDatabase);

    bool bRes = qryInfo.exec("select * from T_PERSON");
    if (false == bRes) {
        QMessageBox::critical(0, tr(""), qryInfo.lastError().text(), QMessageBox::Cancel);
    }
}
//---------------------------------------------------------------------------
