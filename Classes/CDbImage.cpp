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
    QObject        *a_parent,
    QSqlTableModel *a_tableModel,
    const QString  &a_dbField,
    const int      &a_currentIndex,
    QLabel         *a_label
) :
    QObject          (a_parent),
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
CDbImage::importFromFile(
    const QString &a_filePath
)
{
    // TODO: importFromFile
}
//---------------------------------------------------------------------------
void
CDbImage::exportToFile(
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
CDbImage::changeFromFile(
    const QString &a_filePath
)
{
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
}
//---------------------------------------------------------------------------
void
CDbImage::clear() {
    _m_lblLabel->clear();
}
//---------------------------------------------------------------------------
void
CDbImage::remove() {
    clear();

    {
        _m_baBuffer.clear();

        QSqlRecord srRecord = _m_tmModel->record(_m_ciCurrentIndex);
        srRecord.setValue(_m_csDbField, _m_baBuffer);

        _m_tmModel->setRecord(_m_ciCurrentIndex, srRecord);
        bool bRv = _m_tmModel->submitAll();
        Q_ASSERT(true == bRv);
    }
}
//---------------------------------------------------------------------------
void
CDbImage::save() {
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
