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
    QMainWindow     (a_parent),
    _stApp          (NULL),
    _tmModel        (a_tableModel),
    _ciDbRecordIndex(a_sqlNavigator->view()->currentIndex().row()),
    _viDbItems      (),
    _pixPhoto       ()
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(NULL != a_tableModel);
    Q_ASSERT(NULL != a_sqlNavigator);
    Q_ASSERT(- 1  <  _ciDbRecordIndex);

    _construct();

    _stApp = new CSettings(NULL, NULL, this);
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
            if (ui.lblPhoto == label) {
                // ui.lblPhoto
                Q_EMIT signal_photo_clicked();
            } else {
                // other QLabels
                QLabel   *lblPhotoMini  = label;
                cQString  csDbFieldName = CDbImageLabel::find(_viDbItems, lblPhotoMini)->dbFieldName();

                Q_EMIT signal_photoMini_clicked(lblPhotoMini, csDbFieldName);
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
        cint ciPrimaryIndex = _tmModel->record(_ciDbRecordIndex)
                                    .value(DB_F_PHOTOS_PRIMARY).toInt();

        // set primary image index
        {
            QLabel   *lblPhotoMini  = CDbImageLabel::find(_viDbItems, ciPrimaryIndex)->label();
            cQString  csDbFieldName = CDbImageLabel::find(_viDbItems, ciPrimaryIndex)->dbFieldName();

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
    if (!_pixPhoto.isNull()) {
        QSize szScaled = _pixPhoto.size();

        szScaled.scale(ui.lblPhoto->size(), Qt::KeepAspectRatio);

        if (NULL     == ui.lblPhoto->pixmap() ||
            szScaled != ui.lblPhoto->pixmap()->size())
        {
            _photoUpdate();
        }
    }
}
//------------------------------------------------------------------------------
/* virtual */
void
CAlbum::keyPressEvent(
    QKeyEvent *a_event
)
{
    switch (a_event->key()) {
        // close on pressing escape
        case Qt::Key_Escape:
            slot_OnExit();
            break;
        default:
            QMainWindow::keyPressEvent(a_event);
            break;
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
    qPTR_DELETE(_stApp);
}
//------------------------------------------------------------------------------
void
CAlbum::_initMain() {
    ui.setupUi(this);

    // main
    {
        setWindowTitle(APP_PHOTO_ALBUM_TITLE);
        setWindowFlags(Qt::Window);
    }

    // lblPhoto
    ui.lblPhoto->installEventFilter(this);
    ui.lblPhoto->setMinimumSize(PHOTO_MINI_SIZE);

    // _viDbItems
    {
        csize_t ciPhotoNum = PHOTO_NUM;

        QLabel * photoMinis[ciPhotoNum] = {
            ui.lblPhotoMini_1,
            ui.lblPhotoMini_2,
            ui.lblPhotoMini_3,
            ui.lblPhotoMini_4,
            ui.lblPhotoMini_5,
            ui.lblPhotoMini_6,
            ui.lblPhotoMini_7,
            ui.lblPhotoMini_8,
            ui.lblPhotoMini_9,
            ui.lblPhotoMini_10
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

        Q_ASSERT(qARRAY_LENGTH(photoMinis) == qARRAY_LENGTH(dbFieldNames));

        // fill _viDbItems
        _viDbItems.reserve(ciPhotoNum);

        for (size_t i = 0; i < ciPhotoNum; ++ i) {
            CDbImageLabel *item = new CDbImageLabel(
                                        this,
                                        _tmModel,
                                        dbFieldNames[i],
                                        i,
                                        _ciDbRecordIndex,
                                        photoMinis[i], PHOTO_MINI_SIZE,
                                        NULL);

            photoMinis[i]->installEventFilter(this);

            connect(item, &CDbImageLabel::signal_DataChanged,
                    this, &CAlbum::slot_OnPhotoUpdate);
            connect(this, &CAlbum::signal_photoMini_clicked,
                    this, &CAlbum::slot_photoMini_OnClicked);

            _viDbItems.push_back(item);
        }
    }

    // slots
    {
        connect(this, &CAlbum::signal_photo_clicked,
                this, &CAlbum::slot_OnLoop);
    }

    // HACK: for ui.saPhotosMini->sizePolicy() == Fixed
    qApp->processEvents();
}
//------------------------------------------------------------------------------
void
CAlbum::_initActions() {
    // group "File"
    {
        connect(ui.actFile_Exit,       &QAction::triggered,
                this,                  &CAlbum::slot_OnExit);
    }

    // group "Edit"
    {
        connect(ui.actEdit_SaveAs,     &QAction::triggered,
                this,                  &CAlbum::slot_OnSaveAs);
        connect(ui.actEdit_First,      &QAction::triggered,
                this,                  &CAlbum::slot_OnFirst);
        connect(ui.actEdit_Prior,      &QAction::triggered,
                this,                  &CAlbum::slot_OnPrior);
        connect(ui.actEdit_Next,       &QAction::triggered,
                this,                  &CAlbum::slot_OnNext);
        connect(ui.actEdit_Last,       &QAction::triggered,
                this,                  &CAlbum::slot_OnLast);
        connect(ui.actEdit_GoTo,       &QAction::triggered,
                this,                  &CAlbum::slot_OnGoTo);
        connect(ui.actEdit_Insert,     &QAction::triggered,
                this,                  &CAlbum::slot_OnInsert);
        connect(ui.actEdit_Delete,     &QAction::triggered,
                this,                  &CAlbum::slot_OnRemove);
        connect(ui.actEdit_Edit,       &QAction::triggered,
                this,                  &CAlbum::slot_OnEdit);
        connect(ui.actEdit_SetPrimary, &QAction::triggered,
                this,                  &CAlbum::slot_OnSetPrimary);
    }
}
//------------------------------------------------------------------------------
void
CAlbum::_photoUpdate() {
    Q_ASSERT(!_pixPhoto.isNull());

    cQSize  cszSize   = QSize(ui.lblPhoto->width()  - PHOTO_MARGIN,
                              ui.lblPhoto->height() - PHOTO_MARGIN);
    QPixmap pixScaled = _pixPhoto.scaled(
                              cszSize,
                              Qt::KeepAspectRatio,
                              Qt::FastTransformation);

    ui.lblPhoto->setPixmap(pixScaled);
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
    if (CDbImageLabel::currentIndex >= _viDbItems.size() - 1) {
        CDbImageLabel::currentIndex = _viDbItems.size() - 1;
    } else {
        ++ CDbImageLabel::currentIndex;
    }

    slot_OnPhotoUpdate(CDbImageLabel::currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::slot_OnLast() {
    cint currentIndex = _viDbItems.size() - 1;

    slot_OnPhotoUpdate(currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::slot_OnGoTo() {
    cint ciMinValue   = 1;
    cint ciMaxValue   = _viDbItems.size();

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
    QSqlRecord srRecord = _tmModel->record(_ciDbRecordIndex);
    srRecord.setValue(DB_F_PHOTOS_PRIMARY, CDbImageLabel::currentIndex);

    _tmModel->setRecord(_ciDbRecordIndex, srRecord);
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
    qCHECK_DO(CDbImageLabel::isEmpty(_viDbItems), return);

    // calc current index
    if (CDbImageLabel::currentIndex >= _viDbItems.size() - 1) {
        CDbImageLabel::currentIndex = 0;
    } else {
        ++ CDbImageLabel::currentIndex;
    }

    // skip empty images
    if (_viDbItems.at(CDbImageLabel::currentIndex)->isEmpty()) {
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
    QLabel   *lblPhotoMini  = _viDbItems.at(index)->label();
    cQString  csDbFieldName = _viDbItems.at(index)->dbFieldName();

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
        Q_FOREACH (CDbImageLabel *i, _viDbItems) {
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
        cQByteArray baPhoto = _tmModel->record(_ciDbRecordIndex)
                                    .value(a_dbFieldName).toByteArray();

        if (baPhoto.isEmpty()) {
            ui.lblPhoto->setText(TEXT_NO_PHOTO);
        } else {
            bool bRv = _pixPhoto.loadFromData(baPhoto);
            Q_ASSERT(bRv);

            _photoUpdate();
        }
    }
}
//------------------------------------------------------------------------------
