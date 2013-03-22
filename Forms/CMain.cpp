/**
 * \file   CMain.cpp
 * \brief  main widget
 */


#include "CMain.h"

#include "../Forms/CEditor.h"
#include "../Forms/CAlbum.h"
#include "../Forms/CAbout.h"
#include "../QtLib/CUtils.h"
#include "../Classes/CSettings.h"
#include "../Classes/CDelegateDbImage.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CMain::CMain(
    QWidget         *a_parent,
    Qt::WindowFlags  a_flags
) :
    QMainWindow     (a_parent, a_flags),
    m_sAppName      (),
    m_sAppDir       (),
    m_sDbDir        (),
    m_sDbBackupDir  (),
    m_snSqlNavigator(this),
    m_wndAlbum      (NULL),
    _m_stApp        (NULL),
    _m_dbDatabase   (),
    _m_tmModel      (NULL),
    _m_hsDbItems    (),
    _m_dmImage      (NULL)
{
    _construct();

    _m_stApp = new CSettings(this, NULL, NULL);
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   protected
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* virtual */
void
CMain::closeEvent(
    QCloseEvent *a_event
)
{
    _destruct();
    a_event->accept();
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::_construct() {
    _initMain();
    _initModel();
    _initActions();
}
//------------------------------------------------------------------------------
void
CMain::_destruct() {
    qPTR_DELETE(_m_stApp);
}
//------------------------------------------------------------------------------
void
CMain::_initMain() {
    m_Ui.setupUi(this);

    //--------------------------------------------------
    // data
    {
        m_sAppName     = QCoreApplication::applicationName();
        m_sAppDir      = qApp->applicationDirPath();
        m_sDbDir       = m_sAppDir + QDir::separator() + DB_DIR_NAME;
        m_sDbBackupDir = m_sDbDir  + QDir::separator() + BACKUP_DIR_NAME;

        QDir().mkpath(m_sDbDir);
    }

    // main
    {
        setWindowTitle(APP_MAIN_TITLE);
        setGeometry(0, 0, APP_WIDTH, APP_HEIGHT);
        CUtils::widgetAlignCenter(this);
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
        m_Ui.lblPhoto->setFixedSize(PHOTO_WIDTH, PHOTO_HEIGHT);
        m_Ui.lblPhoto->setBackgroundRole(QPalette::Base);
    }
}
//------------------------------------------------------------------------------
void
CMain::_initModel() {
    //--------------------------------------------------
    // settings DB
    {
        bool bRv = QSqlDatabase::isDriverAvailable("QSQLITE");
        qCHECK_DO(!bRv, qMSG(QSqlDatabase().lastError().text()); return);

        _m_dbDatabase = QSqlDatabase::addDatabase("QSQLITE");
        _m_dbDatabase.setDatabaseName(
                        m_sDbDir + QDir::separator() +
                        m_sAppName +
                        DB_FILE_EXT);

        bRv = _m_dbDatabase.open();
        qCHECK_REF(bRv, _m_dbDatabase);

        // create table
        {
            QSqlQuery qryInfo(_m_dbDatabase);

            cQString  csSql = \
                "CREATE TABLE IF NOT EXISTS "
                "    " DB_T_PERSON
                "(   "
                "    " DB_F_ID                     " INTEGER PRIMARY KEY "
                                                   " AUTOINCREMENT "
                                                   " NOT NULL UNIQUE, "

                // Main
                "    " DB_F_MAIN_NICK              " VARCHAR (64), "
                "    " DB_F_MAIN_SURNAME           " VARCHAR (64), "
                "    " DB_F_MAIN_NAME              " VARCHAR (64), "
                "    " DB_F_MAIN_PATRONYMIC        " VARCHAR (64), "
                "    " DB_F_MAIN_AGE               " INT, "
                "    " DB_F_MAIN_HEIGHT            " INT, "
                "    " DB_F_MAIN_WEIGHT            " INT, "
                "    " DB_F_MAIN_HAIRLENGTH        " VARCHAR (64), "
                "    " DB_F_MAIN_HAIRCOLOR         " VARCHAR (64), "
                "    " DB_F_MAIN_APPEARANCE        " VARCHAR (64), "
                "    " DB_F_MAIN_STATUS            " VARCHAR (64), "

                // Phones
                "    " DB_F_PHONES_MOBILE1         " VARCHAR (64), "
                "    " DB_F_PHONES_MOBILE2         " VARCHAR (64), "
                "    " DB_F_PHONES_MOBILE3         " VARCHAR (64), "
                "    " DB_F_PHONES_HOME            " VARCHAR (64), "
                "    " DB_F_PHONES_JOB             " VARCHAR (64), "
                "    " DB_F_PHONES_OTHER           " VARCHAR (256), "

                // Address
                "    " DB_F_ADDRESS_COUNTRY        " VARCHAR (64), "
                "    " DB_F_ADDRESS_CODE           " VARCHAR (64), "
                "    " DB_F_ADDRESS_CITY           " VARCHAR (64), "
                "    " DB_F_ADDRESS_DISTRICT       " VARCHAR (64), "
                "    " DB_F_ADDRESS_STREET         " VARCHAR (64), "
                "    " DB_F_ADDRESS_HOUSE          " VARCHAR (64), "
                "    " DB_F_ADDRESS_PORCH          " VARCHAR (64), "
                "    " DB_F_ADDRESS_FLOOR          " VARCHAR (64), "
                "    " DB_F_ADDRESS_APARTMENT      " VARCHAR (64), "

                // E-mail
                "    " DB_F_EMAIL_EMAIL            " VARCHAR (256), "

                // Web
                "    " DB_F_WEB_WEB                " VARCHAR (256), "

                // Messengers
                "    " DB_F_MESSENGERS_ICQ         " VARCHAR (64), "
                "    " DB_F_MESSENGERS_SKYPE       " VARCHAR (64), "

                // Job
                "    " DB_F_JOB_PROFESSION         " VARCHAR (64), "
                "    " DB_F_JOB_ADDRESS            " VARCHAR (64), "
                "    " DB_F_JOB_SALARY             " VARCHAR (64), "
                "    " DB_F_JOB_COMPANY            " VARCHAR (64), "

                // Dates
                "    " DB_F_DATES_BIRTHDAY         " DATETIME, "
                "    " DB_F_DATES_BIRTHDAYFATHER   " DATETIME, "
                "    " DB_F_DATES_BIRTHDAYMOTHER   " DATETIME, "
                "    " DB_F_DATES_DAYDATING        " DATETIME, "
                "    " DB_F_DATES_DAYFIRSTKISS     " DATETIME, "
                "    " DB_F_DATES_DAYFIRSTSEX      " DATETIME, "

                // Interests
                "    " DB_F_INTERESTS_HOBBY        " VARCHAR (64), "
                "    " DB_F_INTERESTS_SPORTS       " VARCHAR (64), "
                "    " DB_F_INTERESTS_SMOKING      " VARCHAR (64), "
                "    " DB_F_INTERESTS_ALCOHOL      " VARCHAR (64), "
                "    " DB_F_INTERESTS_DRUGS        " VARCHAR (64), "

                // TODO: Periods

                // Etc
                "    " DB_F_ETC_DATECREATION       " DATETIME, "
                "    " DB_F_ETC_DATELASTCHANGE     " DATETIME, "

                // Notes
                "    " DB_F_NOTES_NOTES            " VARCHAR (256), "

                // Photos
                "    " DB_F_PHOTOS_1               " BLOB, "
                "    " DB_F_PHOTOS_2               " BLOB, "
                "    " DB_F_PHOTOS_3               " BLOB, "
                "    " DB_F_PHOTOS_4               " BLOB, "
                "    " DB_F_PHOTOS_5               " BLOB, "
                "    " DB_F_PHOTOS_6               " BLOB, "
                "    " DB_F_PHOTOS_7               " BLOB, "
                "    " DB_F_PHOTOS_8               " BLOB, "
                "    " DB_F_PHOTOS_9               " BLOB, "
                "    " DB_F_PHOTOS_10              " BLOB, "
                "    " DB_F_PHOTOS_11              " BLOB, "
                "    " DB_F_PHOTOS_12              " BLOB, "
                "    " DB_F_PHOTOS_13              " BLOB, "
                "    " DB_F_PHOTOS_14              " BLOB, "
                "    " DB_F_PHOTOS_15              " BLOB, "
                "    " DB_F_PHOTOS_PRIMARY_DBFIELD " INT "
                ")";

            bRv = qryInfo.exec(csSql);
            qCHECK_REF(bRv, qryInfo);
        }
    }

    //--------------------------------------------------
    // _m_tmModel
    {
        struct SHeader {
            cint      section;
            cQVariant value;
        };

        const SHeader chdHeaders[] = {
            {0,  DB_CF_ID},

            // Main
            {1,  DB_CF_MAIN_NICK},
            {2,  DB_CF_MAIN_SURNAME},
            {3,  DB_CF_MAIN_NAME},
            {4,  DB_CF_MAIN_PATRONYMIC},
            {5,  DB_CF_MAIN_AGE},
            {6,  DB_CF_MAIN_HEIGHT},
            {7,  DB_CF_MAIN_WEIGHT},
            {8,  DB_CF_MAIN_HAIRLENGTH},
            {9,  DB_CF_MAIN_HAIRCOLOR},
            {10, DB_CF_MAIN_APPEARANCE},
            {11, DB_CF_MAIN_STATUS},

            // Phones
            {12, DB_CF_PHONES_MOBILE1},
            {13, DB_CF_PHONES_MOBILE2},
            {14, DB_CF_PHONES_MOBILE3},
            {15, DB_CF_PHONES_HOME},
            {16, DB_CF_PHONES_JOB},
            {17, DB_CF_PHONES_OTHER},

            // Address
            {18, DB_CF_ADDRESS_COUNTRY},
            {19, DB_CF_ADDRESS_CODE},
            {20, DB_CF_ADDRESS_CITY},
            {21, DB_CF_ADDRESS_DISTRICT},
            {22, DB_CF_ADDRESS_STREET},
            {23, DB_CF_ADDRESS_HOUSE},
            {24, DB_CF_ADDRESS_PORCH},
            {25, DB_CF_ADDRESS_FLOOR},
            {26, DB_CF_ADDRESS_APARTMENT},

            // E-mail
            {27, DB_CF_EMAIL_EMAIL},

            // Web
            {28, DB_CF_WEB_WEB},

            // Messengers
            {29, DB_CF_MESSENGERS_ICQ},
            {30, DB_CF_MESSENGERS_SKYPE},

            // Job
            {31, DB_CF_JOB_PROFESSION},
            {32, DB_CF_JOB_ADDRESS},
            {33, DB_CF_JOB_SALARY},
            {34, DB_CF_JOB_COMPANY},

            // Dates
            {35, DB_CF_DATES_BIRTHDAY},
            {36, DB_CF_DATES_BIRTHDAYFATHER},
            {37, DB_CF_DATES_BIRTHDAYMOTHER},
            {38, DB_CF_DATES_DAYDATING},
            {39, DB_CF_DATES_DAYFIRSTKISS},
            {40, DB_CF_DATES_DAYFIRSTSEX},

            // Interests
            {41, DB_CF_INTERESTS_HOBBY},
            {42, DB_CF_INTERESTS_SPORTS},
            {43, DB_CF_INTERESTS_SMOKING},
            {44, DB_CF_INTERESTS_ALCOHOL},
            {45, DB_CF_INTERESTS_DRUGS},

            // TODO: Periods

            // Etc
            {46, DB_CF_ETC_DATECREATION},
            {47, DB_CF_ETC_DATELASTCHANGE},

            // Notes
            {48, DB_CF_NOTES_NOTES},

            // Photos
            {49, DB_CF_PHOTOS_1},
            {50, DB_CF_PHOTOS_2},
            {51, DB_CF_PHOTOS_3},
            {52, DB_CF_PHOTOS_4},
            {53, DB_CF_PHOTOS_5},
            {54, DB_CF_PHOTOS_6},
            {55, DB_CF_PHOTOS_7},
            {56, DB_CF_PHOTOS_8},
            {57, DB_CF_PHOTOS_9},
            {58, DB_CF_PHOTOS_10},
            {59, DB_CF_PHOTOS_11},
            {60, DB_CF_PHOTOS_12},
            {61, DB_CF_PHOTOS_13},
            {62, DB_CF_PHOTOS_14},
            {63, DB_CF_PHOTOS_15},
            {64, DB_CF_PHOTOS_PRIMARY_DBFIELD}
        };

        _m_tmModel = new QSqlTableModel(this, _m_dbDatabase);
        _m_tmModel->setTable(DB_T_PERSON);

        // set caption for DB fieleds
        for (size_t i = 0; i < qARRAY_LENGTH(chdHeaders); ++ i) {
            _m_tmModel->setHeaderData(
                    chdHeaders[i].section,
                    Qt::Horizontal,
                    chdHeaders[i].value);
        }

        _m_tmModel->setEditStrategy(QSqlTableModel::OnFieldChange);
        _m_tmModel->select();
    }

    //--------------------------------------------------
    // m_Ui.tvInfo
    {
        m_Ui.tvInfo->setModel(_m_tmModel);
        m_Ui.tvInfo->hideColumn(0); // don't show the DB_F_ID
        // m_Ui.tvInfo->setColumnWidth(0, 40);
        m_Ui.tvInfo->verticalHeader()->setVisible(true);
        m_Ui.tvInfo->verticalHeader()->setDefaultSectionSize(TABLEVIEW_ROW_HEIGHT);
        m_Ui.tvInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_Ui.tvInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_Ui.tvInfo->setSelectionMode(QAbstractItemView::SingleSelection);
        m_Ui.tvInfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        m_Ui.tvInfo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        // m_Ui.tvInfo->setAlternatingRowColors(true);
        // m_Ui.tvInfo->setStyleSheet("alternate-background-color: white; background-color: gray;");
        m_Ui.tvInfo->setSortingEnabled(true);
        m_Ui.tvInfo->sortByColumn(0, Qt::AscendingOrder);

        m_Ui.tvInfo->show();
    }

    //--------------------------------------------------
    // _m_dmImage
    {
        _m_dmImage = new QDataWidgetMapper(this);
        _m_dmImage->setModel(_m_tmModel);
        _m_dmImage->setItemDelegate(
                        new CDelegateDbImage(
                                _m_dmImage,
                                _m_tmModel->fieldIndex(DB_F_PHOTOS_1),
                                PHOTO_SIZE,
                                m_Ui.lblPhotoSize));
        _m_dmImage->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

        // DB items to QHash
        {
             // Photos
            _m_hsDbItems.insert(m_Ui.lblPhoto, DB_F_PHOTOS_1);
        }

        // map DB items
        {
            cdb_items_t::ConstIterator cit;

            for (cit  = _m_hsDbItems.constBegin();
                 cit != _m_hsDbItems.constEnd();
                 ++ cit)
            {
                QWidget *widget  = cit.key();
                cint     section = _m_tmModel->fieldIndex( cit.value() );

                _m_dmImage->addMapping(widget, section);
            }
        }
    }

    //--------------------------------------------------
    // slots
    {
        connect(m_Ui.tvInfo->selectionModel(), &QItemSelectionModel::currentRowChanged,
                _m_dmImage,                    &QDataWidgetMapper::setCurrentModelIndex );

        connect(m_Ui.tvInfo,                   &QTableView::doubleClicked,
                this,                          &CMain::slot_OnEdit);

        connect(m_Ui.tbtnPhotoAlbum,           &QToolButton::clicked,
                this,                          &CMain::slot_OnAlbum);
    }

    //--------------------------------------------------
    // m_snSqlNavigator
    {
        m_snSqlNavigator.construct(_m_tmModel, m_Ui.tvInfo);
        m_snSqlNavigator.last();
    }
}
//------------------------------------------------------------------------------
void
CMain::_initActions() {
    // group "File"
    {
        connect(m_Ui.actFile_Exit,        &QAction::triggered,
                this,                     &CMain::slot_OnExit);
    }

    // group "Edit"
    {
        connect(m_Ui.actEdit_First,       &QAction::triggered,
                this,                     &CMain::slot_OnFirst);
        connect(m_Ui.actEdit_Prior,       &QAction::triggered,
                this,                     &CMain::slot_OnPrior);
        connect(m_Ui.actEdit_Next,        &QAction::triggered,
                this,                     &CMain::slot_OnNext);
        connect(m_Ui.actEdit_Last,        &QAction::triggered,
                this,                     &CMain::slot_OnLast);
        connect(m_Ui.actEdit_GoTo,        &QAction::triggered,
                this,                     &CMain::slot_OnGoTo);
        connect(m_Ui.actEdit_Insert,      &QAction::triggered,
                this,                     &CMain::slot_OnInsert);
        connect(m_Ui.actEdit_Delete,      &QAction::triggered,
                this,                     &CMain::slot_OnRemove);
        connect(m_Ui.actEdit_Edit,        &QAction::triggered,
                this,                     &CMain::slot_OnEdit);
    }

    // group "Find"
    {
        connect(m_Ui.actFind_Search,      &QAction::triggered,
                this,                     &CMain::slot_OnSearch);
    }

    // group "View"
    {
    }

    // group "Options"
    {
        connect(m_Ui.actOptions_Settings, &QAction::triggered,
                this,                     &CMain::slot_OnSettings);
    }

    // group "Help"
    {
        connect(m_Ui.actHelp_Faq,         &QAction::triggered,
                this,                     &CMain::slot_OnFaq);

        connect(m_Ui.actHelp_About,       &QAction::triggered,
                this,                     &CMain::slot_OnAbout);
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "File"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::slot_OnExit() {
    close();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "Edit"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::slot_OnFirst() {
    m_snSqlNavigator.first();
}
//------------------------------------------------------------------------------
void
CMain::slot_OnPrior() {
    m_snSqlNavigator.prior();
}
//------------------------------------------------------------------------------
void
CMain::slot_OnNext() {
    m_snSqlNavigator.next();
}
//------------------------------------------------------------------------------
void
CMain::slot_OnLast() {
    m_snSqlNavigator.last();
}
//------------------------------------------------------------------------------
void
CMain::slot_OnGoTo() {
    cint ciCurrentRow = m_snSqlNavigator.view()->currentIndex().row() + 1;
    cint ciMinValue   = 1;
    cint ciMaxValue   = CUtils::sqlTableModelRowCount(_m_tmModel);

    cint ciTargetRow = QInputDialog::getInt(
                            this,
                            APP_NAME, tr("Go to row:"),
                            ciCurrentRow,
                            ciMinValue, ciMaxValue) - 1;

    m_snSqlNavigator.goTo(ciTargetRow);
}
//------------------------------------------------------------------------------
void
CMain::slot_OnInsert() {
    m_snSqlNavigator.insert();

    {
        CEditor dlgPersonEdit(this, _m_tmModel, &m_snSqlNavigator);

        (int)dlgPersonEdit.exec();
    }
}
//------------------------------------------------------------------------------
void
CMain::slot_OnRemove() {
    QMessageBox msgBox;

    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(tr("Removing record."));
    msgBox.setInformativeText(tr("Do you want to remove record?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    cint ciRv = msgBox.exec();
    switch (ciRv) {
        case QMessageBox::Yes:
            m_snSqlNavigator.remove();
            break;
        case QMessageBox::Cancel:
        default:
            break;
    }
}
//------------------------------------------------------------------------------
void
CMain::slot_OnEdit() {
    CEditor dlgPersonEdit(this, _m_tmModel, &m_snSqlNavigator);

    (int)dlgPersonEdit.exec();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "Find"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::slot_OnSearch() {

}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "View"
*
*******************************************************************************/


/*******************************************************************************
*   group "Options"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::slot_OnSettings() {

}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "Help"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::slot_OnFaq() {

}
//------------------------------------------------------------------------------
void
CMain::slot_OnAbout() {
    CAbout wndAbout(this);

    (int)wndAbout.exec();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   photo
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::slot_OnAlbum() {
    delete m_wndAlbum;
    m_wndAlbum = NULL;

    m_wndAlbum = new CAlbum(this, _m_tmModel, &m_snSqlNavigator);
    m_wndAlbum->show();
}
//------------------------------------------------------------------------------
