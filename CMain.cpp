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

    _initModel();

    /****************************************************************************
    *   setup slots
    *
    *****************************************************************************/

    //--------------------------------------------------
    // mnuEdit
    QObject::connect(_m_Ui.actMovetoFirst, SIGNAL( triggered() ), this, SLOT( first()   ));
    QObject::connect(_m_Ui.actMovetoPrior, SIGNAL( triggered() ), this, SLOT( prior()   ));
    QObject::connect(_m_Ui.actMovetoNext,  SIGNAL( triggered() ), this, SLOT( next()    ));
    QObject::connect(_m_Ui.actMovetoLast,  SIGNAL( triggered() ), this, SLOT( last()    ));
    QObject::connect(_m_Ui.actInsert,      SIGNAL( triggered() ), this, SLOT( insert()  ));
    QObject::connect(_m_Ui.actDelete,      SIGNAL( triggered() ), this, SLOT( remove()  ));
    QObject::connect(_m_Ui.actEdit,        SIGNAL( triggered() ), this, SLOT( edit()    ));
    QObject::connect(_m_Ui.actPost,        SIGNAL( triggered() ), this, SLOT( post()    ));
    QObject::connect(_m_Ui.actCancel,      SIGNAL( triggered() ), this, SLOT( cancel()  ));
    QObject::connect(_m_Ui.actRefresh,     SIGNAL( triggered() ), this, SLOT( refresh() ));

    {
        QImage imgPhoto;
        imgPhoto.load("./image1.png");

        QImage img1 = imgPhoto.scaled(QSize(120 * 2, 90 * 2), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        _m_Ui.lblPhoto->setPixmap(QPixmap::fromImage(img1));
        //ui.lblPhoto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    {
     //   _m_Ui.ledtName->setMap
    }
}
//---------------------------------------------------------------------------
/*virtual*/
CMain::~CMain() {

}
//---------------------------------------------------------------------------
void
CMain::_initModel() {
    bool bRes = false;


    bRes = QSqlDatabase::isDriverAvailable("QSQLITE");
    qCHECK_DO(false == bRes, qMSG(QSqlDatabase().lastError().text()); return);

    _m_dbDatabase = QSqlDatabase::addDatabase("QSQLITE");
    _m_dbDatabase.setDatabaseName("./base.db");

    bRes = _m_dbDatabase.open();
    qCHECK_REF(bRes, _m_dbDatabase);

    //Set up the main table
    QSqlQuery qryInfo(_m_dbDatabase);

    bRes = qryInfo.exec("create table if not exists T_PERSON (F_ID int primary key not null, F_NAME varchar(64), F_ADGE int);");
    qCHECK_REF(bRes, qryInfo);

    //CSqlCryptTableModel
    _m_mdModel = new QSqlTableModel(this, _m_dbDatabase);
    _m_mdModel->setTable("T_PERSON");
    _m_mdModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    _m_mdModel->select();
    //_m_mdModel->removeColumn(0); // don't show the ID
    _m_mdModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
    _m_mdModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    _m_mdModel->setHeaderData(2, Qt::Horizontal, tr("Address"));
    _m_mdModel->select();

    _m_Ui.tabvInfo->setModel(_m_mdModel);
    _m_Ui.tabvInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    _m_Ui.tabvInfo->show();

    m_navNavigator.setup(_m_mdModel, _m_Ui.tabvInfo);
}
//---------------------------------------------------------------------------


/****************************************************************************
*   mnuEdit
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::first() {
    m_navNavigator.first();
}
//---------------------------------------------------------------------------
void
CMain::prior() {
    m_navNavigator.prior();
}
//---------------------------------------------------------------------------
void
CMain::next() {
    m_navNavigator.next();
}
//---------------------------------------------------------------------------
void
CMain::last() {
    m_navNavigator.last();
}
//---------------------------------------------------------------------------
void
CMain::insert() {
    m_navNavigator.insert();
}
//---------------------------------------------------------------------------
void
CMain::remove() {
    m_navNavigator.remove();
}
//---------------------------------------------------------------------------
void
CMain::edit() {
    m_navNavigator.edit();
}
//---------------------------------------------------------------------------
void
CMain::post() {
    m_navNavigator.post();
}
//---------------------------------------------------------------------------
void
CMain::cancel() {
    m_navNavigator.cancel();
}
//---------------------------------------------------------------------------
void
CMain::refresh() {
    m_navNavigator.refresh();
}
//---------------------------------------------------------------------------
