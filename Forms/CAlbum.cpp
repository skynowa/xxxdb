/**
 * \file   CAlbum.h
 * \brief  photo album
 */


#include "CAlbum.h"

#include "../QtLib/CUtils.h"
#include "../Classes/CSettings.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CAlbum::CAlbum(
    QWidget        *a_parent,
    QSqlTableModel *a_tableModel,
    CSqlNavigator  *a_sqlNavigator
) :
    QMainWindow       (a_parent),
    _m_stApp          (NULL),
    _m_tmModel        (a_tableModel),
    _m_ciDbRecordIndex(a_sqlNavigator->view()->currentIndex().row()),
    _m_viDbItems      (),
    _m_pixPhoto       ()
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(NULL != a_tableModel);
    Q_ASSERT(NULL != a_sqlNavigator);
    Q_ASSERT(- 1  <  _m_ciDbRecordIndex);

    _construct();

    _m_stApp = new CSettings(NULL, NULL, this);
}
//------------------------------------------------------------------------------
/* virtual */
CAlbum::~CAlbum() {

}
//------------------------------------------------------------------------------

/*******************************************************************************
*   protected
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* virtual */
bool
CAlbum::eventFilter(
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
                emit signal_photo_clicked();
            } else {
                // other QLabels
                QLabel   *lblPhotoMini  = label;
                cQString  csDbFieldName = CDbImageLabel::find(_m_viDbItems, lblPhotoMini)->dbFieldName();

                emit signal_photoMini_clicked(lblPhotoMini, csDbFieldName);
            }

            return true;
        }
    }

    return QObject::eventFilter(a_obj, a_event);
}
//------------------------------------------------------------------------------
/* virtual */
void
CAlbum::showEvent(
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
/* virtual */
void
CAlbum::resizeEvent(
    QResizeEvent *a_event
)
{
    Q_ASSERT(NULL != a_event);
    Q_UNUSED(a_event);

    // lblPhoto
    if (!_m_pixPhoto.isNull()) {
        QSize szScaled = _m_pixPhoto.size();

        szScaled.scale(m_Ui.lblPhoto->size(), Qt::KeepAspectRatio);

        if (NULL     == m_Ui.lblPhoto->pixmap() ||
            szScaled != m_Ui.lblPhoto->pixmap()->size())
        {
            _photoUpdate();
        }
    }
}
//------------------------------------------------------------------------------
/* virtual */
void
CAlbum::closeEvent(
    QCloseEvent *a_event
)
{
    _destruct();
    a_event->accept();
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CAlbum::_construct() {
    _initMain();
    _initActions();
}
//------------------------------------------------------------------------------
void
CAlbum::_destruct() {
    qPTR_DELETE(_m_stApp);
}
//------------------------------------------------------------------------------
void
CAlbum::_initMain() {
    m_Ui.setupUi(this);

    // main
    {
        setWindowTitle(APP_PHOTO_ALBUM_TITLE);
        setWindowFlags(Qt::Window);
    }

    // lblPhoto
    m_Ui.lblPhoto->installEventFilter(this);
    m_Ui.lblPhoto->setMinimumSize(PHOTO_MINI_SIZE);

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
                                        photoMinis[i], PHOTO_MINI_SIZE);

            photoMinis[i]->installEventFilter(this);

            connect(item, &CDbImageLabel::signal_DataChanged,
                    this, &CAlbum::slot_OnPhotoUpdate);
            connect(this, &CAlbum::signal_photoMini_clicked,
                    this, &CAlbum::slot_photoMini_OnClicked);

            _m_viDbItems.push_back(item);
        }
    }

    // slots
    {
        connect(this, &CAlbum::signal_photo_clicked,
                this, &CAlbum::slot_OnLoop);
    }

    // HACK: for m_Ui.saPhotosMini->sizePolicy() == Fixed
    qApp->processEvents();
}
//------------------------------------------------------------------------------
void
CAlbum::_initActions() {
    // group "File"
    {
        connect(m_Ui.actFile_Exit,       &QAction::triggered,
                this,                    &CAlbum::slot_OnExit);
    }

    // group "Edit"
    {
        connect(m_Ui.actEdit_SaveAs,     &QAction::triggered,
                this,                    &CAlbum::slot_OnSaveAs);
        connect(m_Ui.actEdit_First,      &QAction::triggered,
                this,                    &CAlbum::slot_OnFirst);
        connect(m_Ui.actEdit_Prior,      &QAction::triggered,
                this,                    &CAlbum::slot_OnPrior);
        connect(m_Ui.actEdit_Next,       &QAction::triggered,
                this,                    &CAlbum::slot_OnNext);
        connect(m_Ui.actEdit_Last,       &QAction::triggered,
                this,                    &CAlbum::slot_OnLast);
        connect(m_Ui.actEdit_GoTo,       &QAction::triggered,
                this,                    &CAlbum::slot_OnGoTo);
        connect(m_Ui.actEdit_Insert,     &QAction::triggered,
                this,                    &CAlbum::slot_OnInsert);
        connect(m_Ui.actEdit_Delete,     &QAction::triggered,
                this,                    &CAlbum::slot_OnRemove);
        connect(m_Ui.actEdit_Edit,       &QAction::triggered,
                this,                    &CAlbum::slot_OnEdit);
        connect(m_Ui.actEdit_SetPrimary, &QAction::triggered,
                this,                    &CAlbum::slot_OnSetPrimary);
    }
}
//------------------------------------------------------------------------------
void
CAlbum::_photoUpdate() {
    Q_ASSERT(!_m_pixPhoto.isNull());

    cQSize  cszSize   = QSize(m_Ui.lblPhoto->width()  - PHOTO_MARGIN,
                              m_Ui.lblPhoto->height() - PHOTO_MARGIN);
    QPixmap pixScaled = _m_pixPhoto.scaled(
                              cszSize,
                              Qt::KeepAspectRatio,
                              Qt::FastTransformation);

    m_Ui.lblPhoto->setPixmap(pixScaled);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "File"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CAlbum::slot_OnExit() {
    close();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "Edit"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CAlbum::slot_OnSaveAs() {
    CDbImageLabel::currentDbImageLabel->saveToFile();
}
//------------------------------------------------------------------------------
void
CAlbum::slot_OnFirst() {
    cint currentIndex = 0;

    slot_OnPhotoUpdate(currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::slot_OnPrior() {
    if (0 >= CDbImageLabel::currentIndex) {
        CDbImageLabel::currentIndex = 0;
    } else {
        -- CDbImageLabel::currentIndex;
    }

    slot_OnPhotoUpdate(CDbImageLabel::currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::slot_OnNext() {
    if (CDbImageLabel::currentIndex >= _m_viDbItems.size() - 1) {
        CDbImageLabel::currentIndex = _m_viDbItems.size() - 1;
    } else {
        ++ CDbImageLabel::currentIndex;
    }

    slot_OnPhotoUpdate(CDbImageLabel::currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::slot_OnLast() {
    cint currentIndex = _m_viDbItems.size() - 1;

    slot_OnPhotoUpdate(currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::slot_OnGoTo() {
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
CAlbum::slot_OnInsert() {
    CDbImageLabel::currentDbImageLabel->loadFromFile();
}
//------------------------------------------------------------------------------
void
CAlbum::slot_OnRemove() {
    CDbImageLabel::currentDbImageLabel->remove();
}
//------------------------------------------------------------------------------
void
CAlbum::slot_OnEdit() {
    CDbImageLabel::currentDbImageLabel->loadFromFile();
}
//------------------------------------------------------------------------------
void
CAlbum::slot_OnSetPrimary() {
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
CAlbum::slot_OnLoop() {
    // avoid recursion when photo album is empty
    qCHECK_DO(CDbImageLabel::isEmpty(_m_viDbItems), return);

    // calc current index
    if (CDbImageLabel::currentIndex >= _m_viDbItems.size() - 1) {
        CDbImageLabel::currentIndex = 0;
    } else {
        ++ CDbImageLabel::currentIndex;
    }

    // skip empty images
    if (_m_viDbItems.at(CDbImageLabel::currentIndex)->isEmpty()) {
        slot_OnLoop();
    }

    slot_OnPhotoUpdate(CDbImageLabel::currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::slot_OnPhotoUpdate(
    cint &index
)
{
    QLabel   *lblPhotoMini  = _m_viDbItems.at(index)->label();
    cQString  csDbFieldName = _m_viDbItems.at(index)->dbFieldName();

    slot_photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//------------------------------------------------------------------------------
void
CAlbum::slot_photoMini_OnClicked(
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
            bool bRv = _m_pixPhoto.loadFromData(baPhoto);
            Q_ASSERT(bRv);

            _photoUpdate();
        }
    }
}
//------------------------------------------------------------------------------