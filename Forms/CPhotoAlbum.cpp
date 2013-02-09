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
    QMainWindow                (a_parent),
    _m_tmModel                 (a_tableModel),
    _m_ciCurrentRow            (a_currentRow),
    _m_hsDbControls            (),
    _m_iDBControls_CurrentIndex(0),
    _m_dbImage_1               (NULL)

{
    Q_ASSERT(NULL != _m_tmModel);
    Q_ASSERT(- 1   < _m_ciCurrentRow);

    _construct();
}
//---------------------------------------------------------------------------
/* virtual */
CPhotoAlbum::~CPhotoAlbum() {
    _destruct();

    delete this;
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
        QLabel        *lblPhotoMini  = static_cast<QLabel *>( a_obj );
        const QString  csDbFieldName = _m_hsDbControls[lblPhotoMini];

        photoMini_OnClicked(lblPhotoMini, csDbFieldName);

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
    Q_ASSERT(NULL  != a_label);
    Q_ASSERT(false == a_dbFieldName.isEmpty());

    // lblPhotoMini
    {
        // set border
        foreach (QLabel *key, _m_hsDbControls.keys()) {
            if (a_label == key) {
                // current index
                _m_iDBControls_CurrentIndex = _m_hsDbControls.keys().indexOf(key);

                key->setFrameShape(QFrame::WinPanel);
            } else {
                key->setFrameShape(QFrame::Box);
            }
        }
    }

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
    _initActions();
}
//---------------------------------------------------------------------------
void
CPhotoAlbum::_destruct() {

}
//---------------------------------------------------------------------------
void
CPhotoAlbum::_initMain() {
    m_Ui.setupUi(this);

    setWindowFlags(Qt::Window);

    // _m_hsDbControls
    {
        _m_hsDbControls.insert(m_Ui.lblPhotoMini_1,  CONFIG_DB_F_PHOTOS_1);
        _m_hsDbControls.insert(m_Ui.lblPhotoMini_2,  CONFIG_DB_F_PHOTOS_2);
        _m_hsDbControls.insert(m_Ui.lblPhotoMini_3,  CONFIG_DB_F_PHOTOS_3);
        _m_hsDbControls.insert(m_Ui.lblPhotoMini_4,  CONFIG_DB_F_PHOTOS_4);
        _m_hsDbControls.insert(m_Ui.lblPhotoMini_5,  CONFIG_DB_F_PHOTOS_5);
        _m_hsDbControls.insert(m_Ui.lblPhotoMini_6,  CONFIG_DB_F_PHOTOS_6);
        _m_hsDbControls.insert(m_Ui.lblPhotoMini_7,  CONFIG_DB_F_PHOTOS_7);
        _m_hsDbControls.insert(m_Ui.lblPhotoMini_8,  CONFIG_DB_F_PHOTOS_8);
        _m_hsDbControls.insert(m_Ui.lblPhotoMini_9,  CONFIG_DB_F_PHOTOS_9);
        _m_hsDbControls.insert(m_Ui.lblPhotoMini_10, CONFIG_DB_F_PHOTOS_10);
    }

    // map DB controls
    {
        db_controls_t::ConstIterator cit;

        for (cit = _m_hsDbControls.begin(); cit != _m_hsDbControls.end(); ++ cit) {
            QDataWidgetMapper *wmRv = _dbWidgetMap(cit.key(), cit.value(), CONFIG_PHOTO_MINI_SIZE);
            Q_ASSERT(NULL != wmRv);

            cit.key()->installEventFilter(this);
        }
    }

    // _m_dbImage
    {
        _m_dbImage_1 = new CDbImage(this, _m_tmModel, CONFIG_DB_F_PHOTOS_1,
                                  _m_ciCurrentRow, m_Ui.lblPhoto);
    }
}
//---------------------------------------------------------------------------
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


/****************************************************************************
*   group "File"
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnExit() {
    close();
}
//---------------------------------------------------------------------------


/****************************************************************************
*   group "Edit"
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnSaveAs() {
    _m_dbImage_1->saveToFile();
}
//---------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnFirst() {
    QLabel        *lblPhotoMini  = _m_hsDbControls.keys().first();
    const QString  csDbFieldName = _m_hsDbControls[lblPhotoMini];

    photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//---------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnPrior() {
    if (0 >= _m_iDBControls_CurrentIndex) {
        _m_iDBControls_CurrentIndex = 0;
    } else {
        -- _m_iDBControls_CurrentIndex;
    }

    QLabel        *lblPhotoMini  = _m_hsDbControls.keys().at(_m_iDBControls_CurrentIndex);
    const QString  csDbFieldName = _m_hsDbControls[lblPhotoMini];

    photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//---------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnNext() {
    if (_m_iDBControls_CurrentIndex >= _m_hsDbControls.keys().count() - 1) {
        _m_iDBControls_CurrentIndex = _m_hsDbControls.keys().count() - 1;
    } else {
        ++ _m_iDBControls_CurrentIndex;
    }

    QLabel        *lblPhotoMini  = _m_hsDbControls.keys().at(_m_iDBControls_CurrentIndex);
    const QString  csDbFieldName = _m_hsDbControls[lblPhotoMini];

    photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//---------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnLast() {
    QLabel        *lblPhotoMini  = _m_hsDbControls.keys().last();
    const QString  csDbFieldName = _m_hsDbControls[lblPhotoMini];

    photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//---------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnTo() {
    const int ciMinValue    = 1;
    const int ciMaxValue    = _m_hsDbControls.count();

    const int ciTargetIndex = QInputDialog::getInt(
                                    this, CONFIG_APP_NAME, "Go to photo:",
                                    _m_iDBControls_CurrentIndex + 1, ciMinValue, ciMaxValue) - 1;

    QLabel        *lblPhotoMini  = _m_hsDbControls.keys().at(ciTargetIndex);
    const QString  csDbFieldName = _m_hsDbControls[lblPhotoMini];

    photoMini_OnClicked(lblPhotoMini, csDbFieldName);
}
//---------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnInsert() {
    _m_dbImage_1->loadFromFile();
}
//---------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnRemove() {
    _m_dbImage_1->remove();
}
//---------------------------------------------------------------------------
void
CPhotoAlbum::slot_OnEdit() {
    _m_dbImage_1->loadFromFile();
}
//---------------------------------------------------------------------------

