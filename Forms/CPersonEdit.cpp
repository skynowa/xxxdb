/**
 * \file   CPersonEdit.h
 * \brief  edit person data
 */


#include "CPersonEdit.h"

#include "../QtLib/CUtils.h"
#include "../Classes/CDelegateDbImage.h"


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CPersonEdit::CPersonEdit(
    QWidget        *a_parent,
    QSqlTableModel *a_tableModel,
    const int      &a_currentRow
) :
    QDialog        (a_parent),
    _m_ltwGroups   (),
    _m_tmModel     (a_tableModel),
    _m_hsDbControls(),
    _m_dmMapper    (NULL),
    _m_ciCurrentRow(a_currentRow),
    _m_baPhoto     ()
{
    // _m_ltwGroups - n/a
    Q_ASSERT(NULL != _m_tmModel);
    Q_ASSERT(NULL == _m_dmMapper);
    Q_ASSERT(- 1  <  _m_ciCurrentRow);

    _construct();
}
//---------------------------------------------------------------------------
/* virtual */
CPersonEdit::~CPersonEdit() {
    _destruct();
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPersonEdit::_construct() {
    _initMain();
}
//---------------------------------------------------------------------------
void
CPersonEdit::_destruct() {
    qDeleteAll(_m_ltwGroups);
}
//---------------------------------------------------------------------------
void
CPersonEdit::_initMain() {
    m_Ui.setupUi(this);

    // maps ui controls into DB fields
    {
        _m_dmMapper = new QDataWidgetMapper(this);
        _m_dmMapper->setModel(_m_tmModel);
        _m_dmMapper->setItemDelegate(new CDelegateDbImage(_m_dmMapper, _m_tmModel->fieldIndex(CONFIG_DB_F_PHOTOS_1),
                                                          CONFIG_PHOTO_SIZE, NULL));
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

            for (cit = _m_hsDbControls.begin(); cit != _m_hsDbControls.end(); ++ cit) {
                _m_dmMapper->addMapping(cit.key(), _m_tmModel->fieldIndex(cit.value()));
            }
        }

        // activate current record
        _m_dmMapper->setCurrentIndex(_m_ciCurrentRow);
    }

    // signals
    {
        connect(m_Ui.tbtnPhotoChange,  SIGNAL( clicked() ),
                this,                  SLOT  ( slot_tbtnPhotoChange_OnClicked() ));
        connect(m_Ui.tbtnPhotoDelete,  SIGNAL( clicked() ),
                this,                  SLOT  ( slot_tbtnPhotoDelete_OnClicked() ));
        connect(m_Ui.tbtnPhotoSaveAs,  SIGNAL( clicked() ),
                this,                  SLOT  ( slot_tbtnPhotoSaveAs_OnClicked() ));

        connect(m_Ui.bbxButtons,       SIGNAL( clicked(QAbstractButton *) ),
                this,                  SLOT  ( slot_bbxButtons_OnClicked(QAbstractButton *) ));
        connect(m_Ui.twGroups,         SIGNAL( clicked(const QModelIndex &) ),
                this,                  SLOT  ( slot_twGroups_OnActivated(const QModelIndex &) ));
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private slots
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPersonEdit::slot_tbtnPhotoChange_OnClicked() {
    QFileDialog fdlgDialog(this);

    fdlgDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fdlgDialog.setFileMode(QFileDialog::AnyFile);

    QStringList slFilters;

    slFilters << "Image files (" CONFIG_IMAGE_FORMATS ")";
    slFilters << "All   files (*)";

    fdlgDialog.setNameFilters(slFilters);
    // fdlgDialog.setDirectory();

    QDialog::DialogCode dcRes = static_cast<QDialog::DialogCode>( fdlgDialog.exec() );
    switch (dcRes) {
        case QDialog::Rejected: {
                // n/a
            }
            break;

        case QDialog::Accepted: {
                _m_baPhoto.clear();

                // file to buffer
                {
                    const QString csFilePath = fdlgDialog.selectedFiles().first();

                    if (true == CONFIG_IMAGE_IS_CONVERT) {
                        CUtils::imageConvert(csFilePath, &_m_baPhoto);
                    } else {
                        QFile file(csFilePath);

                        bool bRv = file.open(QIODevice::ReadOnly);
                        Q_ASSERT(true == bRv);

                        _m_baPhoto = file.readAll();
                    }

                    Q_ASSERT(0 < _m_baPhoto.size());
                }

                // lblPhoto
                {
                    if (0 >= _m_baPhoto.size()) {
                        m_Ui.lblPhoto->setText(tr(CONFIG_TEXT_NO_PHOTO));
                    } else {
                        QImage imgPhoto;

                        bool bRv = imgPhoto.loadFromData(_m_baPhoto);
                        Q_ASSERT(true == bRv);

                        QImage  imgPhotoScaled = imgPhoto.scaled(QSize(CONFIG_PHOTO_WIDTH, CONFIG_PHOTO_HEIGHT), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                        QPixmap pixPixmap      = QPixmap::fromImage(imgPhotoScaled);

                        m_Ui.lblPhoto->setPixmap(pixPixmap);
                    }
                }

            }
            break;

        default: {
                Q_ASSERT(false);
            }
            break;
    }
}
//---------------------------------------------------------------------------
void
CPersonEdit::slot_tbtnPhotoDelete_OnClicked() {
    m_Ui.lblPhoto->clear();
}
//---------------------------------------------------------------------------
void
CPersonEdit::slot_tbtnPhotoSaveAs_OnClicked() {
    QFileDialog fdlgDialog(this);

    fdlgDialog.setAcceptMode(QFileDialog::AcceptSave);
    fdlgDialog.setFileMode(QFileDialog::AnyFile);
    // fdlgDialog.selectFile( QFileInfo(psbtnParent->filePath()).baseName() );
    // fdlgDialog.setDefaultSuffix(CONFIG_SHORTCUT_EXT);

    QDialog::DialogCode dcRes = static_cast<QDialog::DialogCode>( fdlgDialog.exec() );
    switch (dcRes) {
        case QDialog::Rejected: {
                // n/a;
            }
            break;

        case QDialog::Accepted: {
                QString    sFilePath = fdlgDialog.selectedFiles().first();
                QByteArray baPhoto   = _m_tmModel->record(_m_ciCurrentRow).value(CONFIG_DB_F_PHOTOS_1).toByteArray();

                QFile  file(sFilePath);
                bool bRv = file.open(QIODevice::WriteOnly);
                Q_ASSERT(true == bRv);

                QDataStream stream(&file);
                int iRv = stream.writeRawData(baPhoto.constData(), baPhoto.size());
                Q_ASSERT(0 < iRv);
            }
            break;

        default: {
                Q_ASSERT(false);
            }
            break;
    }
}
//---------------------------------------------------------------------------
void
CPersonEdit::slot_bbxButtons_OnClicked(
    QAbstractButton *a_button
)
{
    QDialogButtonBox::StandardButton sbType = m_Ui.bbxButtons->standardButton(a_button);
    switch (sbType) {
        case QDialogButtonBox::Reset: {
                _resetAll();
            }
            break;

        case QDialogButtonBox::Ok: {
                _saveAll();
                close();
            }
            break;

        case QDialogButtonBox::Cancel: {
                close();
            }
            break;

        case QDialogButtonBox::Apply: {
                _saveAll();
            }
            break;

        default: {
                Q_ASSERT(false);
            }
            break;
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private slots
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPersonEdit::_resetAll() {
#if 0
    QHash<QString, QWidget *>::Iterator it;

    for (it = _m_hsDbControls.begin(); it != _m_hsDbControls.end(); ++ it) {
        it.value()->clear();
    }
#endif
}
//---------------------------------------------------------------------------
void
CPersonEdit::_saveAll() {
    bool bRv = _m_dmMapper->submit();
    if (false == bRv) {
        qDebug() << __FUNCTION__ << ": fail, " << _m_tmModel->lastError().text();
    }

    // save photo to DB
    {
        if (0 < _m_baPhoto.size()) {
            QSqlRecord srRecord = _m_tmModel->record(_m_ciCurrentRow);
            srRecord.setValue(CONFIG_DB_F_PHOTOS_1, _m_baPhoto);

            _m_tmModel->setRecord(_m_ciCurrentRow, srRecord);
            bRv = _m_tmModel->submitAll();
            Q_ASSERT(true == bRv);

            _m_baPhoto.clear();
        }
    }

    // set current index
    {
        _m_dmMapper->setCurrentIndex(_m_ciCurrentRow);
    }
}
//---------------------------------------------------------------------------
void
CPersonEdit::slot_twGroups_OnActivated(
    const QModelIndex &a_index
)
{
    m_Ui.tabwGroupsDetail->setCurrentIndex( a_index.row() );
}
//---------------------------------------------------------------------------

