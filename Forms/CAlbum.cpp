/**
 * \file   CAlbum.h
 * \brief  photo album
 */


#include "CAlbum.h"

#include "../QtLib/CUtils.h"
#include "../Classes/CIni.h"


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
    _tmModel        (a_tableModel),
    _ciDbRecordIndex(a_sqlNavigator->view()->currentIndex().row()),
    _viDbItems      (),
    _pixPhoto       ()
{
    qTEST(NULL != a_parent);
    qTEST(NULL != a_tableModel);
    qTEST(NULL != a_sqlNavigator);
    qTEST(- 1  <  _ciDbRecordIndex);

    _construct();

    CIni::get(this);
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
    qTEST(NULL != a_obj);
    qTEST(NULL != a_event);

    // clicks on photos
    if (a_event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(a_event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QLabel *label = static_cast<QLabel *>( a_obj );
            if (ui.cDbImage == label) {
                // ui.lblPhoto
                Q_EMIT sig_photo_clicked();
            } else {
                // other QLabels
                QLabel   *lblPhotoMini  = label;
                cQString  csDbFieldName = CDbImage::find(_viDbItems, lblPhotoMini)->dbFieldName();

                Q_EMIT sig_photoMini_clicked(lblPhotoMini, csDbFieldName);
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
    qTEST(NULL != a_event);
    Q_UNUSED(a_event);

    // set primary image
    {
        // get primary image index
        cint ciPrimaryIndex = _tmModel->record(_ciDbRecordIndex)
                                    .value(DB_F_PHOTOS_PRIMARY).toInt();

        // set primary image index
        {
            QLabel   *lblPhotoMini  = CDbImage::find(_viDbItems, ciPrimaryIndex);
            cQString  csDbFieldName = CDbImage::find(_viDbItems, ciPrimaryIndex)->dbFieldName();

            photoMini_onClicked(lblPhotoMini, csDbFieldName);
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
    qTEST(NULL != a_event);
    Q_UNUSED(a_event);

    // lblPhoto
    if (!_pixPhoto.isNull()) {
        QSize szScaled = _pixPhoto.size();

        szScaled.scale(ui.cDbImage->size(), Qt::KeepAspectRatio);

        if (NULL     == ui.cDbImage->pixmap() ||
            szScaled != ui.cDbImage->pixmap()->size())
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
    // addition UI shortcuts
    switch (a_event->key()) {
        // close on pressing escape
        case Qt::Key_Escape:
            actFile_onExit();
            break;
        // call editor by 'Enter'
        case Qt::Key_Enter:
            actEdit_onEdit();
            break;
        default:
            break;
    }

    QMainWindow::keyPressEvent(a_event);
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
CAlbum::_construct()
{
    _initMain();
    _initActions();
}
//------------------------------------------------------------------------------
void
CAlbum::_destruct()
{
    CIni::set(this);
}
//------------------------------------------------------------------------------
void
CAlbum::_initMain() {
    ui.setupUi(this);

    // main
    {
        setWindowFlags(Qt::Window);
    }

    // lblPhoto
    ui.cDbImage->installEventFilter(this);
    ui.cDbImage->setMinimumSize(PHOTO_MINI_SIZE);

    // _viDbItems
    {
        csize_t ciPhotoNum = PHOTO_NUM;

        struct SDbPhotoMini {
            CDbImage *label;
            cQString  field;
        };

        typedef const SDbPhotoMini cSDbPhotoMini;

        cSDbPhotoMini dbPhotoMinis[ciPhotoNum] = {
            { ui.cDbImage_2,  DB_F_PHOTOS_1  },
            { ui.cDbImage_3,  DB_F_PHOTOS_2  },
            { ui.cDbImage_4,  DB_F_PHOTOS_3  },
            { ui.cDbImage_5,  DB_F_PHOTOS_4  },
            { ui.cDbImage_6,  DB_F_PHOTOS_5  },
            { ui.cDbImage_7,  DB_F_PHOTOS_6  },
            { ui.cDbImage_8,  DB_F_PHOTOS_7  },
            { ui.cDbImage_9,  DB_F_PHOTOS_8  },
            { ui.cDbImage_10, DB_F_PHOTOS_9  },
            { ui.cDbImage_11, DB_F_PHOTOS_10 },
            { ui.cDbImage_12, DB_F_PHOTOS_11 },
            { ui.cDbImage_13, DB_F_PHOTOS_12 },
            { ui.cDbImage_14, DB_F_PHOTOS_13 },
            { ui.cDbImage_15, DB_F_PHOTOS_14 },
            { ui.cDbImage_16, DB_F_PHOTOS_15 }
        };

        // fill _viDbItems
        _viDbItems.reserve(ciPhotoNum);

        for (size_t i = 0; i < ciPhotoNum; ++ i) {
            dbPhotoMinis[i].label->construct(
                                        this,
                                        _tmModel,
                                        dbPhotoMinis[i].field,
                                        i,
                                        _ciDbRecordIndex,
                                        PHOTO_MINI_SIZE,
                                        NULL);

            dbPhotoMinis[i].label->installEventFilter(this);

            connect(dbPhotoMinis[i].label, &CDbImage::sig_dataChanged,
                    this, &CAlbum::photoMini_onUpdate);
            connect(this, &CAlbum::sig_photoMini_clicked,
                    this, &CAlbum::photoMini_onClicked);

            _viDbItems.push_back(dbPhotoMinis[i].label);
        }
    }

    // slots
    {
        connect(this, &CAlbum::sig_photo_clicked,
                this, &CAlbum::photo_onLoop);
    }

    // HACK: for ui.saPhotosMini->sizePolicy() == Fixed
    qApp->processEvents();
}
//------------------------------------------------------------------------------
void
CAlbum::_initActions()
{
    // group "File"
    {
        connect(ui.actFile_Exit,       &QAction::triggered,
                this,                  &CAlbum::actFile_onExit);
    }

    // group "Edit"
    {
        connect(ui.actEdit_SaveAs,     &QAction::triggered,
                this,                  &CAlbum::actEdit_onSaveAs);
        connect(ui.actEdit_First,      &QAction::triggered,
                this,                  &CAlbum::actEdit_onFirst);
        connect(ui.actEdit_Prior,      &QAction::triggered,
                this,                  &CAlbum::actEdit_onPrior);
        connect(ui.actEdit_Next,       &QAction::triggered,
                this,                  &CAlbum::actEdit_onNext);
        connect(ui.actEdit_Last,       &QAction::triggered,
                this,                  &CAlbum::actEdit_onLast);
        connect(ui.actEdit_GoTo,       &QAction::triggered,
                this,                  &CAlbum::actEdit_onGoTo);
        connect(ui.actEdit_Insert,     &QAction::triggered,
                this,                  &CAlbum::actEdit_onInsert);
        connect(ui.actEdit_Delete,     &QAction::triggered,
                this,                  &CAlbum::actEdit_onRemove);
        connect(ui.actEdit_Edit,       &QAction::triggered,
                this,                  &CAlbum::actEdit_onEdit);
        connect(ui.actEdit_SetPrimary, &QAction::triggered,
                this,                  &CAlbum::actEdit_onSetPrimary);
    }
}
//------------------------------------------------------------------------------
void
CAlbum::_photoUpdate()
{
    qTEST(!_pixPhoto.isNull());

#if TEM_DISABLE
    cQSize  cszSize   = QSize(ui.lblPhoto->width()  - PHOTO_MARGIN,
                              ui.lblPhoto->height() - PHOTO_MARGIN);
    QPixmap pixScaled = _pixPhoto.scaled(
                              cszSize,
                              Qt::KeepAspectRatio,
                              Qt::FastTransformation);

    ui.lblPhoto->setPixmap(pixScaled);
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "File"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CAlbum::actFile_onExit()
{
    close();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   group "Edit"
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CAlbum::actEdit_onSaveAs()
{
    CDbImage::currentDbImageLabel->saveToFile();
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onFirst()
{
    cint currentIndex = 0;

    photoMini_onUpdate(currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onPrior()
{
    if (0 >= CDbImage::currentIndex) {
        CDbImage::currentIndex = 0;
    } else {
        -- CDbImage::currentIndex;
    }

    photoMini_onUpdate(CDbImage::currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onNext() {
    if (CDbImage::currentIndex >= _viDbItems.size() - 1) {
        CDbImage::currentIndex = _viDbItems.size() - 1;
    } else {
        ++ CDbImage::currentIndex;
    }

    photoMini_onUpdate(CDbImage::currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onLast()
{
    cint currentIndex = _viDbItems.size() - 1;

    photoMini_onUpdate(currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onGoTo()
{
    cint ciMinValue   = 1;
    cint ciMaxValue   = _viDbItems.size();

    cint currentIndex = QInputDialog::getInt(
                                this,
                                APP_NAME, tr("Go to photo:"),
                                CDbImage::currentIndex + 1,
                                ciMinValue, ciMaxValue) - 1;

    photoMini_onUpdate(currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onInsert()
{
    CDbImage::currentDbImageLabel->loadFromFile();
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onRemove()
{
    CDbImage::currentDbImageLabel->remove();
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onEdit()
{
    CDbImage::currentDbImageLabel->loadFromFile();
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onSetPrimary()
{
    // write to DB
    QSqlRecord srRecord = _tmModel->record(_ciDbRecordIndex);
    srRecord.setValue(DB_F_PHOTOS_PRIMARY, CDbImage::currentIndex);

    _tmModel->setRecord(_ciDbRecordIndex, srRecord);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   photo
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CAlbum::photo_onLoop()
{
    // avoid recursion when photo album is empty
    qCHECK_DO(CDbImage::isEmpty(_viDbItems), return);

    // calc current index
    if (CDbImage::currentIndex >= _viDbItems.size() - 1) {
        CDbImage::currentIndex = 0;
    } else {
        ++ CDbImage::currentIndex;
    }

    // skip empty images
    if (_viDbItems.at(CDbImage::currentIndex)->isEmpty()) {
        photo_onLoop();
    }

    photoMini_onUpdate(CDbImage::currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::photoMini_onUpdate(
    cint &index
)
{
    CDbImage *lblPhotoMini  = _viDbItems.at(index);
    cQString  csDbFieldName = _viDbItems.at(index)->dbFieldName();

    photoMini_onClicked(lblPhotoMini, csDbFieldName);
}
//------------------------------------------------------------------------------
void
CAlbum::photoMini_onClicked(
    QLabel   *a_label,
    cQString &a_dbFieldName
)
{
    qTEST(NULL != a_label);
    qTEST(!a_dbFieldName.isEmpty());

    // lblPhotoMini
    {
        // set border
        Q_FOREACH (CDbImage *i, _viDbItems) {
            if (a_label == i) {
                // set current indexes
                CDbImage::currentIndex        = i->index();
                CDbImage::currentDbImageLabel = i;

                i->setFrameShape(QFrame::WinPanel);
            } else {
                i->setFrameShape(QFrame::Box);
            }
        }
    }

    // lblPhoto
    {
        cQByteArray baPhoto = _tmModel->record(_ciDbRecordIndex)
                                    .value(a_dbFieldName).toByteArray();

        if (baPhoto.isEmpty()) {
            ui.cDbImage->setText(TEXT_NO_PHOTO);
        } else {
            bool bRv = _pixPhoto.loadFromData(baPhoto);
            qTEST(bRv);

            _photoUpdate();
        }
    }
}
//------------------------------------------------------------------------------
