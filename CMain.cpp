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
/*virtual*/
CMain::~CMain() {
    _m_dbDatabase.close();
}
//---------------------------------------------------------------------------
void
CMain::_initModel() {
    bool bRes = false;

    _m_dbDatabase = QSqlDatabase::addDatabase("QSQLITE");

    _m_dbDatabase.setDatabaseName("./base.db");

    bRes = _m_dbDatabase.open();
    qCHECK_REF(bRes, _m_dbDatabase);

    //Set up the main table
    QSqlQuery qryInfo(_m_dbDatabase);

    bRes = qryInfo.exec("create table if not exists T_PERSON (F_ID int primary key, F_NAME varchar(64), F_ADGE int);");
    qCHECK_REF(bRes, qryInfo);

    //CSqlCryptTableModel
    _m_mdModel = new CSqlCryptTableModel(this, _m_dbDatabase);
    _m_mdModel->setCryptKey(xT("0123456789"));
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

    m_navNavigator.Setup(_m_mdModel, _m_Ui.tabvInfo);
}
//---------------------------------------------------------------------------



/****************************************************************************
*   mnuEdit
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::First() {
    m_navNavigator.First();
}
//---------------------------------------------------------------------------
void
CMain::Prior() {
    m_navNavigator.Prior();
}
//---------------------------------------------------------------------------
void
CMain::Next() {
    m_navNavigator.Next();
}
//---------------------------------------------------------------------------
void
CMain::Last() {
    m_navNavigator.Last();
}
//---------------------------------------------------------------------------
void
CMain::Insert() {
    m_navNavigator.Insert();
}
//---------------------------------------------------------------------------
void
CMain::Delete() {
    m_navNavigator.Delete();
}
//---------------------------------------------------------------------------
void
CMain::Edit() {
    m_navNavigator.Edit();
}
//---------------------------------------------------------------------------
void
CMain::Post() {
    m_navNavigator.Post();
}
//---------------------------------------------------------------------------
void
CMain::Cancel() {
    m_navNavigator.Cancel();
}
//---------------------------------------------------------------------------
void
CMain::Refresh() {
    m_navNavigator.Refresh();
}
//---------------------------------------------------------------------------
