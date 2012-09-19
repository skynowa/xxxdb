/**
 * \file   CMain.cpp
 * \brief  main widget
 */


#include "CMain.h"

#include "Forms/CPersonEdit.h"


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CMain::CMain(
    QWidget    *parent,
    Qt::WFlags  flags
) :
    QMainWindow        (parent, flags),
    actFile_Exit       (this),
    actEdit_MovetoFirst(this),
    actEdit_MovetoPrior(this),
    actEdit_MovetoNext (this),
    actEdit_MovetoLast (this),
    actEdit_Insert     (this),
    actEdit_Delete     (this),
    actEdit_Edit       (this),
    actEdit_Post       (this),
    actEdit_Cancel     (this),
    actEdit_Refresh    (this),
    actFind_Search     (this),
    actOptions_Settings(this),
    actHelp_Faq        (this),
    actHelp_About      (this)
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
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::_construct() {
    m_Ui.setupUi(this);

    _initMain();
    _initModel();
    _initActions();
    _initMenus();
}
//---------------------------------------------------------------------------
void
CMain::_destruct() {

}
//---------------------------------------------------------------------------
void
CMain::_initMain() {
    // CMain
    {
        setWindowIcon(QIcon(CONFIG_RES_MAIN_ICON));

        setWindowTitle(CONFIG_APP_NAME);

        setGeometry(0, 0, CONFIG_APP_WIDTH, CONFIG_APP_HEIGHT);

        _widgetAlignCenter(this);
    }

    // lblPhoto
    {
        QImage imgPhoto;

        imgPhoto.load(QCoreApplication::applicationDirPath() + "/image.jpg");

        QImage img1 = imgPhoto.scaled(QSize(120 * 2, 90 * 2), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        m_Ui.lblPhoto->setPixmap(QPixmap::fromImage(img1));
        // m_Ui.lblPhoto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    // gbxShortInfo
    {
        m_Ui.gbxShortInfo->setTitle(tr(""));
    }

    // splitters
    {
        m_Ui.splitter->setStretchFactor(1, 1);

        // m_Ui.splPhotoTable->setStretchFactor(1, 1);
        // m_Ui.splPhotoShortInfo->setStretchFactor(1, 1);
    }

    // signals
    {
        connect(m_Ui.tabvInfo, SIGNAL( doubleClicked(const QModelIndex &) ),
                this,          SLOT  ( slot_tabvInfo_OnDoubleClicked(const QModelIndex &) ));
    }
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
                    "CREATE TABLE IF NOT EXISTS "
                    "   t_person "
                    "( "
                    "    f_id      INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                    "    f_name    VARCHAR (64), "
                    "    f_adge    INT, "
                    "    f_photo_1 BLOB "
                    ")";

            bRes = qryInfo.exec(csSql);
            qCHECK_REF(bRes, qryInfo);
        }
    }

    //--------------------------------------------------
    // _m_mdModel
    {
        _m_mdModel = new QSqlTableModel(this, _m_dbDatabase);
        Q_ASSERT(NULL != _m_mdModel);

        _m_mdModel->setTable("t_person");
        _m_mdModel->setEditStrategy(QSqlTableModel::OnFieldChange);
        _m_mdModel->select();
        _m_mdModel->removeColumn(0); // don't show the ID
        _m_mdModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
        _m_mdModel->setHeaderData(1, Qt::Horizontal, tr("Adge"));
        _m_mdModel->select();

        m_Ui.tabvInfo->setModel(_m_mdModel);
        m_Ui.tabvInfo->verticalHeader()->setDefaultSectionSize(CONFIG_TABLEVIEW_ROW_HEIGHT);
        m_Ui.tabvInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_Ui.tabvInfo->setSelectionBehavior(QAbstractItemView::SelectRows);

        m_Ui.tabvInfo->show();
    }

    //--------------------------------------------------
    // m_navNavigator
    {
        m_navNavigator.setup(_m_mdModel, m_Ui.tabvInfo);
    }

}
//---------------------------------------------------------------------------
void
CMain::_initActions() {
    // group "File"
    {
        actFile_Exit.setText(tr("Exit"));
        connect(&actFile_Exit, SIGNAL( triggered() ), this, SLOT( slot_OnExit() ));
        m_Ui.toolBar->addAction(&actFile_Exit);
    }

    // group "Edit"
    {
        actEdit_MovetoFirst.setText(tr("First"));
        connect(&actEdit_MovetoFirst, SIGNAL( triggered() ), this, SLOT( slot_OnFirst() ));
        m_Ui.toolBar->addAction(&actEdit_MovetoFirst);

        actEdit_MovetoPrior.setText(tr("Prior"));
        connect(&actEdit_MovetoPrior, SIGNAL( triggered() ), this, SLOT( slot_OnPrior() ));
        m_Ui.toolBar->addAction(&actEdit_MovetoPrior);

        actEdit_MovetoNext.setText(tr("Next"));
        connect(&actEdit_MovetoNext, SIGNAL( triggered() ), this, SLOT( slot_OnNext() ));
        m_Ui.toolBar->addAction(&actEdit_MovetoNext);

        actEdit_MovetoLast.setText(tr("Last"));
        connect(&actEdit_MovetoLast, SIGNAL( triggered() ), this, SLOT( slot_OnLast() ));
        m_Ui.toolBar->addAction(&actEdit_MovetoLast);

        actEdit_Insert.setText(tr("Insert"));
        connect(&actEdit_Insert, SIGNAL( triggered() ), this, SLOT( slot_OnInsert() ));
        m_Ui.toolBar->addAction(&actEdit_Insert);

        actEdit_Delete.setText(tr("Delete"));
        connect(&actEdit_Delete, SIGNAL( triggered() ), this, SLOT( slot_OnRemove() ));
        m_Ui.toolBar->addAction(&actEdit_Delete);

        actEdit_Edit.setText(tr("Edit"));
        connect(&actEdit_Edit, SIGNAL( triggered() ), this, SLOT( slot_OnEdit() ));
        m_Ui.toolBar->addAction(&actEdit_Edit);

        actEdit_Post.setText(tr("Post"));
        connect(&actEdit_Post, SIGNAL( triggered() ), this, SLOT( slot_OnPost() ));
        m_Ui.toolBar->addAction(&actEdit_Post);

        actEdit_Cancel.setText(tr("Cancel"));
        connect(&actEdit_Cancel, SIGNAL( triggered() ), this, SLOT( slot_OnCancel() ));
        m_Ui.toolBar->addAction(&actEdit_Cancel);

        actEdit_Refresh.setText(tr("Refresh"));
        connect(&actEdit_Refresh, SIGNAL( triggered() ), this, SLOT( slot_OnRefresh() ));
        m_Ui.toolBar->addAction(&actEdit_Refresh);
    }

    // group "Find"
    {
        actFind_Search.setText(tr("Search"));
        connect(&actFind_Search, SIGNAL( triggered() ), this, SLOT( slot_OnSearch() ));
        m_Ui.toolBar->addAction(&actFind_Search);
    }

    // group "View"
    {

    }

    // group "Options"
    {
        actOptions_Settings.setText(tr("Settings"));
        connect(&actOptions_Settings, SIGNAL( triggered() ), this, SLOT( slot_OnSettings() ));
        m_Ui.toolBar->addAction(&actOptions_Settings);
    }

    // group "Help"
    {
        actHelp_Faq.setText(tr("FAQ"));
        connect(&actHelp_Faq, SIGNAL( triggered() ), this, SLOT( slot_OnFaq() ));
        m_Ui.toolBar->addAction(&actHelp_Faq);

        actHelp_About.setText(tr("About"));
        connect(&actHelp_About, SIGNAL( triggered() ), this, SLOT( slot_OnAbout() ));
        m_Ui.toolBar->addAction(&actHelp_About);
    }
}
//---------------------------------------------------------------------------
void
CMain::_initMenus() {
    // group "File"
    {
        mnuFile.setTitle(tr("File"));

        mnuFile.addAction(&actFile_Exit);

        menuBar()->addMenu(&mnuFile);
    }

    // group "Edit"
    {
        mnuEdit.setTitle(tr("Edit"));

        mnuEdit.addAction(&actEdit_MovetoFirst);
        mnuEdit.addAction(&actEdit_MovetoPrior);
        mnuEdit.addAction(&actEdit_MovetoNext);
        mnuEdit.addAction(&actEdit_MovetoLast);
        mnuEdit.addAction(&actEdit_Insert);
        mnuEdit.addAction(&actEdit_Delete);
        mnuEdit.addAction(&actEdit_Edit);
        mnuEdit.addAction(&actEdit_Post);
        mnuEdit.addAction(&actEdit_Cancel);
        mnuEdit.addAction(&actEdit_Refresh);

        menuBar()->addMenu(&mnuEdit);
    }

    // group "Find"
    {
        mnuFind.setTitle(tr("Find"));

        mnuFind.addAction(&actFind_Search);

        menuBar()->addMenu(&mnuFind);
    }

    // group "View"
    {
        mnuView.setTitle(tr("View"));

        menuBar()->addMenu(&mnuView);
    }

    // group "Options"
    {
        mnuOptions.setTitle(tr("Options"));

        mnuOptions.addAction(&actOptions_Settings);

        menuBar()->addMenu(&mnuOptions);
    }

    // group "Help"
    {
        mnuHelp.setTitle(tr("Help"));

        mnuHelp.addAction(&actHelp_Faq);
        mnuHelp.addAction(&actHelp_About);

        menuBar()->addMenu(&mnuHelp);
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*   group "File"
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::slot_OnExit() {
    close();
}
//---------------------------------------------------------------------------


/****************************************************************************
*   group "Edit"
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
CMain::slot_tabvInfo_OnDoubleClicked(const QModelIndex &index) {



    CPersonEdit dlgPersonEdit(this);

    dlgPersonEdit.exec();
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
*   group "Find"
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::slot_OnSearch() {

}
//---------------------------------------------------------------------------


/****************************************************************************
*   group "View"
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*
void
CMain::xxxxxxx() {

}
*/
//---------------------------------------------------------------------------


/****************************************************************************
*   group "Options"
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::slot_OnSettings() {

}
//---------------------------------------------------------------------------


/****************************************************************************
*   group "Help"
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::slot_OnFaq() {

}
//---------------------------------------------------------------------------
void
CMain::slot_OnAbout() {
    QString sMsg = QString(tr(
        "<p>"
        "<b>%1</b> - accounting software for girls"
        "</p>")
            .arg(CONFIG_APP_NAME)
        );

    QMessageBox::about(this, tr("About ") + CONFIG_APP_NAME, sMsg);
}
//---------------------------------------------------------------------------


/****************************************************************************
*   utils
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::_widgetAlignCenter(QWidget *widget) {
    Q_ASSERT(NULL != widget);

    QDesktopWidget *desktop = QApplication::desktop();

    int x = (desktop->width()  - widget->width())  / 2;
    int y = (desktop->height() - widget->height()) / 2;

    widget->setGeometry(x, y, widget->width(), widget->height());
}
//---------------------------------------------------------------------------
