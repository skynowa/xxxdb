/**
 * \file   CDbImage.cpp
 * \brief  DB image
 */


#include "CDbImage.h"


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CDbImage::CDbImage(
    QWidget        *a_parent,
    QSqlTableModel *a_tableModel,
    const QString  &a_dbField,
    const int      &a_currentIndex,
    QLabel         *a_label
) :
    QObject          (a_parent),
    _m_wdParent      (a_parent),
    _m_tmModel       (a_tableModel),
    _m_csDbField     (a_dbField),
    _m_ciCurrentIndex(a_currentIndex),
    _m_lblLabel      (a_label),
    _m_baBuffer      ()
{

}
//---------------------------------------------------------------------------
CDbImage::~CDbImage() {

}
//---------------------------------------------------------------------------
void
CDbImage::loadFromFile() {
    QFileDialog fdlgDialog(_m_wdParent);

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
                const QString csFilePath = fdlgDialog.selectedFiles().first();

                _loadFromFile(csFilePath);
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
CDbImage::saveToFile() {
    QFileDialog fdlgDialog(_m_wdParent);

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
                const QString csFilePath = fdlgDialog.selectedFiles().first();

                _saveToFile(csFilePath);
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
CDbImage::remove() {
    // ensure for removing
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Removing image.");
        msgBox.setInformativeText("Do you want to remove image?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);

        int iRv = msgBox.exec();
        switch (iRv) {
            case QMessageBox::Yes: {
                // yes, remove
                break;
            }

            default: {
                return;
                break;
            }
        }
    }

    // remove
    {
        _m_lblLabel->clear();

        {
            _m_baBuffer.clear();

            QSqlRecord srRecord = _m_tmModel->record(_m_ciCurrentIndex);
            srRecord.setValue(_m_csDbField, _m_baBuffer);

            _m_tmModel->setRecord(_m_ciCurrentIndex, srRecord);
            bool bRv = _m_tmModel->submitAll();
            Q_ASSERT(true == bRv);
        }
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CDbImage::_loadFromFile(
    const QString &a_filePath
)
{
    // TODO: ensure rewrite image

    _m_baBuffer.clear();

    // file to buffer
    {
        if (true == CONFIG_IMAGE_IS_CONVERT) {
            CUtils::imageConvert(a_filePath, &_m_baBuffer);
        } else {
            QFile file(a_filePath);

            bool bRv = file.open(QIODevice::ReadOnly);
            Q_ASSERT(true == bRv);

            _m_baBuffer = file.readAll();
        }

        Q_ASSERT(0 < _m_baBuffer.size());
    }

    // _m_lblLabel
    {
        if (0 >= _m_baBuffer.size()) {
            _m_lblLabel->setText(tr(CONFIG_TEXT_NO_PHOTO));
        } else {
            QImage imgPhoto;

            bool bRv = imgPhoto.loadFromData(_m_baBuffer);
            Q_ASSERT(true == bRv);

            QImage  imgPhotoScaled = imgPhoto.scaled(
                                        QSize(CONFIG_PHOTO_WIDTH, CONFIG_PHOTO_HEIGHT),
                                        Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QPixmap pixPixmap      = QPixmap::fromImage(imgPhotoScaled);

            _m_lblLabel->setPixmap(pixPixmap);
        }
    }

    _flush();
}
//---------------------------------------------------------------------------
void
CDbImage::_saveToFile(
    const QString &a_filePath
)
{
    QByteArray baPhoto = _m_tmModel->record(_m_ciCurrentIndex)
                            .value(_m_csDbField).toByteArray();

    QFile file(a_filePath);
    bool bRv = file.open(QIODevice::WriteOnly);
    Q_ASSERT(true == bRv);

    QDataStream stream(&file);
    int iRv = stream.writeRawData(baPhoto.constData(), baPhoto.size());
    Q_ASSERT(0 < iRv);
}
//---------------------------------------------------------------------------
void
CDbImage::_flush() {
    if (0 < _m_baBuffer.size()) {
        QSqlRecord srRecord = _m_tmModel->record(_m_ciCurrentIndex);
        srRecord.setValue(_m_csDbField, _m_baBuffer);

        _m_tmModel->setRecord(_m_ciCurrentIndex, srRecord);
        bool bRv = _m_tmModel->submitAll();
        Q_ASSERT(true == bRv);

        _m_baBuffer.clear();
    }
}
//---------------------------------------------------------------------------

