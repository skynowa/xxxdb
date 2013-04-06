/**
 * \file   CEditor.h
 * \brief  edit person data
 */


#include "CEditor.h"

#include "../QtLib/CUtils.h"
#include "../Classes/CIni.h"
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
    QDialog         (a_parent),
    wndAlbum        (NULL),
    _ciDbRecordIndex(a_sqlNavigator->view()->currentIndex().row()),
    _iniApp          (NULL),
    _tmModel        (a_tableModel),
    _snNavigator    (a_sqlNavigator),
    _hsDbItems      (),
    _dmText         (NULL),
    _dbImageLabel   ()
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(NULL != a_tableModel);
    Q_ASSERT(NULL != a_sqlNavigator);
    // _ciDbRecordIndex - n/a

    _construct();

    _iniApp = new CIni(NULL, this, NULL);
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
CEditor::_construct()
{
    _initMain();
}
//------------------------------------------------------------------------------
void
CEditor::_destruct()
{
#if 0
    // update DB_F_ETC_DATECREATION, DB_F_ETC_DATELASTCHANGE
    {
        QSqlRecord record = _tmModel->record(_ciDbRecordIndex);

        if (record.value(DB_F_ETC_DATECREATION).isNull()) {
            record.setValue(DB_F_ETC_DATECREATION, QDateTime::currentDateTime());
        }
        record.setValue(DB_F_ETC_DATELASTCHANGE, QDateTime::currentDateTime());

        _tmModel->setRecord(_ciDbRecordIndex, record);
    }
#endif

    qPTR_DELETE(_iniApp);
}
//------------------------------------------------------------------------------
void
CEditor::_initMain()
{
    ui.setupUi(this);

    // maps ui controls into DB fields
    {
        // DB items to QHash
        {
            Q_ASSERT(_hsDbItems.isEmpty());

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

            // TODO: Photos
            // _hsDbItems.insert(ui.lblPhoto,      DB_F_PHOTOS_1);
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

            _dmText->setCurrentIndex(_ciDbRecordIndex);
        }

        // set default control
        ui.cboNick->setFocus();
        ui.cboNick->lineEdit()->selectAll();
    }

    // _dbImageLabel
    {
        // TODO: 0
        _dbImageLabel = new CDbImageLabel(this, _tmModel, DB_F_PHOTOS_1,
                                          0, _ciDbRecordIndex,
                                          ui.lblPhoto, PHOTO_SIZE,
                                          ui.lblPhotoInfo);
    }

    // signals
    {
        connect(ui.tbtnPhotoAlbum, &QToolButton::clicked,
                this,              &CEditor::onAlbum);
        connect(ui.bbxButtons,     &QDialogButtonBox::clicked,
                this,              &CEditor::bbxButtons_onClicked);
        connect(ui.twGroups,       &QTreeWidget::currentItemChanged,
                this,              &CEditor::twGroups_onCurrentItemChanged);
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private slots
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CEditor::onAlbum()
{
    qPTR_DELETE(wndAlbum);

    wndAlbum = new CAlbum(this, _tmModel, _snNavigator);
    wndAlbum->show();
}
//------------------------------------------------------------------------------
void
CEditor::bbxButtons_onClicked(
    QAbstractButton *a_button
)
{
    QDialogButtonBox::StandardButton sbRv = ui.bbxButtons->standardButton(a_button);
    switch (sbRv) {
        case QDialogButtonBox::Reset:
            _resetAll();
            break;
        case QDialogButtonBox::Ok:
            _saveAll();
            close();
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
CEditor::_resetAll()
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

            Q_ASSERT(false);
        }
    }
}
//------------------------------------------------------------------------------
void
CEditor::_saveAll()
{
#if 0
    // set current index
    _dmText->setCurrentIndex(_ciDbRecordIndex);
    _dbImageLabel->mapper()->setCurrentIndex(_ciDbRecordIndex);

    // set current index
    _snNavigator->goTo(_ciDbRecordIndex);
#endif
}
//------------------------------------------------------------------------------
void
CEditor::twGroups_onCurrentItemChanged(
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
