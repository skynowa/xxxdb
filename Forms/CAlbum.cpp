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
            CDbImage *dbPhotoMini = _viDbItems.find(ciPrimaryIndex);

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
        szScaled.scale(ui.dbPhoto->geometry(), Qt::KeepAspectRatio);

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
        _viDbItems.get().reserve(PHOTO_NUM);

        for (size_t i = 0; i < PHOTO_NUM; ++ i) {
            dbPhotoMinis[i].dbPhoto->construct(this, _tmModel,
                dbPhotoMinis[i].field, i, _ciDbRecordIndex, PHOTO_MINI_SIZE);
            dbPhotoMinis[i].dbPhoto->setFixedSize(PHOTO_MINI_SIZE);
            connect(dbPhotoMinis[i].dbPhoto, &CDbImage::sig_dataChanged,
                    this,                    &CAlbum::photoMini_onUpdate);
            connect(dbPhotoMinis[i].dbPhoto, &CDbImage::sig_pressed,
                    this,                    &CAlbum::photoMini_onClicked);

            _viDbItems.get().push_back(dbPhotoMinis[i].dbPhoto);
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
    _viDbItems.currentItem->saveToFile();
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
    if (0 >= _viDbItems.currentIndex) {
        _viDbItems.currentIndex = 0;
    } else {
        -- _viDbItems.currentIndex;
    }

    photoMini_onUpdate(_viDbItems.currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onNext() {
    if (_viDbItems.currentIndex >= _viDbItems.get().size() - 1) {
        _viDbItems.currentIndex = _viDbItems.get().size() - 1;
    } else {
        ++ _viDbItems.currentIndex;
    }

    photoMini_onUpdate(_viDbItems.currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onLast()
{
    cint currentIndex = _viDbItems.get().size() - 1;

    photoMini_onUpdate(currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onGoTo()
{
    cint ciMinValue   = 1;
    cint ciMaxValue   = _viDbItems.get().size();

    cint currentIndex = QInputDialog::getInt(
                                this,
                                APP_NAME, tr("Go to photo:"),
                                _viDbItems.currentIndex + 1,
                                ciMinValue, ciMaxValue) - 1;

    photoMini_onUpdate(currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onInsert()
{
    _viDbItems.currentItem->loadFromFile();
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onRemove()
{
    _viDbItems.currentItem->remove();
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onEdit()
{
    _viDbItems.currentItem->loadFromFile();
}
//------------------------------------------------------------------------------
void
CAlbum::actEdit_onSetPrimary()
{
    // write to DB
    QSqlRecord srRecord = _tmModel->record(_ciDbRecordIndex);
    srRecord.setValue(DB_F_PHOTOS_PRIMARY, _viDbItems.currentIndex);

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
    qCHECK_DO(_viDbItems.isEmpty(), return);

    // calc current index
    if (_viDbItems.currentIndex >= _viDbItems.get().size() - 1) {
        _viDbItems.currentIndex = 0;
    } else {
        ++ _viDbItems.currentIndex;
    }

    // skip empty images
    if (_viDbItems.get().at(_viDbItems.currentIndex)->isEmpty()) {
        photo_onLoop();
    }

    photoMini_onUpdate(_viDbItems.currentIndex);
}
//------------------------------------------------------------------------------
void
CAlbum::photoMini_onUpdate(
    cint &a_index
)
{
    CDbImage *dbPhotoMini = _viDbItems.get().at(a_index);

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
        Q_FOREACH (CDbImage *it_item, _viDbItems.get()) {
            if (dbPhoto == it_item) {
                // set current indexes
                _viDbItems.currentIndex = it_item->index();
                _viDbItems.currentItem  = it_item;

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
