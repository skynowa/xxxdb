/**
 * \file   CMain.cpp
 * \brief  main widget
 */


#include "CMain.h"

#include "../QtLib/CUtils.h"
#include "../QtLib/CApplication.h"
#include "../Classes/CIni.h"
#include "CAlbum.h"
#include "CColumns.h"
#include "CAbout.h"
#include "CSettings.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CMain::CMain(
    QWidget         *a_parent,
    Qt::WindowFlags  a_flags
) :
    QMainWindow  (a_parent, a_flags),
    snNavigator  (this),
    wndAlbum     (NULL),
    _trTranslator(NULL),
    _sTranslatorLang(),
    _dbDatabase  (),
    _tmModel     (NULL),
    _dmText      (NULL),
    _hsDbItems   (),
    _cboFindText (NULL),
    _cboDbFields (NULL)
{
    _construct();

    // CIni
    {
        CIni::construct();
        CIni::get(this);
    }

    snNavigator.last();
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   protected
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* virtual */
void
CMain::keyPressEvent(
    QKeyEvent *a_event
)
{
    // addition UI shortcuts
    switch (a_event->key()) {
        // call editor by 'Enter'
        case Qt::Key_Enter:
            actEdit_onEdit();
            break;
        default:
            break;
    }

    QMainWindow::keyPressEvent(a_event);
}
//------------------------------------------------------------------------------
void
CMain::changeEvent(
    QEvent *a_event
)
{
    // retranslation
    if (a_event->type() == QEvent::LanguageChange) {
        ui.retranslateUi(this);
        _retranslateUi();

        // TODO: ui.lblPhotoInfo
    }

    QWidget::changeEvent(a_event);
}
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
CMain::_construct()
{
    _initModel();
    _initMain();
    _initInfoDetail();
    _initActions();
}
//------------------------------------------------------------------------------
void
CMain::_destruct()
{
    // _trTranslator
    {
        CApplication::removeTranslator(_trTranslator);
        qPTR_DELETE(_trTranslator);
    }

    // CIni
    {
        CIni::set(this);
        CIni::destruct();
    }
}
//------------------------------------------------------------------------------
void
CMain::_initMain()
{
    // _trTranslator - call first
    {
        _trTranslator = new QTranslator(this);
    }

    ui.setupUi(this);

    //--------------------------------------------------
    // data
    {
        QDir().mkpath( CApplication::dbDirPath() );
        QDir().mkpath( CApplication::dbBackupDirPath() );
    }

    // main
    {
        setGeometry(0, 0, APP_WIDTH, APP_HEIGHT);
    }

    // quick find
    {
        // _cboFindText
        _cboFindText = new QComboBox(this);
        _cboFindText->setEditable(true);
        _cboFindText->setFixedWidth(FIND_TEXT_WIDTH);

        connect(_cboFindText, &QComboBox::currentTextChanged,
                this,         &CMain::onQuickFind);

        ui.tbQuickFind->addWidget(_cboFindText);

        // _cboDbFields
        _cboDbFields = new QComboBox(this);
        _cboDbFields->setMaxVisibleItems( _cboDbFields->maxVisibleItems() * 2 );

        for (int i = 0; i < _tmModel->columnCount(); ++ i) {
            qCHECK_DO(CConfig::dbRecords[i].isNonUi, continue);

            _cboDbFields->addItem(CConfig::dbRecords[i].caption);
        }

        connect(_cboDbFields, &QComboBox::currentTextChanged,
                this,         &CMain::cboDbFields_onCurrentTextChanged);

        ui.tbQuickFind->addWidget(_cboDbFields);
    }

    //--------------------------------------------------
    // ui.tabInfo
    {
        ui.tabInfo->setTabText(0, tr("Full view"));
        ui.tabInfo->setTabText(1, tr("Detail view"));
    }

    //--------------------------------------------------
    // ui.tvInfo
    {
        ui.tvInfo->setModel(_tmModel);
        ui.tvInfo->verticalHeader()->setVisible(true);
        ui.tvInfo->verticalHeader()->setDefaultSectionSize(TABLEVIEW_ROW_HEIGHT);
        ui.tvInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui.tvInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui.tvInfo->setSelectionMode(QAbstractItemView::SingleSelection);
        ui.tvInfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ui.tvInfo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ui.tvInfo->setSortingEnabled(true);
        ui.tvInfo->sortByColumn(0, Qt::AscendingOrder);

        ui.tvInfo->show();
    }

    //--------------------------------------------------
    // snNavigator
    {
        snNavigator.construct(_tmModel, ui.tvInfo);
    }

    //--------------------------------------------------
    // ui.dbPhoto
    {
        cint ciDbRecordIndex = snNavigator.view()->currentIndex().row();

        ui.dbPhoto->construct(this, _tmModel, DB_F_PHOTOS_1, 0,
            ciDbRecordIndex, PHOTO_SIZE, ui.lblPhotoInfo);
        //// ui.dbPhoto->setFixedSize(PHOTO_SIZE);
        ui.dbPhoto->setBackgroundRole(QPalette::Base);

        connect(snNavigator.view()->selectionModel(), &QItemSelectionModel::currentRowChanged,
                ui.dbPhoto->mapper(), &QDataWidgetMapper::setCurrentModelIndex);
        connect(ui.dbPhoto, &CDbImage::sig_doubleClicked,
                this,       &CMain::actView_onAlbum);
    }

    //--------------------------------------------------
    // slots
    {
        connect(snNavigator.view(),   &QTableView::doubleClicked,
                this,                 &CMain::actEdit_onEdit);
        connect(ui.tbtnAlbum,         &QToolButton::clicked,
                this,                 &CMain::actView_onAlbum);
        connect(ui.tabInfo,           &QTabWidget::currentChanged,
                this,                 &CMain::tabInfo_onCurrentChanged);

        QShortcut *shortCut = new QShortcut(Qt::CTRL + Qt::Key_F, this);
    #if 0
        connect(shortCut,                 &QShortcut::activated,
                _cboFindText->lineEdit(), &QLineEdit::setFocus);
    #else
        connect(shortCut,                 SIGNAL( activated() ),
                _cboFindText->lineEdit(), SLOT  ( setFocus() ));
    #endif
    }
}
//------------------------------------------------------------------------------
void
CMain::_initInfoDetail()
{
    // maps ui controls into DB fields
    {
        // DB items to QHash
        {
            qTEST(_hsDbItems.isEmpty());

            // Main
            _hsDbItems.insert(ui.cboNick,          DB_F_MAIN_NICK);
            _hsDbItems.insert(ui.cboSurname,       DB_F_MAIN_SURNAME);
            _hsDbItems.insert(ui.cboName,          DB_F_MAIN_NAME);
            _hsDbItems.insert(ui.cboPatronymic,    DB_F_MAIN_PATRONYMIC);
            _hsDbItems.insert(ui.cboAge,           DB_F_MAIN_AGE);
            _hsDbItems.insert(ui.cboHeight,        DB_F_MAIN_HEIGHT);
            _hsDbItems.insert(ui.cboWeight,        DB_F_MAIN_WEIGHT);
            _hsDbItems.insert(ui.cboHairLength,    DB_F_MAIN_HAIRLENGTH);
            _hsDbItems.insert(ui.cboHairColor,     DB_F_MAIN_HAIRCOLOR);
            _hsDbItems.insert(ui.cboAppearance,    DB_F_MAIN_APPEARANCE);
            _hsDbItems.insert(ui.cboAgreement,     DB_F_MAIN_STATUS);

            // Phones
            _hsDbItems.insert(ui.cboMobile1,       DB_F_PHONES_MOBILE1);
            _hsDbItems.insert(ui.cboMobile2,       DB_F_PHONES_MOBILE2);
            _hsDbItems.insert(ui.cboMobile3,       DB_F_PHONES_MOBILE3);
            _hsDbItems.insert(ui.cboPhoneHome,     DB_F_PHONES_HOME);
            _hsDbItems.insert(ui.cboPhoneJob,      DB_F_PHONES_JOB);
            _hsDbItems.insert(ui.tedtPhoneOther,   DB_F_PHONES_OTHER);

            // Address
            _hsDbItems.insert(ui.cboCountry,       DB_F_ADDRESS_COUNTRY);
            _hsDbItems.insert(ui.cboCode,          DB_F_ADDRESS_CODE);
            _hsDbItems.insert(ui.cboCity,          DB_F_ADDRESS_CITY);
            _hsDbItems.insert(ui.cboDistrict,      DB_F_ADDRESS_DISTRICT);
            _hsDbItems.insert(ui.cboStreet,        DB_F_ADDRESS_STREET);
            _hsDbItems.insert(ui.cboHouse,         DB_F_ADDRESS_HOUSE);
            _hsDbItems.insert(ui.cboPorch,         DB_F_ADDRESS_PORCH);
            _hsDbItems.insert(ui.cboFloor,         DB_F_ADDRESS_FLOOR);
            _hsDbItems.insert(ui.cboApartment,     DB_F_ADDRESS_APARTMENT);

            // E-mail
            _hsDbItems.insert(ui.tedtEmail,        DB_F_EMAIL_EMAIL);

            // Web
            _hsDbItems.insert(ui.tedtWeb,          DB_F_WEB_WEB);

            // Messengers
            _hsDbItems.insert(ui.cboIcq,           DB_F_MESSENGERS_ICQ);
            _hsDbItems.insert(ui.cboSkype,         DB_F_MESSENGERS_SKYPE);

            // Job
            _hsDbItems.insert(ui.cboProfession,    DB_F_JOB_PROFESSION);
            _hsDbItems.insert(ui.cboAddress,       DB_F_JOB_ADDRESS);
            _hsDbItems.insert(ui.cboSalary,        DB_F_JOB_SALARY);
            _hsDbItems.insert(ui.cboCompany,       DB_F_JOB_COMPANY);

            // Dates
            _hsDbItems.insert(ui.dtBirthday,       DB_F_DATES_BIRTHDAY);
            _hsDbItems.insert(ui.dtBirthdayFather, DB_F_DATES_BIRTHDAYFATHER);
            _hsDbItems.insert(ui.dtBirthdayMother, DB_F_DATES_BIRTHDAYMOTHER);
            _hsDbItems.insert(ui.dtDayDating,      DB_F_DATES_DAYDATING);
            _hsDbItems.insert(ui.dtDayFirstKiss,   DB_F_DATES_DAYFIRSTKISS);
            _hsDbItems.insert(ui.dtDayFirstSex,    DB_F_DATES_DAYFIRSTSEX);

            // Interests
            _hsDbItems.insert(ui.cboHobby,         DB_F_INTERESTS_HOBBY);
            _hsDbItems.insert(ui.cboSports,        DB_F_INTERESTS_SPORTS);
            _hsDbItems.insert(ui.cboSmoking,       DB_F_INTERESTS_SMOKING);
            _hsDbItems.insert(ui.cboAlcohol,       DB_F_INTERESTS_ALCOHOL);
            _hsDbItems.insert(ui.cboDrugs,         DB_F_INTERESTS_DRUGS);

            // TODO: Periods

            // TODO: Etc

            // Note
            _hsDbItems.insert(ui.tedtNotes,        DB_F_NOTES_NOTES);
        }

        // map DB items
        {
            // _dmText
            _dmText = new QDataWidgetMapper(this);
            _dmText->setModel(_tmModel);
            _dmText->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

            // map
            Q_FOREACH (QWidget *key, _hsDbItems.keys()) {
                QWidget *widget  = key;
                cint     section = _tmModel->fieldIndex(_hsDbItems.value(key));

                _dmText->addMapping(widget, section);
            }

            connect(ui.tvInfo->selectionModel(), &QItemSelectionModel::currentRowChanged,
                    _dmText,                     &QDataWidgetMapper::setCurrentModelIndex );
        }
    }

    // ui.dbPhoto_2
    {
        cint ciDbRecordIndex = snNavigator.view()->currentIndex().row();

        ui.dbPhoto_2->construct(this, _tmModel, DB_F_PHOTOS_1, 0,
            ciDbRecordIndex, PHOTO_SIZE, ui.lblPhotoInfo);
        //// ui.dbPhoto_2->setFixedSize(PHOTO_SIZE);
        ui.dbPhoto_2->setBackgroundRole(QPalette::Base);

        connect(snNavigator.view()->selectionModel(), &QItemSelectionModel::currentRowChanged,
                ui.dbPhoto_2->mapper(), &QDataWidgetMapper::setCurrentModelIndex);
        connect(ui.dbPhoto_2, &CDbImage::sig_doubleClicked,
                this,         &CMain::actView_onAlbum);
    }

    // signals
    {
        connect(ui.tbtnPhotoAlbum, &QToolButton::clicked,
                this,              &CMain::onAlbum);
        connect(ui.twGroups,       &QTreeWidget::currentItemChanged,
                this,              &CMain::twGroups_onCurrentItemChanged);
    }
}
//------------------------------------------------------------------------------
void
CMain::_initModel()
{
    //--------------------------------------------------
    // settings DB
    {
        bool bRv = QSqlDatabase::isDriverAvailable("QSQLITE");
        qCHECK_DO(!bRv, qMSG(QSqlDatabase().lastError().text()); return);

        _dbDatabase = QSqlDatabase::addDatabase("QSQLITE");
        _dbDatabase.setDatabaseName( CApplication::dbFilePath() );

        bRv = _dbDatabase.open();
        qCHECK_REF(bRv, _dbDatabase);

        // create table
        {
            QSqlQuery qryTableCreate(_dbDatabase);

            cQString  csSql = \
                "CREATE TABLE IF NOT EXISTS "
                "    " DB_T_PERSON
                "(   "
                "    " DB_F_ID                   " INTEGER PRIMARY KEY "
                                                 " AUTOINCREMENT "
                                                 " NOT NULL UNIQUE, "

                // Main
                "    " DB_F_MAIN_NICK            " VARCHAR(64), "
                "    " DB_F_MAIN_SURNAME         " VARCHAR(64), "
                "    " DB_F_MAIN_NAME            " VARCHAR(64), "
                "    " DB_F_MAIN_PATRONYMIC      " VARCHAR(64), "
                "    " DB_F_MAIN_AGE             " INT, "
                "    " DB_F_MAIN_HEIGHT          " INT, "
                "    " DB_F_MAIN_WEIGHT          " INT, "
                "    " DB_F_MAIN_HAIRLENGTH      " VARCHAR(64), "
                "    " DB_F_MAIN_HAIRCOLOR       " VARCHAR(64), "
                "    " DB_F_MAIN_APPEARANCE      " VARCHAR(64), "
                "    " DB_F_MAIN_STATUS          " VARCHAR(64), "

                // Phones
                "    " DB_F_PHONES_MOBILE1       " VARCHAR(64), "
                "    " DB_F_PHONES_MOBILE2       " VARCHAR(64), "
                "    " DB_F_PHONES_MOBILE3       " VARCHAR(64), "
                "    " DB_F_PHONES_HOME          " VARCHAR(64), "
                "    " DB_F_PHONES_JOB           " VARCHAR(64), "
                "    " DB_F_PHONES_OTHER         " VARCHAR(256), "

                // Address
                "    " DB_F_ADDRESS_COUNTRY      " VARCHAR(64), "
                "    " DB_F_ADDRESS_CODE         " VARCHAR(64), "
                "    " DB_F_ADDRESS_CITY         " VARCHAR(64), "
                "    " DB_F_ADDRESS_DISTRICT     " VARCHAR(64), "
                "    " DB_F_ADDRESS_STREET       " VARCHAR(64), "
                "    " DB_F_ADDRESS_HOUSE        " VARCHAR(64), "
                "    " DB_F_ADDRESS_PORCH        " VARCHAR(64), "
                "    " DB_F_ADDRESS_FLOOR        " VARCHAR(64), "
                "    " DB_F_ADDRESS_APARTMENT    " VARCHAR(64), "

                // E-mail
                "    " DB_F_EMAIL_EMAIL          " VARCHAR(256), "

                // Web
                "    " DB_F_WEB_WEB              " VARCHAR(256), "

                // Messengers
                "    " DB_F_MESSENGERS_ICQ       " VARCHAR(64), "
                "    " DB_F_MESSENGERS_SKYPE     " VARCHAR(64), "

                // Job
                "    " DB_F_JOB_PROFESSION       " VARCHAR(64), "
                "    " DB_F_JOB_ADDRESS          " VARCHAR(64), "
                "    " DB_F_JOB_SALARY           " VARCHAR(64), "
                "    " DB_F_JOB_COMPANY          " VARCHAR(64), "

                // Dates
                "    " DB_F_DATES_BIRTHDAY       " DATETIME, "
                "    " DB_F_DATES_BIRTHDAYFATHER " DATETIME, "
                "    " DB_F_DATES_BIRTHDAYMOTHER " DATETIME, "
                "    " DB_F_DATES_DAYDATING      " DATETIME, "
                "    " DB_F_DATES_DAYFIRSTKISS   " DATETIME, "
                "    " DB_F_DATES_DAYFIRSTSEX    " DATETIME, "

                // Interests
                "    " DB_F_INTERESTS_HOBBY      " VARCHAR(64), "
                "    " DB_F_INTERESTS_SPORTS     " VARCHAR(64), "
                "    " DB_F_INTERESTS_SMOKING    " VARCHAR(64), "
                "    " DB_F_INTERESTS_ALCOHOL    " VARCHAR(64), "
                "    " DB_F_INTERESTS_DRUGS      " VARCHAR(64), "

                // TODO: Periods

                // Etc
                "    " DB_F_ETC_DATECREATION     " DATETIME, "
                "    " DB_F_ETC_DATELASTCHANGE   " DATETIME, "

                // Notes
                "    " DB_F_NOTES_NOTES          " VARCHAR(256), "

                // Photos
                "    " DB_F_PHOTOS_1             " BLOB, "
                "    " DB_F_PHOTOS_2             " BLOB, "
                "    " DB_F_PHOTOS_3             " BLOB, "
                "    " DB_F_PHOTOS_4             " BLOB, "
                "    " DB_F_PHOTOS_5             " BLOB, "
                "    " DB_F_PHOTOS_6             " BLOB, "
                "    " DB_F_PHOTOS_7             " BLOB, "
                "    " DB_F_PHOTOS_8             " BLOB, "
                "    " DB_F_PHOTOS_9             " BLOB, "
                "    " DB_F_PHOTOS_10            " BLOB, "
                "    " DB_F_PHOTOS_11            " BLOB, "
                "    " DB_F_PHOTOS_12            " BLOB, "
                "    " DB_F_PHOTOS_13            " BLOB, "
                "    " DB_F_PHOTOS_14            " BLOB, "
                "    " DB_F_PHOTOS_15            " BLOB, "
                "    " DB_F_PHOTOS_PRIMARY       " INT "
                ")";

            bRv = qryTableCreate.exec(csSql);
            qCHECK_REF(bRv, qryTableCreate);
        }
    }

    //--------------------------------------------------
    // _tmModel
    {
        _tmModel = new QSqlTableModel(this, _dbDatabase);
        _tmModel->setTable(DB_T_PERSON);

        // set caption for DB fields
        for (int i = 0; i < _tmModel->columnCount(); ++ i) {
            _tmModel->setHeaderData(
                    CConfig::dbRecords[i].index,
                    Qt::Horizontal,
                    CConfig::dbRecords[i].caption);
        }

        _tmModel->setEditStrategy(QSqlTableModel::OnFieldChange);
        bool bRv = _tmModel->select();
        qTEST(bRv);
    }

    qTEST((int)qARRAY_LENGTH(CConfig::dbRecords) == _tmModel->columnCount());
}
//------------------------------------------------------------------------------
void
CMain::_initActions()
{
    // group "File"
    {
        connect(ui.actFile_Exit,     &QAction::triggered,
                this,                &CMain::actFile_onExit);
        connect(ui.actFile_Minimize, &QAction::triggered,
                this,                &CMain::actFile_onMinimize);
    }

    // group "Edit"
    {
        connect(ui.actEdit_First,  &QAction::triggered,
                this,              &CMain::actEdit_onFirst);
        connect(ui.actEdit_Prior,  &QAction::triggered,
                this,              &CMain::actEdit_onPrior);
        connect(ui.actEdit_Next,   &QAction::triggered,
                this,              &CMain::actEdit_onNext);
        connect(ui.actEdit_Last,   &QAction::triggered,
                this,              &CMain::actEdit_onLast);
        connect(ui.actEdit_GoTo,   &QAction::triggered,
                this,              &CMain::actEdit_onGoTo);
        connect(ui.actEdit_Insert, &QAction::triggered,
                this,              &CMain::actEdit_onInsert);
        connect(ui.actEdit_Delete, &QAction::triggered,
                this,              &CMain::actEdit_onRemove);
        connect(ui.actEdit_Edit,   &QAction::triggered,
                this,              &CMain::actEdit_onEdit);
    }

    // group "Find"
    {
        connect(ui.actFind_Search,    &QAction::triggered,
                this,                 &CMain::actFind_onSearch);
        connect(ui.actFind_TextClear, &QAction::triggered,
                this,                 &CMain::actFind_onTextClear);
    }

    // group "View"
    {
        connect(ui.actView_MainToolbar,      &QAction::triggered,
                this,                        &CMain::actView_onMainToolbar);
        connect(ui.actView_QuickFindToolbar, &QAction::triggered,
                this,                        &CMain::actView_onQuickFindToolbar);
        connect(ui.actView_Columns,          &QAction::triggered,
                this,                        &CMain::actView_onColumns);
        connect(ui.actView_Album,            &QAction::triggered,
                this,                        &CMain::actView_onAlbum);
        connect(ui.actView_Statusbar,        &QAction::triggered,
                this,                        &CMain::actView_onStatusbar);

        // Language

        // use radio actions
        QActionGroup *agGroup = new QActionGroup(this);
        ui.actViewLanguage_En->setActionGroup(agGroup);
        ui.actViewLanguage_Ru->setActionGroup(agGroup);

        connect(ui.actViewLanguage_En,       &QAction::triggered,
                this,                        &CMain::actView_onLanguageEn);
        connect(ui.actViewLanguage_Ru,       &QAction::triggered,
                this,                        &CMain::actView_onLanguageRu);
    }

    // group "Options"
    {
        connect(ui.actOptions_Settings, &QAction::triggered,
                this,                   &CMain::actOptions_onSettings);
    }

    // group "Help"
    {
        connect(ui.actHelp_Faq,   &QAction::triggered,
                this,             &CMain::actHelp_onFaq);

        connect(ui.actHelp_About, &QAction::triggered,
                this,             &CMain::actHelp_onAbout);
    }
}
//------------------------------------------------------------------------------
void
CMain::_retranslateUi()
{
    // ui.tvInfo
    for (int i = 0; i < _tmModel->columnCount(); ++ i) {
        _tmModel->setHeaderData(
                CConfig::dbRecords[i].index,
                Qt::Horizontal,
                qApp->translate("CConfig", CConfig::dbRecords[i].caption));
    }

    // _cboDbFields
    for (int i = 0; i < _tmModel->columnCount(); ++ i) {
        _cboDbFields->setItemText(
            i,
            qApp->translate("CConfig", CConfig::dbRecords[i].caption)
        );
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "File"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::actFile_onExit()
{
    close();
}
//------------------------------------------------------------------------------
void
CMain::actFile_onMinimize()
{
    setWindowState(Qt::WindowMinimized);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "Edit"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::actEdit_onFirst()
{
    snNavigator.first();
}
//------------------------------------------------------------------------------
void
CMain::actEdit_onPrior()
{
    snNavigator.prior();
}
//------------------------------------------------------------------------------
void
CMain::actEdit_onNext()
{
    snNavigator.next();
}
//------------------------------------------------------------------------------
void
CMain::actEdit_onLast()
{
    snNavigator.last();
}
//------------------------------------------------------------------------------
void
CMain::actEdit_onGoTo()
{
    qCHECK_DO(snNavigator.view()->currentIndex().row() < 0, return);

    cint ciCurrentRow = snNavigator.view()->currentIndex().row() + 1;
    cint ciMinValue   = 1;
    cint ciMaxValue   = CUtils::sqlTableModelRowCount(_tmModel);

    cint ciTargetRow  = QInputDialog::getInt(
                            this,
                            APP_NAME,
                            tr("Go to row (total %1 rows):").arg(ciMaxValue),
                            ciCurrentRow,
                            ciMinValue, ciMaxValue) - 1;

    snNavigator.goTo(ciTargetRow);
}
//------------------------------------------------------------------------------
void
CMain::actEdit_onInsert()
{
    snNavigator.insert();
}
//------------------------------------------------------------------------------
void
CMain::actEdit_onRemove()
{
    qCHECK_DO(snNavigator.view()->currentIndex().row() < 0, return);

    QMessageBox msgBox;

    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(tr("Removing record."));
    msgBox.setInformativeText(tr("Do you want to remove record?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    cint ciRv = msgBox.exec();
    switch (ciRv) {
        case QMessageBox::Yes:
            snNavigator.remove();
            break;
        case QMessageBox::Cancel:
        default:
            break;
    }
}
//------------------------------------------------------------------------------
void
CMain::actEdit_onEdit()
{
    qCHECK_DO(snNavigator.view()->currentIndex().row() < 0, return);

    ui.tabInfo->setCurrentWidget(ui.tabInfoDetail);
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   group "Find"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::actFind_onSearch()
{

}
//------------------------------------------------------------------------------
void
CMain::actFind_onTextClear()
{
    _cboFindText->lineEdit()->clear();
    _cboFindText->setFocus();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "View"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::actView_onMainToolbar()
{
    cbool bIsChecked = ui.actView_MainToolbar->isChecked();

    ui.tbMain->setVisible(bIsChecked);
}
//------------------------------------------------------------------------------
void
CMain::actView_onQuickFindToolbar()
{
    cbool bIsChecked = ui.actView_QuickFindToolbar->isChecked();

    ui.tbQuickFind->setVisible(bIsChecked);
}
//------------------------------------------------------------------------------
void
CMain::actView_onColumns()
{
    CColumns dlgColumns(this, _tmModel);

    (int)dlgColumns.exec();
}
//------------------------------------------------------------------------------
void
CMain::actView_onAlbum()
{
    qCHECK_DO(snNavigator.view()->currentIndex().row() < 0, return);

    qPTR_DELETE(wndAlbum);

    wndAlbum = new CAlbum(this, _tmModel, &snNavigator);
    wndAlbum->show();
}
//------------------------------------------------------------------------------
void
CMain::actView_onStatusbar()
{
    cbool bIsChecked = ui.actView_Statusbar->isChecked();

    ui.sbInfo->setVisible(bIsChecked);
}
//------------------------------------------------------------------------------
void
CMain::actView_onLanguageEn()
{
    (bool)CApplication::removeTranslator(_trTranslator);
    _sTranslatorLang.clear();
}
//------------------------------------------------------------------------------
void
CMain::actView_onLanguageRu()
{
    bool bRv = _trTranslator->load(LANGS_FILE_NAME_RU, CApplication::langsDirPath());
    qTEST(bRv);
    _sTranslatorLang = LANGS_FILE_NAME_RU;

    (bool)CApplication::installTranslator(_trTranslator);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "Options"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::actOptions_onSettings()
{
    CSettings dlgSettings(this);

    (int)dlgSettings.exec();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "Help"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::actHelp_onFaq()
{

}
//------------------------------------------------------------------------------
void
CMain::actHelp_onAbout()
{
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
CMain::onQuickFind(
    cQString &a_arg
)
{
    // get DB field by caption
    QString dbField;

    for (int i = 0; i < _tmModel->columnCount(); ++ i) {
        if (_cboDbFields->currentText() ==
            qApp->translate("CConfig", CConfig::dbRecords[i].caption)
        ) {
            dbField = CConfig::dbRecords[i].field;
            break;
        }
    }
    qTEST(!dbField.isEmpty());

    // filter
    CUtils::db_fields_t dbFields;
    dbFields.push_back( QPair<QString, QString>(dbField, a_arg) );

    CUtils::dbFilter(_tmModel, DB_T_PERSON, dbFields, "", "", "");
}
//------------------------------------------------------------------------------
void
CMain::cboDbFields_onCurrentTextChanged(
    cQString &a_arg
)
{
    Q_UNUSED(a_arg);

    // set focus
    {
        _cboFindText->setFocus();
        _cboFindText->lineEdit()->selectAll();
    }

    Q_EMIT _cboFindText->currentTextChanged( _cboFindText->currentText() );
}
//------------------------------------------------------------------------------
void
CMain::onAlbum()
{
    qPTR_DELETE(wndAlbum);

    wndAlbum = new CAlbum(this, _tmModel, &snNavigator);
    wndAlbum->show();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private slots
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CMain::_detailView_resetAll()
{
    // ensure for reset
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Reset data.");
        msgBox.setInformativeText("Do you want to reset data?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);

        cint ciRv = msgBox.exec();
        switch (ciRv) {
            case QMessageBox::Yes:
                // yes, reset
                break;
            default:
                return;
                break;
        }
    }

    // reset data
    {
        Q_FOREACH (QWidget *key, _hsDbItems.keys()) {
            QWidget *widget = key;
            widget->setFocus();

            QComboBox *comboBox = dynamic_cast<QComboBox *>( widget );
            if (NULL != comboBox) {
                comboBox->lineEdit()->clear();
                continue;
            }

            QPlainTextEdit *textEdit = dynamic_cast<QPlainTextEdit *>( widget );
            if (NULL != textEdit) {
                textEdit->clear();
                continue;
            }

            QDateTimeEdit *dateTimeEdit = dynamic_cast<QDateTimeEdit *>( widget );
            if (NULL != dateTimeEdit) {
                dateTimeEdit->setDate(QDate(2000, 1, 1));
                continue;
            }

            QLabel *label = dynamic_cast<QLabel *>( widget );
            if (NULL != label) {
                label->clear();
                continue;
            }

            qTEST(false);
        }
    }
}
//------------------------------------------------------------------------------
void
CMain::tabInfo_onCurrentChanged(
    int index
)
{
    if (index == 1) {
        // set default control
        ui.cboNick->setFocus();
        ui.cboNick->lineEdit()->selectAll();
    }
}
//------------------------------------------------------------------------------
void
CMain::twGroups_onCurrentItemChanged(
    QTreeWidgetItem *a_current,
    QTreeWidgetItem *a_previous
)
{
    Q_UNUSED(a_current);
    Q_UNUSED(a_previous);

    cint index = ui.twGroups->currentIndex().row();

    ui.tabwGroupsDetail->setCurrentIndex(index);
}
//------------------------------------------------------------------------------
