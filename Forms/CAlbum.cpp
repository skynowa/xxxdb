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
            CDbImage *dbPhotoMini = CDbImage::find(_viDbItems, ciPrimaryIndex);

            photoMini_onClicked(dbPhotoMini);
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

    // ui.dbPhoto
    if (!_pixPhoto.isNull()) {
        QSize szScaled = _pixPhoto.size();

        szScaled.scale(ui.dbPhoto->size(), Qt::KeepAspectRatio);

        if (NULL     == ui.dbPhoto->pixmap() ||
            szScaled != ui.dbPhoto->pixmap()->size())
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

    // ui.dbPhoto
    ui.dbPhoto->construct(this, _tmModel, DB_F_PHOTOS_1, 1, _ciDbRecordIndex,
                          PHOTO_SIZE);
    ui.dbPhoto->setMinimumSize(PHOTO_MINI_SIZE);
    connect(ui.dbPhoto, &CDbImage::sig_pressed,
            this,       &CAlbum::photo_onLoop);

    // _viDbItems
    {
        struct SDbPhotoMini {
            CDbImage *dbPhoto;
            cQString  field;
        };
        typedef const SDbPhotoMini cdb_photo_mini_t;

        cdb_photo_mini_t dbPhotoMinis[PHOTO_NUM] = {
            { ui.dbPhoto_1,  DB_F_PHOTOS_1  },
            { ui.dbPhoto_2,  DB_F_PHOTOS_2  },
            { ui.dbPhoto_3,  DB_F_PHOTOS_3  },
            { ui.dbPhoto_4,  DB_F_PHOTOS_4  },
            { ui.dbPhoto_5,  DB_F_PHOTOS_5  },
            { ui.dbPhoto_6,  DB_F_PHOTOS_6  },
            { ui.dbPhoto_7,  DB_F_PHOTOS_7  },
            { ui.dbPhoto_8,  DB_F_PHOTOS_8  },
            { ui.dbPhoto_9,  DB_F_PHOTOS_9  },
            { ui.dbPhoto_10, DB_F_PHOTOS_10 },
            { ui.dbPhoto_11, DB_F_PHOTOS_11 },
            { ui.dbPhoto_12, DB_F_PHOTOS_12 },
            { ui.dbPhoto_13, DB_F_PHOTOS_13 },
            { ui.dbPhoto_14, DB_F_PHOTOS_14 },
            { ui.dbPhoto_15, DB_F_PHOTOS_15 }
        };

        // fill _viDbItems
        _viDbItems.reserve(PHOTO_NUM);

        for (size_t i = 0; i < PHOTO_NUM; ++ i) {
            dbPhotoMinis[i].dbPhoto->construct(this, _tmModel,
                dbPhotoMinis[i].field, i, _ciDbRecordIndex, PHOTO_MINI_SIZE);
            dbPhotoMinis[i].dbPhoto->setFixedSize(PHOTO_MINI_SIZE);
            connect(dbPhotoMinis[i].dbPhoto, &CDbImage::sig_dataChanged,
                    this,                    &CAlbum::photoMini_onUpdate);
            connect(dbPhotoMinis[i].dbPhoto, &CDbImage::sig_pressed,
                    this,                    &CAlbum::photoMini_onClicked);

            _viDbItems.push_back(dbPhotoMinis[i].dbPhoto);
        }
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

    cQSize  cszSize   = QSize(ui.dbPhoto->width()  - PHOTO_MARGIN,
                              ui.dbPhoto->height() - PHOTO_MARGIN);
    QPixmap pixScaled = _pixPhoto.scaled(
                              cszSize,
                              Qt::KeepAspectRatio,
                              Qt::FastTransformation);

    ui.dbPhoto->setPixmap(pixScaled);
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
    cint &a_index
)
{
    CDbImage *dbPhotoMini = _viDbItems.at(a_index);

    photoMini_onClicked(dbPhotoMini);
}
//------------------------------------------------------------------------------
void
CAlbum::photoMini_onClicked(
    QObject *a_sender
)
{
    qTEST(NULL != a_sender);

    CDbImage *dbPhoto = static_cast<CDbImage *>(a_sender);

    // dbPhotoMini
    {
        // set border
        Q_FOREACH (CDbImage *it_item, _viDbItems) {
            if (dbPhoto == it_item) {
                // set current indexes
                CDbImage::currentIndex        = it_item->index();
                CDbImage::currentDbImageLabel = it_item;

                it_item->setFrameShape(QFrame::WinPanel);
            } else {
                it_item->setFrameShape(QFrame::Box);
            }
        }
    }

    // ui.dbPhoto
    {
        cQString csDbFieldName = dbPhoto->dbFieldName();

        cQByteArray baPhoto = _tmModel->record(_ciDbRecordIndex)
                                    .value(csDbFieldName).toByteArray();

        if (baPhoto.isEmpty()) {
            ui.dbPhoto->setTextDefault();
        } else {
            bool bRv = _pixPhoto.loadFromData(baPhoto);
            qTEST(bRv);

            _photoUpdate();
        }
    }
}
//------------------------------------------------------------------------------
