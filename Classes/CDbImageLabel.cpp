/**
 * \file   CDbImageLabel.cpp
 * \brief  DB image label
 */


#include "CDbImageLabel.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CDbImageLabel::CDbImageLabel(QWidget        *a_parent,       ///< parent QWidget
    QSqlTableModel *a_tableModel,   ///< QSqlTableModel
    cQString       &a_dbFieldName,  ///< DB field name
    cint           &a_recordIndex,  ///< DB record index
    QLabel         *a_label         ///< QLabel for display image
) :
    QObject         (a_parent),
    _m_wdParent     (a_parent),
    _m_tmModel      (a_tableModel),
    _m_csDbFieldName(a_dbFieldName),
    _m_ciRecordIndex(a_recordIndex),
    _m_lblLabel     (a_label),
    _m_baBuffer     ()
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(NULL != a_tableModel);
    Q_ASSERT(!a_dbFieldName.isEmpty());
    Q_ASSERT(- 1 < a_recordIndex);
    Q_ASSERT(NULL != a_label);
}
//------------------------------------------------------------------------------
CDbImageLabel::~CDbImageLabel() {

}
//------------------------------------------------------------------------------


/*******************************************************************************
*   public, data
*
*******************************************************************************/

//------------------------------------------------------------------------------
const QString &
CDbImageLabel::dbFieldName() const {
    return _m_csDbFieldName;
}
//------------------------------------------------------------------------------
const int &
CDbImageLabel::recordIndex() const {
    return _m_ciRecordIndex;
}
//------------------------------------------------------------------------------
QLabel *
CDbImageLabel::label() const {
    return _m_lblLabel;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   public, actions
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CDbImageLabel::loadFromFile() {
    QFileDialog fdlgDialog(_m_wdParent);

    fdlgDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fdlgDialog.setFileMode(QFileDialog::AnyFile);

    QStringList slFilters;

    slFilters << "Image files (" IMAGE_FORMATS ")";
    slFilters << "All   files (*)";

    fdlgDialog.setNameFilters(slFilters);
    // fdlgDialog.setDirectory();

    cint ciRv = fdlgDialog.exec();
    switch (ciRv) {
        case QDialog::Rejected:
            // n/a
            break;
        case QDialog::Accepted: {
            cQString csFilePath = fdlgDialog.selectedFiles().first();
            _loadFromFile(csFilePath, QSize(PHOTO_WIDTH, PHOTO_HEIGHT));
            }
            break;
        default:
            Q_ASSERT(false);
            break;
    }
}
//------------------------------------------------------------------------------
void
CDbImageLabel::saveToFile() {
    QFileDialog fdlgDialog(_m_wdParent);

    fdlgDialog.setAcceptMode(QFileDialog::AcceptSave);
    fdlgDialog.setFileMode(QFileDialog::AnyFile);
    // fdlgDialog.selectFile( QFileInfo(psbtnParent->filePath()).baseName() );
    // fdlgDialog.setDefaultSuffix(SHORTCUT_EXT);

    cint ciRv = fdlgDialog.exec();
    switch (ciRv) {
        case QDialog::Rejected:
            // n/a;
            break;
        case QDialog::Accepted: {
            cQString csFilePath = fdlgDialog.selectedFiles().first();
            _saveToFile(csFilePath);
            }
            break;
        default:
            Q_ASSERT(false);
            break;
    }
}
//------------------------------------------------------------------------------
void
CDbImageLabel::remove() {
    // ensure for removing
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Removing image.");
        msgBox.setInformativeText("Do you want to remove image?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);

        cint ciRv = msgBox.exec();
        switch (ciRv) {
            case QMessageBox::Yes:
                // yes, remove
                break;
            default:
                return;
                break;
        }
    }

    _remove();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   public, static
*
*******************************************************************************/

//------------------------------------------------------------------------------
int            CDbImageLabel::currentDbIndex = - 1;
CDbImageLabel *CDbImageLabel::currentDbImage = NULL;
//------------------------------------------------------------------------------
/* static */
CDbImageLabel *
CDbImageLabel::find(
    cdb_items_t  &dbItems,
    const QLabel *photoMini
)
{
    foreach (CDbImageLabel *item, dbItems) {
        if (photoMini == item->label()) {
            return item;
        }
    }

    return NULL;
}
//------------------------------------------------------------------------------
/* static */
CDbImageLabel *
CDbImageLabel::find(
    cdb_items_t &dbItems,
    cint        &index
)
{
    foreach (CDbImageLabel *item, dbItems) {
        if (index == item->recordIndex()) {
            return item;
        }
    }

    return NULL;
}
//------------------------------------------------------------------------------
/* static */
bool
CDbImageLabel::isLabelsEmpty(
    cdb_items_t &dbItems
)
{
    foreach (CDbImageLabel *item, dbItems) {
        if (NULL != item->label()->pixmap()) {
            return true;
        }
    }

    return false;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CDbImageLabel::_loadFromFile(
    cQString &a_filePath,   ///< image file path
    cSize    &a_photoSize   ///< image target size
)
{
    // TODO: ensure rewrite image

    _m_baBuffer.clear();

    // file to buffer
    {
        if (true == IMAGE_IS_CONVERT) {
            CUtils::imageConvert(a_filePath, &_m_baBuffer);
        } else {
            QFile file(a_filePath);

            bool bRv = file.open(QIODevice::ReadOnly);
            Q_ASSERT(bRv);

            _m_baBuffer = file.readAll();
        }

        Q_ASSERT(0 < _m_baBuffer.size());
    }

    // _m_lblLabel
    {
        if (0 >= _m_baBuffer.size()) {
            _m_lblLabel->setText(tr(TEXT_NO_PHOTO));
        } else {
            QImage imgPhoto;

            bool bRv = imgPhoto.loadFromData(_m_baBuffer);
            Q_ASSERT(bRv);

            QImage  imgPhotoScaled = imgPhoto.scaled(
                                        a_photoSize,
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation);
            QPixmap pixPixmap      = QPixmap::fromImage(imgPhotoScaled);

            _m_lblLabel->setPixmap(pixPixmap);
        }
    }

    _flush();
}
//------------------------------------------------------------------------------
void
CDbImageLabel::_saveToFile(
    cQString &a_filePath   ///< image file path
)
{
    QByteArray baPhoto = _m_tmModel->record(_m_ciRecordIndex)
                            .value(_m_csDbFieldName).toByteArray();

    QFile file(a_filePath);
    bool bRv = file.open(QIODevice::WriteOnly);
    Q_ASSERT(bRv);

    QDataStream stream(&file);
    cint ciRv = stream.writeRawData(baPhoto.constData(), baPhoto.size());
    Q_ASSERT(0 < ciRv);
}
//------------------------------------------------------------------------------
void
CDbImageLabel::_remove() {
    _m_baBuffer.clear();
    _flush();
    _m_lblLabel->clear();
}
//------------------------------------------------------------------------------
void
CDbImageLabel::_flush() {
    qCHECK_DO(_m_baBuffer.size() < 0, return);

    QSqlRecord srRecord = _m_tmModel->record(_m_ciRecordIndex);
    srRecord.setValue(_m_csDbFieldName, _m_baBuffer);

    _m_tmModel->setRecord(_m_ciRecordIndex, srRecord);
    bool bRv = _m_tmModel->submitAll();
    Q_ASSERT(bRv);

    _m_baBuffer.clear();
}
//------------------------------------------------------------------------------

