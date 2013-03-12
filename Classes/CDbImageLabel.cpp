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
    cint           &a_dbRecordIndex,  ///< DB record index
    QLabel         *a_label         ///< QLabel for display image
) :
    QObject           (a_parent),
    _m_wdParent       (a_parent),
    _m_tmModel        (a_tableModel),
    _m_csDbFieldName  (a_dbFieldName),
    _m_ciDbRecordIndex(a_dbRecordIndex),
    _m_lblLabel       (a_label),
    _m_baBuffer       ()
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(NULL != a_tableModel);
    Q_ASSERT(!a_dbFieldName.isEmpty());
    Q_ASSERT(- 1 < a_dbRecordIndex);
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
    Q_ASSERT(!_m_csDbFieldName.isEmpty());

    return _m_csDbFieldName;
}
//------------------------------------------------------------------------------
const int &
CDbImageLabel::dbRecordIndex() const {
    Q_ASSERT(- 1 < _m_ciDbRecordIndex);

    return _m_ciDbRecordIndex;
}
//------------------------------------------------------------------------------
QLabel *
CDbImageLabel::label() const {
    Q_ASSERT(NULL != _m_lblLabel);

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
    fdlgDialog.setDirectory( QDir() );

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
int            CDbImageLabel::currentDbRecordIndex = - 1;
CDbImageLabel *CDbImageLabel::currentDbImageLabel  = NULL;
//------------------------------------------------------------------------------
/* static */
CDbImageLabel *
CDbImageLabel::find(
    cdb_items_t  &a_dbItems,
    const QLabel *a_label
)
{
    foreach (CDbImageLabel *item, a_dbItems) {
        if (a_label == item->label()) {
            return item;
        }
    }

    return NULL;
}
//------------------------------------------------------------------------------
/* static */
CDbImageLabel *
CDbImageLabel::find(
    cdb_items_t &a_dbItems,
    cint        &a_dbRecordIndex
)
{
    foreach (CDbImageLabel *item, a_dbItems) {
        if (a_dbRecordIndex == item->dbRecordIndex()) {
            return item;
        }
    }

    return NULL;
}
//------------------------------------------------------------------------------
/* static */
bool
CDbImageLabel::isLabelsEmpty(
    cdb_items_t &a_dbItems
)
{
    foreach (CDbImageLabel *item, a_dbItems) {
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
    cSize    &a_imageSize   ///< image target size
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
            QImage imgImage;

            bool bRv = imgImage.loadFromData(_m_baBuffer);
            Q_ASSERT(bRv);

            QImage  imgImageScaled = imgImage.scaled(
                                        a_imageSize,
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation);
            QPixmap pixPixmap      = QPixmap::fromImage(imgImageScaled);

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
    QByteArray baImage = _m_tmModel->record( dbRecordIndex() )
                            .value(_m_csDbFieldName).toByteArray();

    QFile file(a_filePath);
    bool bRv = file.open(QIODevice::WriteOnly);
    Q_ASSERT(bRv);

    QDataStream stream(&file);
    cint ciRv = stream.writeRawData(baImage.constData(), baImage.size());
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

    QSqlRecord srRecord = _m_tmModel->record( dbRecordIndex() );
    srRecord.setValue(_m_csDbFieldName, _m_baBuffer);

    _m_tmModel->setRecord(dbRecordIndex(), srRecord);
    bool bRv = _m_tmModel->submitAll();
    Q_ASSERT(bRv);

    _m_baBuffer.clear();
}
//------------------------------------------------------------------------------

