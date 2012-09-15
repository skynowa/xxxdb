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
    _construct();
}
//---------------------------------------------------------------------------
/*virtual*/
CMain::~CMain() {
    _destruct();
}
//---------------------------------------------------------------------------


/****************************************************************************
*   mnuEdit
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::slot_OnFirst() {
    m_navNavigator.first();
}
//---------------------------------------------------------------------------
void
CMain::slot_OnPrior() {
    m_navNavigator.prior();
}
//---------------------------------------------------------------------------
void
CMain::slot_OnNext() {
    m_navNavigator.next();
}
//---------------------------------------------------------------------------
void
CMain::slot_OnLast() {
    m_navNavigator.last();
}
//---------------------------------------------------------------------------
void
CMain::slot_OnInsert() {
    m_navNavigator.insert();
}
//---------------------------------------------------------------------------
void
CMain::slot_OnRemove() {
    m_navNavigator.remove();
}
//---------------------------------------------------------------------------
void
CMain::slot_OnEdit() {
    m_navNavigator.edit();
}
//---------------------------------------------------------------------------
void
CMain::slot_OnPost() {
    m_navNavigator.post();
}
//---------------------------------------------------------------------------
void
CMain::slot_OnCancel() {
    m_navNavigator.cancel();
}
//---------------------------------------------------------------------------
void
CMain::slot_OnRefresh() {
    m_navNavigator.refresh();
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::_construct() {
    _m_Ui.setupUi(this);

    _initModel();

    /****************************************************************************
    *   setup slots
    *
    *****************************************************************************/

    //--------------------------------------------------
    // mnuEdit
    QObject::connect(_m_Ui.actMovetoFirst, SIGNAL( triggered() ), this, SLOT( slot_OnFirst()   ));
    QObject::connect(_m_Ui.actMovetoPrior, SIGNAL( triggered() ), this, SLOT( slot_OnPrior()   ));
    QObject::connect(_m_Ui.actMovetoNext,  SIGNAL( triggered() ), this, SLOT( slot_OnNext()    ));
    QObject::connect(_m_Ui.actMovetoLast,  SIGNAL( triggered() ), this, SLOT( slot_OnLast()    ));
    QObject::connect(_m_Ui.actInsert,      SIGNAL( triggered() ), this, SLOT( slot_OnInsert()  ));
    QObject::connect(_m_Ui.actDelete,      SIGNAL( triggered() ), this, SLOT( slot_OnRemove()  ));
    QObject::connect(_m_Ui.actEdit,        SIGNAL( triggered() ), this, SLOT( slot_OnEdit()    ));
    QObject::connect(_m_Ui.actPost,        SIGNAL( triggered() ), this, SLOT( slot_OnPost()    ));
    QObject::connect(_m_Ui.actCancel,      SIGNAL( triggered() ), this, SLOT( slot_OnCancel()  ));
    QObject::connect(_m_Ui.actRefresh,     SIGNAL( triggered() ), this, SLOT( slot_OnRefresh() ));

    {
        QImage imgPhoto;

        imgPhoto.load(QCoreApplication::applicationDirPath() + "/image.jpg");

        QImage img1 = imgPhoto.scaled(QSize(120 * 2, 90 * 2), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        _m_Ui.lblPhoto->setPixmap(QPixmap::fromImage(img1));
        // _m_Ui.lblPhoto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    {
        // _m_Ui.ledtName->setMap
    }
}
//---------------------------------------------------------------------------
void
CMain::_destruct() {

}
//---------------------------------------------------------------------------
void
CMain::_initModel() {
    //--------------------------------------------------
    // settings DB
    {
        bool bRes = false;

        bRes = QSqlDatabase::isDriverAvailable("QSQLITE");
        qCHECK_DO(false == bRes, qMSG(QSqlDatabase().lastError().text()); return;);

        _m_dbDatabase = QSqlDatabase::addDatabase("QSQLITE");
        _m_dbDatabase.setDatabaseName(QCoreApplication::applicationFilePath() + CONFIG_DB_FILE_EXT);

        bRes = _m_dbDatabase.open();
        qCHECK_REF(bRes, _m_dbDatabase);

        {
            QSqlQuery qryInfo(_m_dbDatabase);

            const QString csSql = \
                    "CREATE TABLE IF NOT EXISTS t_person"
                    "( "
                    "    f_id   INTEGER     PRIMARY KEY AUTOINCREMENT "
                    "                       NOT NULL "
                    "                       UNIQUE, "
                    "    f_name varchar(64), "
                    "    f_adge int "
                    ")";

            bRes = qryInfo.exec(csSql);
            qCHECK_REF(bRes, qryInfo);
        }
    }

    //--------------------------------------------------
    // _m_mdModel
    {
        _m_mdModel = new QSqlTableModel(this, _m_dbDatabase);
        _m_mdModel->setTable("t_person");
        _m_mdModel->setEditStrategy(QSqlTableModel::OnFieldChange);
        _m_mdModel->select();
        _m_mdModel->removeColumn(0); // don't show the ID
        _m_mdModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
        _m_mdModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        _m_mdModel->setHeaderData(2, Qt::Horizontal, tr("Adge"));
        _m_mdModel->select();

        _m_Ui.tabvInfo->setModel(_m_mdModel);
        _m_Ui.tabvInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        _m_Ui.tabvInfo->show();
    }

    //--------------------------------------------------
    // m_navNavigator
    {
        m_navNavigator.setup(_m_mdModel, _m_Ui.tabvInfo);
    }

}
//---------------------------------------------------------------------------

