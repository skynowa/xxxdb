/**
 * \file   CDelegateDbImage.cpp
 * \brief
 */


#include "CDelegateDbImage.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CDelegateDbImage::CDelegateDbImage(
    QObject *a_parent,
    cint    &a_imageFieldIndex,
    cSize   &a_size,
    QLabel  *a_infoPanel /* = NULL */
) :
    QSqlRelationalDelegate(a_parent),
    _m_ciImageFieldIndex  (a_imageFieldIndex),
    _m_cszSize            (a_size),
    _m_lblInfoPanel       (a_infoPanel)
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(0    <= _m_ciImageFieldIndex);
    // _m_lblInfoPanel - n/a
}
//------------------------------------------------------------------------------
void
CDelegateDbImage::setEditorData(
    QWidget           *a_editor,
    const QModelIndex &a_index
) const
{
    if (_m_ciImageFieldIndex == a_index.column()) {
        QLabel *lblPhoto = static_cast<QLabel *>( a_editor );
        Q_ASSERT(NULL != lblPhoto);

        cQByteArray baPhoto = a_index.data(Qt::EditRole).toByteArray();
        if (baPhoto.isEmpty()) {
            lblPhoto->setText(tr(TEXT_NO_PHOTO));
        } else {
            QImage imgPhoto;

            bool bRv = imgPhoto.loadFromData(baPhoto);
            Q_ASSERT(true == bRv);

            QImage  imgPhotoScaled = imgPhoto.scaled(
                                        _m_cszSize,
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation);
            QPixmap pixPixmap      = QPixmap::fromImage(imgPhotoScaled);

            lblPhoto->setPixmap(pixPixmap);
        }

        if (NULL != _m_lblInfoPanel) {
            cQString csText = QString("Photo size: %1")
                                .arg( CUtils::formatBytes(baPhoto.size()) );

            _m_lblInfoPanel->setText(csText);
        }
    } else {
        QSqlRelationalDelegate::setEditorData(a_editor, a_index);
    }
}
//------------------------------------------------------------------------------
void
CDelegateDbImage::setModelData(
    QWidget            *a_editor,
    QAbstractItemModel *a_model,
    const QModelIndex  &a_index
) const
{
    if (_m_ciImageFieldIndex == a_index.column()) {
        QLabel *lblPhoto = static_cast<QLabel *>( a_editor );
        Q_ASSERT(NULL != lblPhoto);

        QBuffer bfPhoto;

        const QPixmap *ppmPixmap = lblPhoto->pixmap();
        if (NULL == ppmPixmap) {
            // clear photo in DB
            if (bfPhoto.isOpen()) {
                bfPhoto.reset();
            }

            a_model->setData(a_index, bfPhoto.data(), Qt::EditRole);
        } else {
            // TODO: don't rewrite photo in DB
        #if 0
            bfPhoto.open(QIODevice::WriteOnly);

            bool bRv = ppmPixmap->save(&bfPhoto, "jpeg");
            Q_ASSERT(true == bRv);

            a_model->setData(a_index, bfPhoto.data(), Qt::EditRole);
        #endif
        }
    } else {
        QSqlRelationalDelegate::setModelData(a_editor, a_model, a_index);
    }
}
//------------------------------------------------------------------------------
