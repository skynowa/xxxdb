/**
 * \file   CPhotoAlbum.h
 * \brief  photo album
 */


#include "CPhotoAlbum.h"

#include "../QtLib/CUtils.h"
#include "../Classes/CDelegateDbImage.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CPhotoAlbum::CPhotoAlbum(
    QWidget        *a_parent,
    QSqlTableModel *a_tableModel,
    const int      &a_currentRow
) :
    QMainWindow    (a_parent),
    _m_tmModel     (a_tableModel),
    _m_ciCurrentRow(a_currentRow),
    _m_viDbItems   (),
    _m_pixPixmap   ()
{
    Q_ASSERT(NULL != _m_tmModel);
    Q_ASSERT(- 1   < _m_ciCurrentRow);

    _construct();
}
//------------------------------------------------------------------------------
/* virtual */
CPhotoAlbum::~CPhotoAlbum() {
    _destruct();
}
//------------------------------------------------------------------------------
bool
CPhotoAlbum::eventFilter(
    QObject *a_obj,
    QEvent  *a_event
)
{
    if (a_event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(a_event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QLabel *label = static_cast<QLabel *>( a_obj );
            if (m_Ui.lblPhoto == label) {
                // m_Ui.lblPhoto
                slot_OnLoop();
            } else {
                // other QLabels
                QLabel   *lblPhotoMini  = label;
                cQString  csDbFieldName = CImageItem::find(_m_viDbItems, lblPhotoMini)->dbFieldName;

                slot_photoMini_OnClicked(lblPhotoMini, csDbFieldName);
            }

            return true;
        }
    }

    return QObject::eventFilter(a_obj, a_event);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::showEvent(
    QShowEvent *a_event
)
{
    Q_UNUSED(a_event);

    // set primary image
    {
        // get primary image index
        int iPrimaryIndex = - 1;
        {
            QSqlRecord srRecord = _m_tmModel->record(_m_ciCurrentRow);
            iPrimaryIndex = srRecord.value(DB_F_PHOTOS_PRIMARY_DBFIELD).toInt();
        }

        // set primary image index
        {
            QLabel   *lblPhotoMini  = CImageItem::find(_m_viDbItems, iPrimaryIndex)->photoMini;
            cQString  csDbFieldName = CImageItem::find(_m_viDbItems, iPrimaryIndex)->dbFieldName;

            slot_photoMini_OnClicked(lblPhotoMini, csDbFieldName);
        }
    }
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::resizeEvent(
    QResizeEvent *a_event
)
{
    Q_UNUSED(a_event);

    // lblPhoto
    if (!_m_pixPixmap.isNull()) {
        QSize szScaled = _m_pixPixmap.size();

        szScaled.scale(m_Ui.lblPhoto->size(), Qt::KeepAspectRatio);

        if (NULL     == m_Ui.lblPhoto->pixmap() ||
            szScaled != m_Ui.lblPhoto->pixmap()->size())
        {
            // update
            cint    ciMargin = 2;   // MAGIC: ciMargin
            QPixmap pixNew   = _m_pixPixmap.scaled(
                                    QSize(m_Ui.lblPhoto->width()  - ciMargin,
                                          m_Ui.lblPhoto->height() - ciMargin),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

            m_Ui.lblPhoto->setPixmap(pixNew);
        }
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CPhotoAlbum::_construct() {
    _initMain();
    _initActions();
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::_destruct() {

}
//------------------------------------------------------------------------------
void
CPhotoAlbum::_initMain() {
    m_Ui.setupUi(this);

    setWindowFlags(Qt::Window);

    // lblPhoto
    m_Ui.lblPhoto->installEventFilter(this);

    // _m_viDbItems
    {
        csize_t ciPhotoNum = PHOTO_NUM;

        QLabel * photoMinis[ciPhotoNum] = {
            m_Ui.lblPhotoMini_1,
            m_Ui.lblPhotoMini_2,
            m_Ui.lblPhotoMini_3,
            m_Ui.lblPhotoMini_4,
            m_Ui.lblPhotoMini_5,
            m_Ui.lblPhotoMini_6,
            m_Ui.lblPhotoMini_7,
            m_Ui.lblPhotoMini_8,
            m_Ui.lblPhotoMini_9,
            m_Ui.lblPhotoMini_10
        };

        cQString dbFieldNames[ciPhotoNum] = {
            DB_F_PHOTOS_1,
            DB_F_PHOTOS_2,
            DB_F_PHOTOS_3,
            DB_F_PHOTOS_4,
            DB_F_PHOTOS_5,
            DB_F_PHOTOS_6,
            DB_F_PHOTOS_7,
            DB_F_PHOTOS_8,
            DB_F_PHOTOS_9,
            DB_F_PHOTOS_10
        };

        // fill _m_viDbItems
        _m_viDbItems.reserve(ciPhotoNum);

        for (size_t i = 0; i < ciPhotoNum; ++ i) {
            CImageItem *item = new CImageItem;
            item->index       = i;
            item->photoMini   = photoMinis[i];
            item->dbFieldName = dbFieldNames[i];
            item->dbImage     = new CDbImage(this, _m_tmModel, dbFieldNames[i],
                                             _m_ciCurrentRow, photoMinis[i]);

            _m_viDbItems.push_back(item);
        }
    }

    // map DB controls
    foreach (CImageItem *cit, _m_viDbItems) {
        (QDataWidgetMapper *) _dbWidgetMap(cit->photoMini, cit->dbFieldName,
                                           PHOTO_MINI_SIZE);
        cit->photoMini->installEventFilter(this);
    }
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::_initActions() {
    // group "File"
    {
        connect(m_Ui.actFile_Exit,        SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnExit() ));
    }

    // group "Edit"
    {
        connect(m_Ui.actEdit_SaveAs,      SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnSaveAs() ));
        connect(m_Ui.actEdit_First,       SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnFirst() ));
        connect(m_Ui.actEdit_Prior,       SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnPrior() ));
        connect(m_Ui.actEdit_Next,        SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnNext() ));
        connect(m_Ui.actEdit_Last,        SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnLast() ));
        connect(m_Ui.actEdit_To,          SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnTo() ));
        connect(m_Ui.actEdit_Insert,      SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnInsert() ));
        connect(m_Ui.actEdit_Delete,      SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnRemove() ));
        connect(m_Ui.actEdit_Edit,        SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnEdit() ));
        connect(m_Ui.actEdit_SetPrimary,  SIGNAL( triggered() ),
                this,                     SLOT  ( slot_OnSetPrimary() ));
    }
}
//------------------------------------------------------------------------------
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
    wmRv->setItemDelegate(new CDelegateDbImage(
                            wmRv,
                            _m_tmModel->fieldIndex(a_dbFieldName),
                            a_size,
                            NULL));
    wmRv->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    wmRv->addMapping(a_widget, _m_tmModel->fieldIndex(a_dbFieldName));
    wmRv->setCurrentIndex(_m_ciCurrentRow);

    return wmRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "File"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnExit() {
    close();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "Edit"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnSaveAs() {
    CImageItem::currentDbImage->saveToFile();
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnFirst() {
    QLabel   *lblPhotoMini  = _m_viDbItems.first()->photoMini;
    cQString  csDbFieldName = _m_viDbItems.first()->dbFieldName;

    slot_photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnPrior() {
    if (0 >= CImageItem::currentDbIndex) {
        CImageItem::currentDbIndex = 0;
    } else {
        -- CImageItem::currentDbIndex;
    }

    QLabel   *lblPhotoMini  = _m_viDbItems.at(CImageItem::currentDbIndex)->photoMini;
    cQString  csDbFieldName = _m_viDbItems.at(CImageItem::currentDbIndex)->dbFieldName;

    slot_photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnNext() {
    if (CImageItem::currentDbIndex >= _m_viDbItems.count() - 1) {
        CImageItem::currentDbIndex = _m_viDbItems.count() - 1;
    } else {
        ++ CImageItem::currentDbIndex;
    }

    QLabel   *lblPhotoMini  = _m_viDbItems.at(CImageItem::currentDbIndex)->photoMini;
    cQString  csDbFieldName = _m_viDbItems.at(CImageItem::currentDbIndex)->dbFieldName;

    slot_photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnLast() {
    QLabel  *lblPhotoMini  = _m_viDbItems.last()->photoMini;
    QString  csDbFieldName = _m_viDbItems.last()->dbFieldName;

    slot_photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnTo() {
    cint ciMinValue    = 1;
    cint ciMaxValue    = _m_viDbItems.count();

    cint ciTargetIndex = QInputDialog::getInt(
                            this,
                            APP_NAME, tr("Go to photo:"),
                            CImageItem::currentDbIndex + 1,
                            ciMinValue, ciMaxValue) - 1;

    QLabel   *lblPhotoMini  = _m_viDbItems.at(ciTargetIndex)->photoMini;
    cQString  csDbFieldName = _m_viDbItems.at(ciTargetIndex)->dbFieldName;

    slot_photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnInsert() {
    CImageItem::currentDbImage->loadFromFile();
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnRemove() {
    CImageItem::currentDbImage->remove();
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnEdit() {
    CImageItem::currentDbImage->loadFromFile();
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnSetPrimary() {
    cint ciPrimaryIndex = CImageItem::currentDbIndex;

    // write to DB
    QSqlRecord srRecord = _m_tmModel->record(_m_ciCurrentRow);
    srRecord.setValue(DB_F_PHOTOS_PRIMARY_DBFIELD, ciPrimaryIndex);

    _m_tmModel->setRecord(_m_ciCurrentRow, srRecord);
    bool bRv = _m_tmModel->submit();
    Q_ASSERT(true == bRv);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   photo
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnLoop() {
    if (CImageItem::currentDbIndex >= _m_viDbItems.count() - 1) {
        CImageItem::currentDbIndex = 0;
    } else {
        ++ CImageItem::currentDbIndex;
    }

    QLabel   *lblPhotoMini  = _m_viDbItems.at(CImageItem::currentDbIndex)->photoMini;
    cQString  csDbFieldName = _m_viDbItems.at(CImageItem::currentDbIndex)->dbFieldName;

    slot_photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_photoMini_OnClicked(
    QLabel   *a_label,
    cQString &a_dbFieldName
)
{
    Q_ASSERT(NULL  != a_label);
    Q_ASSERT(false == a_dbFieldName.isEmpty());

    // lblPhotoMini
    {
        // set border
        foreach (CImageItem *i, _m_viDbItems) {
            if (a_label == i->photoMini) {
                // set current indexs
                CImageItem::currentDbIndex = i->index;
                CImageItem::currentDbImage = i->dbImage;

                i->photoMini->setFrameShape(QFrame::WinPanel);
            } else {
                i->photoMini->setFrameShape(QFrame::Box);
            }
        }
    }

    // lblPhoto
    {
        cQByteArray baPhoto = _m_tmModel->record(_m_ciCurrentRow)
                                .value(a_dbFieldName).toByteArray();

        if (0 >= baPhoto.size()) {
            m_Ui.lblPhoto->setText(tr(TEXT_NO_PHOTO));
        } else {
            QImage imgPhoto;

            bool bRv = imgPhoto.loadFromData(baPhoto);
            Q_ASSERT(true == bRv);

            cint        ciMargin = 2;   // MAGIC: ciMargin
            const QSize cszSize  = QSize(m_Ui.lblPhoto->width()  - ciMargin,
                                         m_Ui.lblPhoto->height() - ciMargin);
            QImage      pixNew   = imgPhoto.scaled(
                                        cszSize,
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation);
            _m_pixPixmap = QPixmap::fromImage(pixNew);

            m_Ui.lblPhoto->setPixmap(_m_pixPixmap);
        }
    }
}
//------------------------------------------------------------------------------
