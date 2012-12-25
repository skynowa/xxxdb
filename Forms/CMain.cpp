/**
 * \file   CMain.cpp
 * \brief  main widget
 */


#include "CMain.h"

#include "../Forms/CPersonEdit.h"
#include "../QtLib/CUtils.h"
#include "../Classes/CDelegateDbImage.h"

#include <xLib/Common/CxString.h>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CMain::CMain(
    QWidget    *parent,
    Qt::WFlags  flags
) :
    QMainWindow    (parent, flags),
    m_sAppName     (),
    m_sAppDir      (),
    m_sDbDir       (),
    m_sDbBackupDir (),
    m_navNavigator (this),
    _m_dbDatabase  (),
    _m_tmModel     (NULL),
    _m_hsDbControls(),
    _m_dmMapper    (NULL)
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
    _initMain();
    _initModel();
    _initActions();
}
//---------------------------------------------------------------------------
void
CMain::_destruct() {
    _settingsSave();

    xPTR_DELETE(_m_dmMapper);
    xPTR_DELETE(_m_tmModel);
}
//---------------------------------------------------------------------------
void
CMain::_initMain() {
    m_Ui.setupUi(this);

    //--------------------------------------------------
    // data
    {
        m_sAppName     = CONFIG_APP_NAME;
        m_sAppDir      = qApp->applicationDirPath();
        m_sDbDir       = m_sAppDir + QDir::separator() + "Db";
        m_sDbBackupDir = m_sDbDir  + QDir::separator() + "Backup";

        QDir().mkpath(m_sDbDir);
    }

    // CMain
    {
        setWindowIcon(QIcon(CONFIG_RES_MAIN_ICON));
        setWindowTitle(CONFIG_APP_NAME);
        setGeometry(0, 0, CONFIG_APP_WIDTH, CONFIG_APP_HEIGHT);
        CUtils::widgetAlignCenter(this);
    }

    // gbxPhotoAlbum
    {
        m_Ui.gbxPhotoAlbum->setTitle(tr(""));
        m_Ui.gbxPhotoAlbum->setFixedHeight(50);
    }

    // gbxShortInfo
    {
        m_Ui.gbxShortInfo->setTitle(tr(""));
    }

    // splitters
    {
        // m_Ui.splitter->setStretchFactor(1, 1);
        // m_Ui.splitter->size().setWidth(1000);
        // m_Ui.splitter->adjustSize();

        // m_Ui.splPhotoTable->setStretchFactor(1, 1);
        // m_Ui.splPhotoShortInfo->setStretchFactor(1, 1);
    }

    // lblPhoto
    {
        m_Ui.lblPhoto->clear();
        m_Ui.lblPhoto->setFixedSize(CONFIG_PHOTO_WIDTH, CONFIG_PHOTO_HEIGHT);
        m_Ui.lblPhoto->setScaledContents(false);
        m_Ui.lblPhoto->setBackgroundRole(QPalette::Base);
        m_Ui.lblPhoto->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        m_Ui.lblPhoto->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        m_Ui.lblPhoto->setFrameShape(QFrame::Box);
    }

    _settingsLoad();
}
//---------------------------------------------------------------------------
void
CMain::_initModel() {
    //--------------------------------------------------
    // settings DB
    {
        bool bRv = QSqlDatabase::isDriverAvailable("QSQLITE");
        qCHECK_DO(false == bRv, qMSG(QSqlDatabase().lastError().text()); return;);

        _m_dbDatabase = QSqlDatabase::addDatabase("QSQLITE");
        _m_dbDatabase.setDatabaseName(QCoreApplication::applicationFilePath() + CONFIG_DB_FILE_EXT);

        bRv = _m_dbDatabase.open();
        qCHECK_REF(bRv, _m_dbDatabase);

        {
            QSqlQuery qryInfo(_m_dbDatabase);

            const QString csSql = \
                    "CREATE TABLE IF NOT EXISTS "
                    "    " CONFIG_DB_T_PERSON
                    "(   "
                    "    " CONFIG_DB_F_ID                     " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "

                    // Main
                    "    " CONFIG_DB_F_MAIN_NICK              " VARCHAR (64), "
                    "    " CONFIG_DB_F_MAIN_SURNAME           " VARCHAR (64), "
                    "    " CONFIG_DB_F_MAIN_NAME              " VARCHAR (64), "
                    "    " CONFIG_DB_F_MAIN_PATRONYMIC        " VARCHAR (64), "
                    "    " CONFIG_DB_F_MAIN_AGE               " INT, "
                    "    " CONFIG_DB_F_MAIN_HEIGHT            " INT, "
                    "    " CONFIG_DB_F_MAIN_WEIGHT            " INT, "
                    "    " CONFIG_DB_F_MAIN_HAIRLENGTH        " VARCHAR (64), "
                    "    " CONFIG_DB_F_MAIN_HAIRCOLOR         " VARCHAR (64), "
                    "    " CONFIG_DB_F_MAIN_APPEARANCE        " VARCHAR (64), "
                    "    " CONFIG_DB_F_MAIN_AGREEMENT         " VARCHAR (64), "

                    // Phones
                    "    " CONFIG_DB_F_PHONES_MOBILE1         " VARCHAR (64), "
                    "    " CONFIG_DB_F_PHONES_MOBILE2         " VARCHAR (64), "
                    "    " CONFIG_DB_F_PHONES_MOBILE3         " VARCHAR (64), "
                    "    " CONFIG_DB_F_PHONES_PHONEHOME       " VARCHAR (64), "
                    "    " CONFIG_DB_F_PHONES_PHONEJOB        " VARCHAR (64), "
                    "    " CONFIG_DB_F_PHONES_PHONEADDITIONAL " VARCHAR (256), "

                    // Address
                    "    " CONFIG_DB_F_ADDRESS_COUNTRY        " VARCHAR (64), "
                    "    " CONFIG_DB_F_ADDRESS_CODE           " VARCHAR (64), "
                    "    " CONFIG_DB_F_ADDRESS_CITY           " VARCHAR (64), "
                    "    " CONFIG_DB_F_ADDRESS_DISTRICT       " VARCHAR (64), "
                    "    " CONFIG_DB_F_ADDRESS_STREET         " VARCHAR (64), "
                    "    " CONFIG_DB_F_ADDRESS_HOUSE          " VARCHAR (64), "
                    "    " CONFIG_DB_F_ADDRESS_PORCH          " VARCHAR (64), "
                    "    " CONFIG_DB_F_ADDRESS_FLOOR          " VARCHAR (64), "
                    "    " CONFIG_DB_F_ADDRESS_APARTMENT      " VARCHAR (64), "

                    // E-mail
                    "    " CONFIG_DB_F_EMAIL_EMAIL            " VARCHAR (256), "

                    // Web
                    "    " CONFIG_DB_F_WEB_WEB                " VARCHAR (256), "

                    // Messengers
                    "    " CONFIG_DB_F_MESSENGERS_ICQ         " VARCHAR (64), "
                    "    " CONFIG_DB_F_MESSENGERS_SKYPE       " VARCHAR (64), "

                    // Job
                    "    " CONFIG_DB_F_JOB_PROFESSION         " VARCHAR (64), "
                    "    " CONFIG_DB_F_JOB_ADDRESS            " VARCHAR (64), "
                    "    " CONFIG_DB_F_JOB_SALARY             " VARCHAR (64), "
                    "    " CONFIG_DB_F_JOB_COMPANY            " VARCHAR (64), "

                    // Dates
                    "    " CONFIG_DB_F_DATES_BIRTHDAY         " DATETIME, "
                    "    " CONFIG_DB_F_DATES_BIRTHDAYFATHER   " DATETIME, "
                    "    " CONFIG_DB_F_DATES_BIRTHDAYMOTHER   " DATETIME, "
                    "    " CONFIG_DB_F_DATES_DAYDATING        " DATETIME, "
                    "    " CONFIG_DB_F_DATES_DAYFIRSTKISS     " DATETIME, "
                    "    " CONFIG_DB_F_DATES_DAYFIRSTSEX      " DATETIME, "

                    // Interests
                    "    " CONFIG_DB_F_INTERESTS_HOBBY        " VARCHAR (64), "
                    "    " CONFIG_DB_F_INTERESTS_SPORTS       " VARCHAR (64), "
                    "    " CONFIG_DB_F_INTERESTS_SMOKING      " VARCHAR (64), "
                    "    " CONFIG_DB_F_INTERESTS_ALCOHOL      " VARCHAR (64), "
                    "    " CONFIG_DB_F_INTERESTS_DRUGS        " VARCHAR (64), "

                    // TODO: Periods

                    // Etc
                    "    " CONFIG_DB_F_ETC_DATECREATION       " DATETIME, "
                    "    " CONFIG_DB_F_ETC_DATELASTCHANGE     " DATETIME, "

                    // Notes
                    "    " CONFIG_DB_F_NOTES_NOTES            " VARCHAR (256), "

                    // Photos
                    "    " CONFIG_DB_F_PHOTOS_1               " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_2               " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_3               " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_4               " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_5               " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_6               " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_7               " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_8               " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_9               " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_10              " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_11              " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_12              " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_13              " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_14              " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_15              " BLOB, "
                    "    " CONFIG_DB_F_PHOTOS_PRIMARY_DBFIELD " VARCHAR (64) "
                    ")";

            bRv = qryInfo.exec(csSql);
            qCHECK_REF(bRv, qryInfo);
        }
    }

    //--------------------------------------------------
    // _m_tmModel
    {
        _m_tmModel = new QSqlTableModel(this, _m_dbDatabase);
        Q_ASSERT(NULL != _m_tmModel);

        _m_tmModel->setTable("t_person");
    #if 0
        _m_tmModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
        _m_tmModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        _m_tmModel->setHeaderData(2, Qt::Horizontal, tr("Adge"));
        _m_tmModel->setHeaderData(3, Qt::Horizontal, tr("Photo"));
    #endif
        _m_tmModel->setEditStrategy(QSqlTableModel::OnRowChange);
        _m_tmModel->select();

        m_Ui.tabvInfo->setModel(_m_tmModel);
        m_Ui.tabvInfo->hideColumn(0); // don't show the CONFIG_DB_F_ID
        // m_Ui.tabvInfo->setColumnWidth(0, 40);
        m_Ui.tabvInfo->verticalHeader()->setVisible(true);
        m_Ui.tabvInfo->verticalHeader()->setDefaultSectionSize(CONFIG_TABLEVIEW_ROW_HEIGHT);
        m_Ui.tabvInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_Ui.tabvInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_Ui.tabvInfo->setSelectionMode(QAbstractItemView::SingleSelection);
        m_Ui.tabvInfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        m_Ui.tabvInfo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        // m_Ui.tabvInfo->setAlternatingRowColors(true);
        // m_Ui.tabvInfo->setStyleSheet("alternate-background-color: white; background-color: gray;");
        m_Ui.tabvInfo->setSortingEnabled(true);
        m_Ui.tabvInfo->sortByColumn(0, Qt::AscendingOrder);

        m_Ui.tabvInfo->show();
    }

    //--------------------------------------------------
    // _m_dmMapper
    {
        _m_dmMapper = new QDataWidgetMapper(this);
        _m_dmMapper->setModel(_m_tmModel);
        _m_dmMapper->setItemDelegate(new CDelegateDbImage(_m_dmMapper, _m_tmModel->fieldIndex(CONFIG_DB_F_PHOTOS_1), m_Ui.lblPhotoSize));
        _m_dmMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

        // DB controls to QMap
        {
             // Photos
            _m_hsDbControls.insert(CONFIG_DB_F_PHOTOS_1, m_Ui.lblPhoto);
        }

        // map DB controls
        {
            QHash<QString, QWidget *>::Iterator it;

            for (it = _m_hsDbControls.begin(); it != _m_hsDbControls.end(); ++ it) {
                _m_dmMapper->addMapping(it.value(), _m_tmModel->fieldIndex(it.key()));
            }
        }
    }

    //--------------------------------------------------
    // slots
    {
        connect(m_Ui.tabvInfo->selectionModel(), SIGNAL( currentRowChanged(QModelIndex,QModelIndex) ),
                _m_dmMapper,                     SLOT  ( setCurrentModelIndex(QModelIndex)) );

        connect(m_Ui.tabvInfo,                   SIGNAL( doubleClicked(const QModelIndex &) ),
                this,                            SLOT  ( slot_OnEdit() ));
    }

    //--------------------------------------------------
    // m_navNavigator
    {
        m_navNavigator.construct(_m_tmModel, m_Ui.tabvInfo);

        // go to the last record
        m_navNavigator.last();
    }
}
//---------------------------------------------------------------------------
void
CMain::_initActions() {
    // group "File"
    {
        connect(m_Ui.actFile_Exit,        SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnExit() ));
    }

    // group "Edit"
    {
        connect(m_Ui.actEdit_First,       SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnFirst() ));
        connect(m_Ui.actEdit_Prior,       SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnPrior() ));
        connect(m_Ui.actEdit_Next,        SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnNext() ));
        connect(m_Ui.actEdit_Last,        SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnLast() ));
        connect(m_Ui.actEdit_Insert,      SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnInsert() ));
        connect(m_Ui.actEdit_Delete,      SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnRemove() ));
        connect(m_Ui.actEdit_Edit,        SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnEdit() ));
        connect(m_Ui.actEdit_Post,        SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnPost() ));
        connect(m_Ui.actEdit_Cancel,      SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnCancel() ));
        connect(m_Ui.actEdit_Refresh,     SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnRefresh() ));
    }

    // group "Find"
    {
        connect(m_Ui.actFind_Search,      SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnSearch() ));
    }

    // group "View"
    {
    }

    // group "Options"
    {
        connect(m_Ui.actOptions_Settings, SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnSettings() ));
    }

    // group "Help"
    {
        connect(m_Ui.actHelp_Faq,         SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnFaq() ));

        connect(m_Ui.actHelp_About,       SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnAbout() ));
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

    const int   ciCurrentRow = _m_tmModel->rowCount() - 1;
    CPersonEdit dlgPersonEdit(this, _m_tmModel, ciCurrentRow);

    dlgPersonEdit.exec();
}
//---------------------------------------------------------------------------
void
CMain::slot_OnRemove() {
    m_navNavigator.remove();
}
//---------------------------------------------------------------------------
void
CMain::slot_OnEdit() {
    const int   ciCurrentRow = m_Ui.tabvInfo->currentIndex().row();
    CPersonEdit dlgPersonEdit(this, _m_tmModel, ciCurrentRow);

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
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CMain::_settingsLoad() {
    QSize  szSize;
    QPoint pnPosition;

    {
        QSettings stSettings(QCoreApplication::applicationName() + ".ini", QSettings::IniFormat, this);

        stSettings.beginGroup("main");
        szSize     = stSettings.value("size",     QSize(CONFIG_APP_WIDTH, CONFIG_APP_HEIGHT)).toSize();
        pnPosition = stSettings.value("position", QPoint(200, 200)).toPoint();
        stSettings.endGroup();
    }

    // apply settings
    {
        resize(szSize);
        move(pnPosition);
    }
}
//---------------------------------------------------------------------------
void
CMain::_settingsSave() {
    QSettings stSettings(QCoreApplication::applicationName() + ".ini", QSettings::IniFormat, this);

    stSettings.beginGroup("main");
    stSettings.setValue("position", pos());
    stSettings.setValue("size",     size());
    stSettings.endGroup();
}
//---------------------------------------------------------------------------
