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
        _m_dmMapper->setItemDelegate(new CDelegateDbImage(_m_dmMapper, _m_tmModel->fieldIndex(CONFIG_DB_F_PHOTO_1), NULL));
        _m_dmMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

        _m_dmMapper->addMapping(m_Ui.cboName->lineEdit(), _m_tmModel->fieldIndex(CONFIG_DB_F_MAIN_NAME));
        _m_dmMapper->addMapping(m_Ui.cboAge->lineEdit(),  _m_tmModel->fieldIndex(CONFIG_DB_F_MAIN_AGE));
        _m_dmMapper->addMapping(m_Ui.lblPhoto,            _m_tmModel->fieldIndex(CONFIG_DB_F_PHOTO_1));
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
                QByteArray baPhoto   = _m_tmModel->record(_m_ciCurrentRow).value(CONFIG_DB_F_PHOTO_1).toByteArray();

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
    m_Ui.cboName->lineEdit()->clear();
    m_Ui.cboAge->lineEdit()->clear();
    m_Ui.lblPhoto->clear();
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

