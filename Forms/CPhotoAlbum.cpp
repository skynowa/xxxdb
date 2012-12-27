/**
 * \file   CPhotoAlbum.h
 * \brief  photo album
 */


#include "CPhotoAlbum.h"

#include "../QtLib/CUtils.h"
#include "../Classes/CDelegateDbImage.h"


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CPhotoAlbum::CPhotoAlbum(
    QWidget        *a_parent,
    QSqlTableModel *a_tableModel,
    const int      &a_currentRow
) :
    QDialog        (a_parent),
    _m_tmModel     (a_tableModel),
    _m_ciCurrentRow(a_currentRow)

{
    Q_ASSERT(NULL != _m_tmModel);

    _construct();
}
//---------------------------------------------------------------------------
/* virtual */
CPhotoAlbum::~CPhotoAlbum() {
    _destruct();
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPhotoAlbum::_construct() {
    _initMain();
}
//---------------------------------------------------------------------------
void
CPhotoAlbum::_destruct() {

}
//---------------------------------------------------------------------------
void
CPhotoAlbum::_initMain() {
    m_Ui.setupUi(this);

    // maps ui controls into DB fields
    {
        // (void)_dbWidgetMap(m_Ui.lblPhoto,        CONFIG_DB_F_PHOTOS_1,  size());

        (void)_dbWidgetMap(m_Ui.lblPhotoMini_1,  CONFIG_DB_F_PHOTOS_1,  CONFIG_PHOTO_MINI_SIZE);
        (void)_dbWidgetMap(m_Ui.lblPhotoMini_2,  CONFIG_DB_F_PHOTOS_2,  CONFIG_PHOTO_MINI_SIZE);
        (void)_dbWidgetMap(m_Ui.lblPhotoMini_3,  CONFIG_DB_F_PHOTOS_3,  CONFIG_PHOTO_MINI_SIZE);
        (void)_dbWidgetMap(m_Ui.lblPhotoMini_4,  CONFIG_DB_F_PHOTOS_4,  CONFIG_PHOTO_MINI_SIZE);
        (void)_dbWidgetMap(m_Ui.lblPhotoMini_5,  CONFIG_DB_F_PHOTOS_5,  CONFIG_PHOTO_MINI_SIZE);
        (void)_dbWidgetMap(m_Ui.lblPhotoMini_6,  CONFIG_DB_F_PHOTOS_6,  CONFIG_PHOTO_MINI_SIZE);
        (void)_dbWidgetMap(m_Ui.lblPhotoMini_7,  CONFIG_DB_F_PHOTOS_7,  CONFIG_PHOTO_MINI_SIZE);
        (void)_dbWidgetMap(m_Ui.lblPhotoMini_8,  CONFIG_DB_F_PHOTOS_8,  CONFIG_PHOTO_MINI_SIZE);
        (void)_dbWidgetMap(m_Ui.lblPhotoMini_9,  CONFIG_DB_F_PHOTOS_9,  CONFIG_PHOTO_MINI_SIZE);
        (void)_dbWidgetMap(m_Ui.lblPhotoMini_10, CONFIG_DB_F_PHOTOS_10, CONFIG_PHOTO_MINI_SIZE);
    }
}
//---------------------------------------------------------------------------
QDataWidgetMapper *
CPhotoAlbum::_dbWidgetMap(
    QWidget       *a_widget,
    const QString &a_dbFieldName,
    const QSize   &a_size
)
{
    QDataWidgetMapper *wmRv = NULL;

    wmRv = new QDataWidgetMapper(this);
    wmRv->setModel(_m_tmModel);
    wmRv->setItemDelegate(new CDelegateDbImage(wmRv, _m_tmModel->fieldIndex(a_dbFieldName), a_size, NULL));
    wmRv->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    wmRv->addMapping(a_widget, _m_tmModel->fieldIndex(a_dbFieldName));
    wmRv->setCurrentIndex(_m_ciCurrentRow);

    return wmRv;
}
//---------------------------------------------------------------------------
