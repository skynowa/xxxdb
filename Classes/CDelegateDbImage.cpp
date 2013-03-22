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
    cQSize  &a_size,
    QLabel  *a_infoPanel /* = NULL */
) :
    QSqlRelationalDelegate(a_parent),
    _ciImageFieldIndex    (a_imageFieldIndex),
    _cszSize              (a_size),
    _lblInfoPanel         (a_infoPanel)
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(- 1   < a_imageFieldIndex);
    Q_ASSERT(a_size.isValid());
    // a_infoPanel - n/a
}
//------------------------------------------------------------------------------
void
CDelegateDbImage::setEditorData(
    QWidget           *a_editor,
    const QModelIndex &a_index
) const
{
    Q_ASSERT(NULL != a_editor);
    Q_ASSERT(a_index.isValid());

    if (_ciImageFieldIndex == a_index.column()) {
        QLabel *lblPhoto = static_cast<QLabel *>( a_editor );
        Q_ASSERT(NULL != lblPhoto);

        cQByteArray baPhoto = a_index.data(Qt::EditRole).toByteArray();
        if (baPhoto.isEmpty()) {
            lblPhoto->setText(TEXT_NO_PHOTO);
        } else {
            QPixmap pixOriginal;

            bool bRv = pixOriginal.loadFromData(baPhoto);
            Q_ASSERT(bRv);

            QPixmap pixScaled = pixOriginal.scaled(
                                        _cszSize,
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation);

            lblPhoto->setPixmap(pixScaled);
        }

        if (NULL != _lblInfoPanel) {
            cQString csText = QString(tr("Photo size: %1"))
                                .arg( CUtils::formatBytes(baPhoto.size()) );

            _lblInfoPanel->setText(csText);
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
    Q_ASSERT(NULL != a_editor);
    Q_ASSERT(NULL != a_model);
    Q_ASSERT(a_index.isValid());

    if (_ciImageFieldIndex == a_index.column()) {
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
            Q_ASSERT(bRv);

            a_model->setData(a_index, bfPhoto.data(), Qt::EditRole);
        #endif
        }
    } else {
        QSqlRelationalDelegate::setModelData(a_editor, a_model, a_index);
    }
}
//------------------------------------------------------------------------------
