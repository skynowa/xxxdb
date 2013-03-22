/**
 * \file   CEditor.h
 * \brief  edit person data
 */


#include "CEditor.h"

#include "../QtLib/CUtils.h"
#include "../Classes/CSettings.h"
#include "../Classes/CDbImageLabel.h"
#include "../Classes/CDelegateDbImage.h"
#include "CAlbum.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CEditor::CEditor(
    QWidget        *a_parent,
    QSqlTableModel *a_tableModel,
    CSqlNavigator  *a_sqlNavigator
) :
    QDialog           (a_parent),
    m_wndAlbum        (NULL),
    _m_stApp          (NULL),
    _m_tmModel        (a_tableModel),
    _m_snSqlNavigator (a_sqlNavigator),
    _m_hsDbItems      (),
    _m_dmText         (NULL),
    _m_dmImage        (NULL),
    _m_ciDbRecordIndex(a_sqlNavigator->view()->currentIndex().row()),
    _m_dbImageLabel   ()
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(NULL != a_tableModel);
    Q_ASSERT(NULL != a_sqlNavigator);
    Q_ASSERT(- 1  <  _m_ciDbRecordIndex);

    _construct();

    _m_stApp = new CSettings(NULL, this, NULL);
}
//------------------------------------------------------------------------------
/* virtual */
CEditor::~CEditor() {

}
//------------------------------------------------------------------------------

/*******************************************************************************
*   protected
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* virtual */
void
CEditor::closeEvent(
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
CEditor::_construct() {
    _initMain();
}
//------------------------------------------------------------------------------
void
CEditor::_destruct() {
    qPTR_DELETE(_m_stApp);
}
//------------------------------------------------------------------------------
void
CEditor::_initMain() {
    m_Ui.setupUi(this);

    // main
    {
        setWindowTitle(APP_PERSON_EDIT_TITLE);
    }

    // maps ui controls into DB fields
    {
        // DB items to QHash
        {
            // Main
            _m_hsDbItems.insert(m_Ui.cboNick,          DB_F_MAIN_NICK);
            _m_hsDbItems.insert(m_Ui.cboSurname,       DB_F_MAIN_SURNAME);
            _m_hsDbItems.insert(m_Ui.cboName,          DB_F_MAIN_NAME);
            _m_hsDbItems.insert(m_Ui.cboPatronymic,    DB_F_MAIN_PATRONYMIC);
            _m_hsDbItems.insert(m_Ui.cboAge,           DB_F_MAIN_AGE);
            _m_hsDbItems.insert(m_Ui.cboHeight,        DB_F_MAIN_HEIGHT);
            _m_hsDbItems.insert(m_Ui.cboWeight,        DB_F_MAIN_WEIGHT);
            _m_hsDbItems.insert(m_Ui.cboHairLength,    DB_F_MAIN_HAIRLENGTH);
            _m_hsDbItems.insert(m_Ui.cboHairColor,     DB_F_MAIN_HAIRCOLOR);
            _m_hsDbItems.insert(m_Ui.cboAppearance,    DB_F_MAIN_APPEARANCE);
            _m_hsDbItems.insert(m_Ui.cboAgreement,     DB_F_MAIN_STATUS);

            // Phones
            _m_hsDbItems.insert(m_Ui.cboMobile1,       DB_F_PHONES_MOBILE1);
            _m_hsDbItems.insert(m_Ui.cboMobile2,       DB_F_PHONES_MOBILE2);
            _m_hsDbItems.insert(m_Ui.cboMobile3,       DB_F_PHONES_MOBILE3);
            _m_hsDbItems.insert(m_Ui.cboPhoneHome,     DB_F_PHONES_HOME);
            _m_hsDbItems.insert(m_Ui.cboPhoneJob,      DB_F_PHONES_JOB);
            _m_hsDbItems.insert(m_Ui.tedtPhoneOther,   DB_F_PHONES_OTHER);

            // Address
            _m_hsDbItems.insert(m_Ui.cboCountry,       DB_F_ADDRESS_COUNTRY);
            _m_hsDbItems.insert(m_Ui.cboCode,          DB_F_ADDRESS_CODE);
            _m_hsDbItems.insert(m_Ui.cboCity,          DB_F_ADDRESS_CITY);
            _m_hsDbItems.insert(m_Ui.cboDistrict,      DB_F_ADDRESS_DISTRICT);
            _m_hsDbItems.insert(m_Ui.cboStreet,        DB_F_ADDRESS_STREET);
            _m_hsDbItems.insert(m_Ui.cboHouse,         DB_F_ADDRESS_HOUSE);
            _m_hsDbItems.insert(m_Ui.cboPorch,         DB_F_ADDRESS_PORCH);
            _m_hsDbItems.insert(m_Ui.cboFloor,         DB_F_ADDRESS_FLOOR);
            _m_hsDbItems.insert(m_Ui.cboApartment,     DB_F_ADDRESS_APARTMENT);

            // E-mail
            _m_hsDbItems.insert(m_Ui.tedtEmail,        DB_F_EMAIL_EMAIL);

            // Web
            _m_hsDbItems.insert(m_Ui.tedtWeb,          DB_F_WEB_WEB);

            // Messengers
            _m_hsDbItems.insert(m_Ui.cboIcq,           DB_F_MESSENGERS_ICQ);
            _m_hsDbItems.insert(m_Ui.cboSkype,         DB_F_MESSENGERS_SKYPE);

            // Job
            _m_hsDbItems.insert(m_Ui.cboProfession,    DB_F_JOB_PROFESSION);
            _m_hsDbItems.insert(m_Ui.cboAddress,       DB_F_JOB_ADDRESS);
            _m_hsDbItems.insert(m_Ui.cboSalary,        DB_F_JOB_SALARY);
            _m_hsDbItems.insert(m_Ui.cboCompany,       DB_F_JOB_COMPANY);

            // Dates
            _m_hsDbItems.insert(m_Ui.dtBirthday,       DB_F_DATES_BIRTHDAY);
            _m_hsDbItems.insert(m_Ui.dtBirthdayFather, DB_F_DATES_BIRTHDAYFATHER);
            _m_hsDbItems.insert(m_Ui.dtBirthdayMother, DB_F_DATES_BIRTHDAYMOTHER);
            _m_hsDbItems.insert(m_Ui.dtDayDating,      DB_F_DATES_DAYDATING);
            _m_hsDbItems.insert(m_Ui.dtDayFirstKiss,   DB_F_DATES_DAYFIRSTKISS);
            _m_hsDbItems.insert(m_Ui.dtDayFirstSex,    DB_F_DATES_DAYFIRSTSEX);

            // Interests
            _m_hsDbItems.insert(m_Ui.cboHobby,         DB_F_INTERESTS_HOBBY);
            _m_hsDbItems.insert(m_Ui.cboSports,        DB_F_INTERESTS_SPORTS);
            _m_hsDbItems.insert(m_Ui.cboSmoking,       DB_F_INTERESTS_SMOKING);
            _m_hsDbItems.insert(m_Ui.cboAlcohol,       DB_F_INTERESTS_ALCOHOL);
            _m_hsDbItems.insert(m_Ui.cboDrugs,         DB_F_INTERESTS_DRUGS);

            // TODO: Periods

            // Etc
            _m_hsDbItems.insert(m_Ui.dtDateCreation,   DB_F_ETC_DATECREATION);
            _m_hsDbItems.insert(m_Ui.dtDateLastChange, DB_F_ETC_DATELASTCHANGE);

            // Note
            _m_hsDbItems.insert(m_Ui.tedtNotes,        DB_F_NOTES_NOTES);

            // TODO: Photos
            // _m_hsDbItems.insert(m_Ui.lblPhoto,      DB_F_PHOTOS_1);
        }

        // map DB items
        {
            // _m_dmText
            _m_dmText = new QDataWidgetMapper(this);
            _m_dmText->setModel(_m_tmModel);
            _m_dmText->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

            // map
            foreach (QWidget *key, _m_hsDbItems.keys()) {
                QWidget *widget  = key;
                cint     section = _m_tmModel->fieldIndex(_m_hsDbItems.value(key));

                _m_dmText->addMapping(widget, section);
            }

            _m_dmText->setCurrentIndex(_m_ciDbRecordIndex);
        }

        // _m_dmImage
        {
            _m_dmImage = new QDataWidgetMapper(this);
            _m_dmImage->setModel(_m_tmModel);
            _m_dmImage->setItemDelegate(new CDelegateDbImage(
                                                _m_dmImage,
                                                _m_tmModel->fieldIndex(DB_F_PHOTOS_1),
                                                PHOTO_SIZE,
                                                NULL));
            _m_dmImage->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
            _m_dmImage->addMapping(m_Ui.lblPhoto, _m_tmModel->fieldIndex(DB_F_PHOTOS_1));
            _m_dmImage->setCurrentIndex(_m_ciDbRecordIndex);
        }

        // set default control
        m_Ui.cboNick->setFocus();
        m_Ui.cboNick->lineEdit()->selectAll();
    }

    // _m_dbImage
    {
        // TODO: 0
        _m_dbImageLabel = new CDbImageLabel(this, _m_tmModel, DB_F_PHOTOS_1,
                                            0, _m_ciDbRecordIndex,
                                            m_Ui.lblPhoto, PHOTO_SIZE);
    }

    // signals
    {
        connect(m_Ui.tbtnPhotoAlbum, &QToolButton::clicked,
                this,                &CEditor::slot_OnAlbum);
        connect(m_Ui.bbxButtons,     &QDialogButtonBox::clicked,
                this,                &CEditor::slot_bbxButtons_OnClicked);
        connect(m_Ui.twGroups,       &QTreeWidget::clicked,
                this,                &CEditor::slot_twGroups_OnActivated);
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private slots
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CEditor::slot_OnAlbum() {
    delete m_wndAlbum;
    m_wndAlbum = NULL;

    m_wndAlbum = new CAlbum(this, _m_tmModel, _m_snSqlNavigator);
    m_wndAlbum->show();
}
//------------------------------------------------------------------------------
void
CEditor::slot_bbxButtons_OnClicked(
    QAbstractButton *a_button
)
{
    QDialogButtonBox::StandardButton sbRv = m_Ui.bbxButtons->standardButton(a_button);
    switch (sbRv) {
        case QDialogButtonBox::Reset:
            _resetAll();
            break;
        case QDialogButtonBox::Ok:
            _saveAll();
            close();
            break;
        case QDialogButtonBox::Cancel:
            close();
            break;
        case QDialogButtonBox::Apply:
            _saveAll();
            break;
        default:
            Q_ASSERT(false);
            break;
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private slots
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CEditor::_resetAll() {
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
        db_items_t::Iterator it;

        for (it = _m_hsDbItems.begin(); it != _m_hsDbItems.end(); ++ it) {
            QWidget *widget = it.key();

            QLineEdit *lineEdit = dynamic_cast<QLineEdit *>( widget );
            if (NULL != lineEdit) {
                lineEdit->clear();
                continue;
            }

            QTextEdit *textEdit = dynamic_cast<QTextEdit *>( widget );
            if (NULL != textEdit) {
                textEdit->clear();
                continue;
            }

            QDateTimeEdit *dateTimeEdit = dynamic_cast<QDateTimeEdit *>( widget );
            if (NULL != dateTimeEdit) {
                dateTimeEdit->clear();
                continue;
            }

            QLabel *label = dynamic_cast<QLabel *>( widget );
            if (NULL != label) {
                label->clear();
                continue;
            }

            Q_ASSERT(false);
        }
    }
}
//------------------------------------------------------------------------------
void
CEditor::_saveAll() {
    // set current index
    _m_dmText->setCurrentIndex(_m_ciDbRecordIndex);
    _m_dmImage->setCurrentIndex(_m_ciDbRecordIndex);

    // set current index
    _m_snSqlNavigator->goTo(_m_ciDbRecordIndex);
}
//------------------------------------------------------------------------------
void
CEditor::slot_twGroups_OnActivated(
    const QModelIndex &a_index
)
{
    m_Ui.tabwGroupsDetail->setCurrentIndex( a_index.row() );
}
//------------------------------------------------------------------------------

