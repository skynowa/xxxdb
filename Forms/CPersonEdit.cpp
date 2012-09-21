/**
 * \file   CPersonEdit.h
 * \brief  edit person data
 */


#include "CPersonEdit.h"


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CPersonEdit::CPersonEdit(
    QWidget        *parent,
    QSqlTableModel *tableModel,
    const int      &currentRow
) :
    QDialog        (parent),
    _m_tmModel     (tableModel),
    _m_ciCurrentRow(currentRow)
{
    Q_ASSERT(NULL != _m_tmModel);
    Q_ASSERT(- 1  <  _m_ciCurrentRow);

    _construct();
}
//---------------------------------------------------------------------------
/*virtual*/
CPersonEdit::~CPersonEdit() {
    _destruct();
}
//---------------------------------------------------------------------------

/****************************************************************************
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPersonEdit::_construct() {
    _initMain();
}
//---------------------------------------------------------------------------
void
CPersonEdit::_destruct() {
    qDeleteAll(_m_ltwGroups);
}
//---------------------------------------------------------------------------
void
CPersonEdit::_initMain() {
    m_Ui.setupUi(this);

    // QTreeWidget
    {
        m_Ui.twGroups->setColumnCount(1);
        m_Ui.twGroups->setHeaderLabels(QStringList() << CONFIG_DATA_GROUP_HEADER);
        m_Ui.twGroups->setMinimumWidth(110);
        m_Ui.twGroups->setMaximumWidth(110);

        // top items
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_MAIN) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_PHONES) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_ADDRESS) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_EMAIL) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_WEB) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_MESSENGERS) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_JOB) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_STUDIES) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_DATES) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_INTERESTS) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_PERIODS) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_ETC) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_NOTE) );

        m_Ui.twGroups->addTopLevelItems(_m_ltwGroups);

        m_Ui.twGroups->expandAll();
        m_Ui.twGroups->resizeColumnToContents(0);
    }

    // tabwGroupsDetail
    {
        #if 0
            QTreeWidgetItem *item;

            QWidget *w = new QWidget(this);

            foreach(item, _m_ltwGroups) {
                m_Ui.tabwGroupsDetail->addTab(w, item->text(0));
            }
        #endif
    }

    // "Main" group
    {
        QSqlRecord srRecord = _m_tmModel->record(_m_ciCurrentRow);

        m_Ui.cboName->lineEdit()->setText( srRecord.value(CONFIG_DB_F_MAIN_NAME).toString() );
        m_Ui.cboAge->lineEdit()->setText ( srRecord.value(CONFIG_DB_F_MAIN_AGE ).toString() );


        // m_Ui.lblPhoto
        {
            QImage imgPhoto;
            imgPhoto.loadFromData( srRecord.value(CONFIG_DB_F_MAIN_AGE ).toByteArray() );

            QImage  img1   = imgPhoto.scaled(QSize(120 * 2, 90 * 2), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            QPixmap pixmap = QPixmap::fromImage(img1);

            m_Ui.lblPhoto->setPixmap(pixmap);
            // m_Ui.lblPhoto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }

        // lblPhoto
        {
            const int  ciCurrentRow = _m_ciCurrentRow;
            QByteArray baPhoto      = _m_tmModel->record(ciCurrentRow).value(CONFIG_DB_F_PHOTO_1).toByteArray();

            if (0 >= baPhoto.size()) {
                // TODO: show "empty" photo
                m_Ui.lblPhoto->clear();
            } else {
                QImage imgPhoto;

                bool bRv = imgPhoto.loadFromData(baPhoto);
                Q_ASSERT(true == bRv);

                QImage  imgPhotoScaled = imgPhoto.scaled(QSize(CONFIG_PHOTO_WIDTH, CONFIG_PHOTO_HEIGHT), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                QPixmap pixPixmap      = QPixmap::fromImage(imgPhotoScaled);

                m_Ui.lblPhoto->setPixmap(pixPixmap);
            }
        }
    }

    // signals
    {
        connect(m_Ui.tbtnPhotoChange, SIGNAL( clicked() ),
                this,                 SLOT  ( slot_tbtnPhotoChange_OnClicked() ));
        connect(m_Ui.tbtnPhotoDelete, SIGNAL( clicked() ),
                this,                 SLOT  ( slot_tbtnPhotoDelete_OnClicked() ));
        connect(m_Ui.tbtnPhotoSaveAs, SIGNAL( clicked() ),
                this,                 SLOT  ( slot_tbtnPhotoSaveAs_OnClicked() ));

        connect(m_Ui.bbxButtons,      SIGNAL( clicked(QAbstractButton *) ),
                this,                 SLOT  ( slot_bbxButtons_OnClicked(QAbstractButton *) ));
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private slots
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPersonEdit::slot_tbtnPhotoChange_OnClicked() {
    QFileDialog fdlgDialog(this);

    fdlgDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fdlgDialog.setFileMode(QFileDialog::AnyFile);

    QStringList slFilters;

    slFilters << "Images (*.png *.xpm *.jpg *.jpeg *.bmp)";
#if defined(Q_WS_WIN)
    slFilters << "All files (*)";
#else
    slFilters << "All files (*)";
#endif

    fdlgDialog.setNameFilters(slFilters);
    //fdlgDialog.setDirectory();

    QDialog::DialogCode dcRes = static_cast<QDialog::DialogCode>( fdlgDialog.exec() );
    switch (dcRes) {
        case QDialog::Rejected: {
                // n/a
            }
            break;

        case QDialog::Accepted: {
                QString sFilePath = fdlgDialog.selectedFiles().first();

                QFile file(sFilePath);

                bool bRv = file.open(QIODevice::ReadOnly);
                Q_ASSERT(true == bRv);

                _m_baPhoto = file.readAll();

            }
            break;

        default: {
                Q_ASSERT(false);
            }
            break;
    }
}
//---------------------------------------------------------------------------
void
CPersonEdit::slot_tbtnPhotoDelete_OnClicked() {
    QSqlRecord srRecord = _m_tmModel->record(_m_ciCurrentRow);

    srRecord.setValue(CONFIG_DB_F_PHOTO_1, _m_baPhoto);
    _m_baPhoto.clear();

    _m_tmModel->setRecord(_m_ciCurrentRow, srRecord);
    _m_tmModel->submitAll();
}
//---------------------------------------------------------------------------
void
CPersonEdit::slot_tbtnPhotoSaveAs_OnClicked() {
    QFileDialog fdlgDialog(this);

    fdlgDialog.setAcceptMode(QFileDialog::AcceptSave);
    fdlgDialog.setFileMode(QFileDialog::AnyFile);
    //fdlgDialog.selectFile( QFileInfo(psbtnParent->filePath()).baseName() );
    //fdlgDialog.setDefaultSuffix(CONFIG_SHORTCUT_EXT);

    QDialog::DialogCode dcRes = static_cast<QDialog::DialogCode>( fdlgDialog.exec() );
    switch (dcRes) {
        case QDialog::Rejected: {
                // n/a;
            }
            break;

        case QDialog::Accepted: {
                QString    sFilePath = fdlgDialog.selectedFiles().first();
                QByteArray baPhoto   = _m_tmModel->record(_m_ciCurrentRow).value(CONFIG_DB_F_PHOTO_1).toByteArray();

                QFile  file(sFilePath);
                bool bRv = file.open(QIODevice::WriteOnly);
                Q_ASSERT(true == bRv);

                QDataStream stream(&file);
                int iRv = stream.writeRawData( baPhoto.constData(), baPhoto.size() );
                Q_ASSERT(0 < iRv);
            }
            break;

        default: {
                Q_ASSERT(false);
            }
            break;
    }
}
//---------------------------------------------------------------------------
void
CPersonEdit::slot_bbxButtons_OnClicked(
    QAbstractButton *button
)
{
    QDialogButtonBox::StandardButton sbType = m_Ui.bbxButtons->standardButton(button);
    switch (sbType) {
        case QDialogButtonBox::Reset: {
                _resetAll();
            }
            break;

        case QDialogButtonBox::Ok: {
                _saveAll();
                close();
            }
            break;

        case QDialogButtonBox::Cancel: {
                close();
            }
            break;

        case QDialogButtonBox::Apply: {
                _saveAll();
            }
            break;

        default: {
                Q_ASSERT(false);
            }
            break;
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private slots
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPersonEdit::_resetAll() {
    m_Ui.cboName->lineEdit()->clear();
    m_Ui.cboAge->lineEdit()->clear();
}
//---------------------------------------------------------------------------
void
CPersonEdit::_saveAll() {
    QSqlRecord srRecord = _m_tmModel->record(_m_ciCurrentRow);

    {
        srRecord.setValue(CONFIG_DB_F_MAIN_NAME, m_Ui.cboName->lineEdit()->text());
        srRecord.setValue(CONFIG_DB_F_MAIN_AGE,  m_Ui.cboAge->lineEdit()->text() );

        if (0 < _m_baPhoto.size()) {
            srRecord.setValue(CONFIG_DB_F_PHOTO_1, _m_baPhoto);
            _m_baPhoto.clear();
        }
    }

    _m_tmModel->setRecord(_m_ciCurrentRow, srRecord);
    _m_tmModel->submitAll();
}
//---------------------------------------------------------------------------












