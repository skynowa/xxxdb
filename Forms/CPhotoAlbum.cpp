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
bool
CPhotoAlbum::eventFilter(
    QObject *a_obj,
    QEvent  *a_event
)
{
    Q_UNUSED(a_obj);

    if (a_event->type() == QEvent::MouseButtonPress)  {
        QLabel *label = static_cast<QLabel *>( a_obj );

        photoMini_OnClicked(label, CONFIG_DB_F_PHOTOS_1);

        return true;
    }

    return QObject::eventFilter(a_obj, a_event);
}
//---------------------------------------------------------------------------
void
CPhotoAlbum::photoMini_OnClicked(
    QLabel        *a_label,
    const QString &a_dbFieldName
)
{
    // lblPhoto
    {
        QByteArray baPhoto = _m_tmModel->record(_m_ciCurrentRow).value(a_dbFieldName).toByteArray();

        if (0 >= baPhoto.size()) {
            m_Ui.lblPhoto->setText(tr(CONFIG_TEXT_NO_PHOTO));
        } else {
            QImage imgPhoto;

            bool bRv = imgPhoto.loadFromData(baPhoto);
            Q_ASSERT(true == bRv);

            const int   ciHiddenMargin = 2;   // MAGIC: ciHiddenMargin
            const QSize cszSize        = QSize(m_Ui.lblPhoto->width()  - ciHiddenMargin,
                                               m_Ui.lblPhoto->height() - ciHiddenMargin);
            QImage      imgPhotoScaled = imgPhoto.scaled(cszSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QPixmap     pixPixmap      = QPixmap::fromImage(imgPhotoScaled);

            m_Ui.lblPhoto->setPixmap(pixPixmap);
        }

        a_label->setFrameShape(QFrame::WinPanel);
        // a_label->setFrameShadow(QFrame::Sunken);
    }
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

    // install event filter
    {
        m_Ui.lblPhotoMini_1->installEventFilter(this);
        m_Ui.lblPhotoMini_2->installEventFilter(this);
        m_Ui.lblPhotoMini_3->installEventFilter(this);
        m_Ui.lblPhotoMini_4->installEventFilter(this);
        m_Ui.lblPhotoMini_5->installEventFilter(this);
        m_Ui.lblPhotoMini_6->installEventFilter(this);
        m_Ui.lblPhotoMini_7->installEventFilter(this);
        m_Ui.lblPhotoMini_8->installEventFilter(this);
        m_Ui.lblPhotoMini_9->installEventFilter(this);
        m_Ui.lblPhotoMini_10->installEventFilter(this);
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
