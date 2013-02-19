/**
 * \file   CPersonEdit.h
 * \brief  edit person data
 */


#include "CPersonEdit.h"

#include "../QtLib/CUtils.h"
#include "../Classes/CDelegateDbImage.h"
#include "CPhotoAlbum.h"


/******************************************************************************
*   public
*
******************************************************************************/

//-----------------------------------------------------------------------------
CPersonEdit::CPersonEdit(
    QWidget        *a_parent,
    QSqlTableModel *a_tableModel,
    cint           &a_currentRow
) :
    QDialog        (a_parent),
    m_wndPhotoAlbum(NULL),
    _m_tmModel     (a_tableModel),
    _m_hsDbControls(),
    _m_dmMapper    (NULL),
    _m_ciCurrentRow(a_currentRow),
    _m_dbImage     ()
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(NULL != a_tableModel);
    Q_ASSERT(- 1  <  a_currentRow);

    _construct();
}
//-----------------------------------------------------------------------------
/* virtual */
CPersonEdit::~CPersonEdit() {
    _destruct();
}
//-----------------------------------------------------------------------------


/******************************************************************************
*   private
*
******************************************************************************/

//-----------------------------------------------------------------------------
void
CPersonEdit::_construct() {
    _initMain();
}
//-----------------------------------------------------------------------------
void
CPersonEdit::_destruct() {

}
//-----------------------------------------------------------------------------
void
CPersonEdit::_initMain() {
    m_Ui.setupUi(this);

    // maps ui controls into DB fields
    {
        _m_dmMapper = new QDataWidgetMapper(this);
        _m_dmMapper->setModel(_m_tmModel);
        _m_dmMapper->setItemDelegate(new CDelegateDbImage(
                                            _m_dmMapper,
                                            _m_tmModel->fieldIndex(CONFIG_DB_F_PHOTOS_1),
                                            CONFIG_PHOTO_SIZE,
                                            NULL));
        _m_dmMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

        // DB controls to QMap
        {
            // Main
            _m_hsDbControls.insert(m_Ui.cboNick->lineEdit(),       CONFIG_DB_F_MAIN_NICK);
            _m_hsDbControls.insert(m_Ui.cboSurname->lineEdit(),    CONFIG_DB_F_MAIN_SURNAME);
            _m_hsDbControls.insert(m_Ui.cboName->lineEdit(),       CONFIG_DB_F_MAIN_NAME);
            _m_hsDbControls.insert(m_Ui.cboPatronymic->lineEdit(), CONFIG_DB_F_MAIN_PATRONYMIC);
            _m_hsDbControls.insert(m_Ui.cboAge->lineEdit(),        CONFIG_DB_F_MAIN_AGE);
            _m_hsDbControls.insert(m_Ui.cboHeight->lineEdit(),     CONFIG_DB_F_MAIN_HEIGHT);
            _m_hsDbControls.insert(m_Ui.cboWeight->lineEdit(),     CONFIG_DB_F_MAIN_WEIGHT);
            _m_hsDbControls.insert(m_Ui.cboHairLength->lineEdit(), CONFIG_DB_F_MAIN_HAIRLENGTH);
            _m_hsDbControls.insert(m_Ui.cboHairColor->lineEdit(),  CONFIG_DB_F_MAIN_HAIRCOLOR);
            _m_hsDbControls.insert(m_Ui.cboAppearance->lineEdit(), CONFIG_DB_F_MAIN_APPEARANCE);
            _m_hsDbControls.insert(m_Ui.cboAgreement->lineEdit(),  CONFIG_DB_F_MAIN_AGREEMENT);

            // Phones
            _m_hsDbControls.insert(m_Ui.cboMobile1->lineEdit(),    CONFIG_DB_F_PHONES_MOBILE1);
            _m_hsDbControls.insert(m_Ui.cboMobile2->lineEdit(),    CONFIG_DB_F_PHONES_MOBILE2);
            _m_hsDbControls.insert(m_Ui.cboMobile3->lineEdit(),    CONFIG_DB_F_PHONES_MOBILE3);
            _m_hsDbControls.insert(m_Ui.cboPhoneHome->lineEdit(),  CONFIG_DB_F_PHONES_HOME);
            _m_hsDbControls.insert(m_Ui.cboPhoneJob->lineEdit(),   CONFIG_DB_F_PHONES_JOB);
            _m_hsDbControls.insert(m_Ui.tedtPhoneAdditional,       CONFIG_DB_F_PHONES_OTHER);

            // Address
            _m_hsDbControls.insert(m_Ui.cboCountry->lineEdit(),    CONFIG_DB_F_ADDRESS_COUNTRY);
            _m_hsDbControls.insert(m_Ui.cboCode->lineEdit(),       CONFIG_DB_F_ADDRESS_CODE);
            _m_hsDbControls.insert(m_Ui.cboCity->lineEdit(),       CONFIG_DB_F_ADDRESS_CITY);
            _m_hsDbControls.insert(m_Ui.cboDistrict->lineEdit(),   CONFIG_DB_F_ADDRESS_DISTRICT);
            _m_hsDbControls.insert(m_Ui.cboStreet->lineEdit(),     CONFIG_DB_F_ADDRESS_STREET);
            _m_hsDbControls.insert(m_Ui.cboHouse->lineEdit(),      CONFIG_DB_F_ADDRESS_HOUSE);
            _m_hsDbControls.insert(m_Ui.cboPorch->lineEdit(),      CONFIG_DB_F_ADDRESS_PORCH);
            _m_hsDbControls.insert(m_Ui.cboFloor->lineEdit(),      CONFIG_DB_F_ADDRESS_FLOOR);
            _m_hsDbControls.insert(m_Ui.cboApartment->lineEdit(),  CONFIG_DB_F_ADDRESS_APARTMENT);

            // E-mail
            _m_hsDbControls.insert(m_Ui.tedtEmail,                 CONFIG_DB_F_EMAIL_EMAIL);

            // Web
            _m_hsDbControls.insert(m_Ui.tedtWeb,                   CONFIG_DB_F_WEB_WEB);

            // Messengers
            _m_hsDbControls.insert(m_Ui.cboIcq->lineEdit(),        CONFIG_DB_F_MESSENGERS_ICQ);
            _m_hsDbControls.insert(m_Ui.cboSkype->lineEdit(),      CONFIG_DB_F_MESSENGERS_SKYPE);

            // Job
            _m_hsDbControls.insert(m_Ui.cboProfession->lineEdit(), CONFIG_DB_F_JOB_PROFESSION);
            _m_hsDbControls.insert(m_Ui.cboAddress->lineEdit(),    CONFIG_DB_F_JOB_ADDRESS);
            _m_hsDbControls.insert(m_Ui.cboSalary->lineEdit(),     CONFIG_DB_F_JOB_SALARY);
            _m_hsDbControls.insert(m_Ui.cboCompany->lineEdit(),    CONFIG_DB_F_JOB_COMPANY);

            // Dates
            _m_hsDbControls.insert(m_Ui.dtBirthday,                CONFIG_DB_F_DATES_BIRTHDAY);
            _m_hsDbControls.insert(m_Ui.dtBirthdayFather,          CONFIG_DB_F_DATES_BIRTHDAYFATHER);
            _m_hsDbControls.insert(m_Ui.dtBirthdayMother,          CONFIG_DB_F_DATES_BIRTHDAYMOTHER);
            _m_hsDbControls.insert(m_Ui.dtDayDating,               CONFIG_DB_F_DATES_DAYDATING);
            _m_hsDbControls.insert(m_Ui.dtDayFirstKiss,            CONFIG_DB_F_DATES_DAYFIRSTKISS);
            _m_hsDbControls.insert(m_Ui.dtDayFirstSex,             CONFIG_DB_F_DATES_DAYFIRSTSEX);

            // Interests
            _m_hsDbControls.insert(m_Ui.cboHobby->lineEdit(),      CONFIG_DB_F_INTERESTS_HOBBY);
            _m_hsDbControls.insert(m_Ui.cboSports->lineEdit(),     CONFIG_DB_F_INTERESTS_SPORTS);
            _m_hsDbControls.insert(m_Ui.cboSmoking->lineEdit(),    CONFIG_DB_F_INTERESTS_SMOKING);
            _m_hsDbControls.insert(m_Ui.cboAlcohol->lineEdit(),    CONFIG_DB_F_INTERESTS_ALCOHOL);
            _m_hsDbControls.insert(m_Ui.cboDrugs->lineEdit(),      CONFIG_DB_F_INTERESTS_DRUGS);

            // TODO: Periods

            // Etc
            _m_hsDbControls.insert(m_Ui.dtDateCreation,            CONFIG_DB_F_ETC_DATECREATION);
            _m_hsDbControls.insert(m_Ui.dtDateLastChange,          CONFIG_DB_F_ETC_DATELASTCHANGE);

            // Note
            _m_hsDbControls.insert(m_Ui.tedtNotes,                 CONFIG_DB_F_NOTES_NOTES);

            // Photos
            _m_hsDbControls.insert(m_Ui.lblPhoto,                  CONFIG_DB_F_PHOTOS_1);
        }

        // map DB controls
        {
            db_controls_t::ConstIterator cit;

            for (cit  = _m_hsDbControls.begin();
                 cit != _m_hsDbControls.end();
                 ++ cit)
            {
                QWidget *widget  = cit.key();
                cint     section = _m_tmModel->fieldIndex(cit.value());
                _m_dmMapper->addMapping(widget, section);
            }
        }

        // activate current record
        _m_dmMapper->setCurrentIndex(_m_ciCurrentRow);

        // set default control
        m_Ui.cboNick->setFocus();
        m_Ui.cboNick->lineEdit()->selectAll();
    }

    // _m_dbImage
    {
        _m_dbImage = new CDbImage(this, _m_tmModel, CONFIG_DB_F_PHOTOS_1,
                                  _m_ciCurrentRow, m_Ui.lblPhoto);
    }

    // signals
    {
        connect(m_Ui.tbtnPhotoAlbum, SIGNAL( clicked() ),
                this,                SLOT  ( slot_OnPhotoAlbum() ));
        connect(m_Ui.bbxButtons,     SIGNAL( clicked(QAbstractButton *) ),
                this,                SLOT  ( slot_bbxButtons_OnClicked(QAbstractButton *) ));
        connect(m_Ui.twGroups,       SIGNAL( clicked(const QModelIndex &) ),
                this,                SLOT  ( slot_twGroups_OnActivated(const QModelIndex &) ));
    }
}
//-----------------------------------------------------------------------------


/******************************************************************************
*   private slots
*
******************************************************************************/

//-----------------------------------------------------------------------------
void
CPersonEdit::slot_OnPhotoAlbum() {
    delete m_wndPhotoAlbum;
    m_wndPhotoAlbum = NULL;

    m_wndPhotoAlbum = new CPhotoAlbum(this, _m_tmModel, _m_ciCurrentRow);
    m_wndPhotoAlbum->show();
}
//-----------------------------------------------------------------------------
void
CPersonEdit::slot_bbxButtons_OnClicked(
    QAbstractButton *a_button
)
{
    QDialogButtonBox::StandardButton sbType =
            m_Ui.bbxButtons->standardButton(a_button);
    switch (sbType) {
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
//-----------------------------------------------------------------------------


/******************************************************************************
*   private slots
*
******************************************************************************/

//-----------------------------------------------------------------------------
void
CPersonEdit::_resetAll() {
#if 0
    QHash<QString, QWidget *>::Iterator it;

    for (it = _m_hsDbControls.begin(); it != _m_hsDbControls.end(); ++ it) {
        it.value()->clear();
    }
#endif
}
//-----------------------------------------------------------------------------
void
CPersonEdit::_saveAll() {
    // submit data
    {
        bool bRv = _m_dmMapper->submit();
        if (false == bRv) {
            qDebug() << __FUNCTION__ << ": mapper fail, "
                     << _m_tmModel->lastError().text();
        }

        bRv = _m_tmModel->submitAll();
        if (false == bRv) {
            qDebug() << __FUNCTION__ << ": model fail, "
                     << _m_tmModel->lastError().text();
        }
    }

    // set current index
    _m_dmMapper->setCurrentIndex(_m_ciCurrentRow);
}
//-----------------------------------------------------------------------------
void
CPersonEdit::slot_twGroups_OnActivated(
    const QModelIndex &a_index
)
{
    m_Ui.tabwGroupsDetail->setCurrentIndex( a_index.row() );
}
//-----------------------------------------------------------------------------

