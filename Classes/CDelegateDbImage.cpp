/**
 * \file   CDelegateDbImage.cpp
 * \brief
 */


#include "CDelegateDbImage.h"


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CDelegateDbImage::CDelegateDbImage(
    QObject   *a_parent,
    const int &a_imageFieldIndex,
    QLabel    *a_infoPanel /* = NULL */
) :
    QSqlRelationalDelegate(a_parent),
    _m_ciImageFieldIndex  (a_imageFieldIndex),
    _m_lblInfoPanel       (a_infoPanel)
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(0    <= _m_ciImageFieldIndex);
    // _m_lblInfoPanel - n/a
}
//---------------------------------------------------------------------------
void
CDelegateDbImage::setEditorData(
    QWidget           *a_editor,
    const QModelIndex &a_index
) const
{
    if (_m_ciImageFieldIndex == a_index.column()) {
        QLabel *lblPhoto = static_cast<QLabel *>( a_editor );
        Q_ASSERT(lblPhoto);

        QByteArray baPhoto = a_index.data(Qt::EditRole).toByteArray();

        if (0 >= baPhoto.size()) {
            lblPhoto->setText(tr(CONFIG_TEXT_NO_PHOTO));
        } else {
            QImage imgPhoto;

            bool bRv = imgPhoto.loadFromData(baPhoto);
            Q_ASSERT(true == bRv);

            QImage  imgPhotoScaled = imgPhoto.scaled(QSize(CONFIG_PHOTO_WIDTH, CONFIG_PHOTO_HEIGHT), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QPixmap pixPixmap      = QPixmap::fromImage(imgPhotoScaled);

            lblPhoto->setPixmap(pixPixmap);
        }

        if (NULL != _m_lblInfoPanel) {
            const QString csText = QString("Photo size: ") + qS2QS( CxString::sFormatBytes(baPhoto.size()) );

            _m_lblInfoPanel->setText(csText);
        }
    } else {
        QSqlRelationalDelegate::setEditorData(a_editor, a_index);
    }
}
//---------------------------------------------------------------------------
void
CDelegateDbImage::setModelData(
    QWidget            *a_editor,
    QAbstractItemModel *a_model,
    const QModelIndex  &a_index
) const
{
    if (_m_ciImageFieldIndex == a_index.column()) {
        QLabel *label = static_cast<QLabel *>( a_editor );
        Q_ASSERT(label);

        QBuffer buf;
        buf.open(QIODevice::WriteOnly);

        bool bRv = label->pixmap()->save(&buf, "jpeg");
        Q_ASSERT(true == bRv);

        a_model->setData(a_index, buf.data(), Qt::EditRole);
    } else {
        QSqlRelationalDelegate::setModelData(a_editor, a_model, a_index);
    }
}
//---------------------------------------------------------------------------



