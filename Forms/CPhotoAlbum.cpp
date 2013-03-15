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
    CSqlNavigator  *a_sqlNavigator
) :
    QMainWindow       (a_parent),
    _m_tmModel        (a_tableModel),
    _m_ciDbRecordIndex(a_sqlNavigator->view()->currentIndex().row()),
    _m_viDbItems      (),
    _m_pixPixmap      ()
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(NULL != a_tableModel);
    Q_ASSERT(NULL != a_sqlNavigator);
    Q_ASSERT(- 1  <  _m_ciDbRecordIndex);

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
    Q_ASSERT(NULL != a_obj);
    Q_ASSERT(NULL != a_event);

    // clicks on photos
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
                cQString  csDbFieldName = CDbImageLabel::find(_m_viDbItems, lblPhotoMini)->dbFieldName();

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
    Q_ASSERT(NULL != a_event);
    Q_UNUSED(a_event);

    // set primary image
    {
        // get primary image index
        cint ciPrimaryIndex = _m_tmModel->record(_m_ciDbRecordIndex)
                                .value(DB_F_PHOTOS_PRIMARY_DBFIELD).toInt();

        // set primary image index
        {
            QLabel   *lblPhotoMini  = CDbImageLabel::find(_m_viDbItems, ciPrimaryIndex)->label();
            cQString  csDbFieldName = CDbImageLabel::find(_m_viDbItems, ciPrimaryIndex)->dbFieldName();

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
    Q_ASSERT(NULL != a_event);
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
            CDbImageLabel *item = new CDbImageLabel(
                                        this,
                                        _m_tmModel,
                                        dbFieldNames[i],
                                        i,
                                        _m_ciDbRecordIndex,
                                        photoMinis[i]);

            connect(item, &CDbImageLabel::signal_DataChanged,
                    this, &CPhotoAlbum::slot_OnPhotoUpdate);

            _m_viDbItems.push_back(item);
        }
    }

    // map DB controls
    foreach (CDbImageLabel *cit, _m_viDbItems) {
        (void)_dbImageWidgetMap(cit->label(), cit->dbFieldName(), PHOTO_MINI_SIZE);
        cit->label()->installEventFilter(this);
    }
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::_initActions() {
    // group "File"
    {
        connect(m_Ui.actFile_Exit,       SIGNAL( triggered() ),
                this,                    SLOT  ( slot_OnExit() ));
    }

    // group "Edit"
    {
        connect(m_Ui.actEdit_SaveAs,     SIGNAL( triggered() ),
                this,                    SLOT  ( slot_OnSaveAs() ));
        connect(m_Ui.actEdit_First,      SIGNAL( triggered() ),
                this,                    SLOT  ( slot_OnFirst() ));
        connect(m_Ui.actEdit_Prior,      SIGNAL( triggered() ),
                this,                    SLOT  ( slot_OnPrior() ));
        connect(m_Ui.actEdit_Next,       SIGNAL( triggered() ),
                this,                    SLOT  ( slot_OnNext() ));
        connect(m_Ui.actEdit_Last,       SIGNAL( triggered() ),
                this,                    SLOT  ( slot_OnLast() ));
        connect(m_Ui.actEdit_GoTo,       SIGNAL( triggered() ),
                this,                    SLOT  ( slot_OnGoTo() ));
        connect(m_Ui.actEdit_Insert,     SIGNAL( triggered() ),
                this,                    SLOT  ( slot_OnInsert() ));
        connect(m_Ui.actEdit_Delete,     SIGNAL( triggered() ),
                this,                    SLOT  ( slot_OnRemove() ));
        connect(m_Ui.actEdit_Edit,       SIGNAL( triggered() ),
                this,                    SLOT  ( slot_OnEdit() ));
        connect(m_Ui.actEdit_SetPrimary, SIGNAL( triggered() ),
                this,                    SLOT  ( slot_OnSetPrimary() ));
    }
}
//------------------------------------------------------------------------------
QDataWidgetMapper *
CPhotoAlbum::_dbImageWidgetMap(
    QWidget  *a_widget,
    cQString &a_dbFieldName,
    cSize    &a_size
)
{
    Q_ASSERT(NULL != a_widget);
    Q_ASSERT(!a_dbFieldName.isEmpty());
    Q_ASSERT(a_size.isValid());

    QDataWidgetMapper *wmRv = new QDataWidgetMapper(this);
    wmRv->setModel(_m_tmModel);
    wmRv->setItemDelegate(new CDelegateDbImage(
                            wmRv,
                            _m_tmModel->fieldIndex(a_dbFieldName),
                            a_size,
                            NULL));
    wmRv->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    wmRv->addMapping(a_widget, _m_tmModel->fieldIndex(a_dbFieldName));
    wmRv->setCurrentIndex(_m_ciDbRecordIndex);

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
    CDbImageLabel::currentDbImageLabel->saveToFile();
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnFirst() {
    cint currentIndex = 0;

    slot_OnPhotoUpdate(currentIndex);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnPrior() {
    if (0 >= CDbImageLabel::currentIndex) {
        CDbImageLabel::currentIndex = 0;
    } else {
        -- CDbImageLabel::currentIndex;
    }

    slot_OnPhotoUpdate(CDbImageLabel::currentIndex);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnNext() {
    if (CDbImageLabel::currentIndex >= _m_viDbItems.size() - 1) {
        CDbImageLabel::currentIndex = _m_viDbItems.size() - 1;
    } else {
        ++ CDbImageLabel::currentIndex;
    }

    slot_OnPhotoUpdate(CDbImageLabel::currentIndex);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnLast() {
    cint currentIndex = _m_viDbItems.size() - 1;

    slot_OnPhotoUpdate(currentIndex);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnGoTo() {
    cint ciMinValue   = 1;
    cint ciMaxValue   = _m_viDbItems.size();

    cint currentIndex = QInputDialog::getInt(
                                this,
                                APP_NAME, tr("Go to photo:"),
                                CDbImageLabel::currentIndex + 1,
                                ciMinValue, ciMaxValue) - 1;

    slot_OnPhotoUpdate(currentIndex);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnInsert() {
    CDbImageLabel::currentDbImageLabel->loadFromFile();
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnRemove() {
    CDbImageLabel::currentDbImageLabel->remove();
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnEdit() {
    CDbImageLabel::currentDbImageLabel->loadFromFile();
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnSetPrimary() {
    // write to DB
    QSqlRecord srRecord = _m_tmModel->record(_m_ciDbRecordIndex);
    srRecord.setValue(DB_F_PHOTOS_PRIMARY_DBFIELD, CDbImageLabel::currentIndex);

    _m_tmModel->setRecord(_m_ciDbRecordIndex, srRecord);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   photo
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnLoop() {
    if (CDbImageLabel::currentIndex >= _m_viDbItems.size() - 1) {
        CDbImageLabel::currentIndex = 0;
    } else {
        ++ CDbImageLabel::currentIndex;
    }

    slot_OnPhotoUpdate(CDbImageLabel::currentIndex);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnPhotoUpdate(
    cint &index
)
{
    QLabel   *lblPhotoMini  = _m_viDbItems.at(index)->label();
    cQString  csDbFieldName = _m_viDbItems.at(index)->dbFieldName();

    slot_photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//------------------------------------------------------------------------------
void
CPhotoAlbum::slot_photoMini_OnClicked(
    QLabel   *a_label,
    cQString &a_dbFieldName
)
{
    Q_ASSERT(NULL != a_label);
    Q_ASSERT(!a_dbFieldName.isEmpty());

    // lblPhotoMini
    {
        // set border
        foreach (CDbImageLabel *i, _m_viDbItems) {
            if (a_label == i->label()) {
                // set current indexes
                CDbImageLabel::currentIndex        = i->index();
                CDbImageLabel::currentDbImageLabel = i;

                i->label()->setFrameShape(QFrame::WinPanel);
            } else {
                i->label()->setFrameShape(QFrame::Box);
            }
        }
    }

    // lblPhoto
    {
        cQByteArray baPhoto = _m_tmModel->record(_m_ciDbRecordIndex)
                                    .value(a_dbFieldName).toByteArray();

        if (baPhoto.isEmpty()) {
            m_Ui.lblPhoto->setText(TEXT_NO_PHOTO);
        } else {
            QImage imgPhoto;

            bool bRv = imgPhoto.loadFromData(baPhoto);
            Q_ASSERT(bRv);

            cint   ciMargin = 2;   // MAGIC: ciMargin
            cSize  cszSize  = QSize(m_Ui.lblPhoto->width()  - ciMargin,
                                    m_Ui.lblPhoto->height() - ciMargin);
            QImage pixNew   = imgPhoto.scaled(
                                    cszSize,
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);
            _m_pixPixmap = QPixmap::fromImage(pixNew);

            m_Ui.lblPhoto->setPixmap(_m_pixPixmap);
        }
    }
}
//------------------------------------------------------------------------------
