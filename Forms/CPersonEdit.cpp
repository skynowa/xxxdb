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
    _m_dmMapper    (NULL),
    _m_ciCurrentRow(a_currentRow)
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
    delete _m_dmMapper; _m_dmMapper = NULL;
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
        _m_dmMapper->setItemDelegate(new CDelegateDbImage(_m_dmMapper, _m_tmModel->fieldIndex(CONFIG_DB_F_MAIN_PHOTO_1), NULL));
        _m_dmMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

        // DB controls to QMap
        {
            // Main
            _m_mapDbControls[CONFIG_DB_F_MAIN_NICK]              = m_Ui.cboNick->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MAIN_SURNAME]           = m_Ui.cboSurname->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MAIN_NAME]              = m_Ui.cboName->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MAIN_SECONDNAME]        = m_Ui.cboSecondName->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MAIN_AGE]               = m_Ui.cboAge->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MAIN_HEIGHT]            = m_Ui.cboHeight->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MAIN_WEIGHT]            = m_Ui.cboWeight->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MAIN_HAIRLENGTH]        = m_Ui.cboHairLength->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MAIN_HAIRCOLOR]         = m_Ui.cboHairColor->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MAIN_APPEARANCE]        = m_Ui.cboAppearance->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MAIN_AGREEMENT]         = m_Ui.cboAgreement->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MAIN_PHOTO_1]           = m_Ui.lblPhoto;

            // Phones
            _m_mapDbControls[CONFIG_DB_F_PHONES_MOBILE1]         = m_Ui.cboMobile1->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_PHONES_MOBILE2]         = m_Ui.cboMobile2->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_PHONES_MOBILE3]         = m_Ui.cboMobile3->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_PHONES_PHONEHOME]       = m_Ui.cboPhoneHome->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_PHONES_PHONEJOB]        = m_Ui.cboPhoneJob->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_PHONES_PHONEADDITIONAL] = m_Ui.tedtPhoneAdditional;

            // Address
            _m_mapDbControls[CONFIG_DB_F_ADDRESS_COUNTRY]        = m_Ui.cboCountry->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_ADDRESS_CODE]           = m_Ui.cboCode->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_ADDRESS_CITY]           = m_Ui.cboCity->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_ADDRESS_DISTRICT]       = m_Ui.cboDistrict->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_ADDRESS_STREET]         = m_Ui.cboStreet->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_ADDRESS_HOUSE]          = m_Ui.cboHouse->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_ADDRESS_PORCH]          = m_Ui.cboPorch->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_ADDRESS_FLOOR]          = m_Ui.cboFloor->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_ADDRESS_APARTMENT]      = m_Ui.cboApartment->lineEdit();

            // E-mail
            _m_mapDbControls[CONFIG_DB_F_EMAIL_EMAIL]            = m_Ui.tedtEmail;

            // Web
            _m_mapDbControls[CONFIG_DB_F_WEB_WEB]                = m_Ui.tedtWeb;

            // Messengers
            _m_mapDbControls[CONFIG_DB_F_MESSENGERS_ICQ]         = m_Ui.cboIcq->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_MESSENGERS_SKYPE]       = m_Ui.cboSkype->lineEdit();

            // Job
            _m_mapDbControls[CONFIG_DB_F_JOB_PROFESSION]         = m_Ui.cboProfession->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_JOB_ADDRESS]            = m_Ui.cboAddress->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_JOB_SALARY]             = m_Ui.cboSalary->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_JOB_COMPANY]            = m_Ui.cboCompany->lineEdit();

            // Dates
            _m_mapDbControls[CONFIG_DB_F_DATES_BIRTHDAY]         = m_Ui.cboBirthday->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_DATES_BIRTHDAYFATHER]   = m_Ui.cboBirthdayFather->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_DATES_BIRTHDAYMOTHER]   = m_Ui.cboBirthdayMother->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_DATES_DAYDATING]        = m_Ui.cboDayDating->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_DATES_DAYFIRSTKISS]     = m_Ui.cboDayFirstKiss->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_DATES_DAYFIRSTSEX]      = m_Ui.cboDayFirstSex->lineEdit();

            // Interests
            _m_mapDbControls[CONFIG_DB_F_INTERESTS_HOBBY]        = m_Ui.cboHobby->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_INTERESTS_SPORTS]       = m_Ui.cboSports->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_INTERESTS_SMOKING]      = m_Ui.cboSmoking->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_INTERESTS_ALCOHOL]      = m_Ui.cboAlcohol->lineEdit();
            _m_mapDbControls[CONFIG_DB_F_INTERESTS_DRUGS]        = m_Ui.cboDrugs->lineEdit();

            // Periods


            // Etc
            _m_mapDbControls[CONFIG_DB_F_ETC_DATECREATION]       = m_Ui.dtDateCreation;
            _m_mapDbControls[CONFIG_DB_F_ETC_DATELASTCHANGE]     = m_Ui.dtDateLastChange;

            // Note
            _m_mapDbControls[CONFIG_DB_F_NOTE_NOTES]             = m_Ui.tedtNotes;
        }

        // map DB controls
        {
            QMap<QString, QWidget *>::Iterator it;

            for (it = _m_mapDbControls.begin(); it != _m_mapDbControls.end(); ++ it) {
                _m_dmMapper->addMapping(it.value(), _m_tmModel->fieldIndex(it.key()));
            }
        }

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
                QByteArray baPhoto;

                // file to buffer
                {
                    const QString csFilePath = fdlgDialog.selectedFiles().first();

                    if (true == CONFIG_IMAGE_IS_CONVERT) {
                        CUtils::imageConvert(csFilePath, &baPhoto);
                    } else {
                        QFile file(csFilePath);

                        bool bRv = file.open(QIODevice::ReadOnly);
                        Q_ASSERT(true == bRv);

                        baPhoto = file.readAll();
                    }

                    Q_ASSERT(0 < baPhoto.size());
                }

                // lblPhoto
                {
                    if (0 >= baPhoto.size()) {
                        m_Ui.lblPhoto->setText(tr(CONFIG_TEXT_NO_PHOTO));
                    } else {
                        QImage imgPhoto;

                        bool bRv = imgPhoto.loadFromData(baPhoto);
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
                QByteArray baPhoto   = _m_tmModel->record(_m_ciCurrentRow).value(CONFIG_DB_F_MAIN_PHOTO_1).toByteArray();

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
    QMap<QString, QWidget *>::Iterator it;

    for (it = _m_mapDbControls.begin(); it != _m_mapDbControls.end(); ++ it) {
        it.value()->clear();
    }
#endif
}
//---------------------------------------------------------------------------
void
CPersonEdit::_saveAll() {
    bool bRv = _m_dmMapper->submit();
    Q_ASSERT(true == bRv);

    // set current index
    {
        _m_dmMapper->setCurrentIndex(_m_ciCurrentRow);
    }

    // set current index
    {
        CMain *parent = static_cast<CMain *>( this->parent() );
        Q_ASSERT(NULL != parent);

        parent->m_Ui.tabvInfo->selectRow(_m_ciCurrentRow);
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

