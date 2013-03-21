/**
 * \file   CDbImageLabel.cpp
 * \brief  DB image label
 */


#include "CDbImageLabel.h"
#include "../Classes/CDelegateDbImage.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CDbImageLabel::CDbImageLabel(
    QWidget        *a_parent,           ///< parent QWidget
    QSqlTableModel *a_tableModel,       ///< QSqlTableModel
    cQString       &a_dbFieldName,      ///< DB field name
    cint           &a_index,            ///< index
    cint           &a_dbRecordIndex,    ///< DB record index
    QLabel         *a_label,            ///< QLabel for display image
    cQSize         &a_size              ///< image sizes
) :
    QObject           (a_parent),
    _m_wdParent       (a_parent),
    _m_tmModel        (a_tableModel),
    _m_csDbFieldName  (a_dbFieldName),
    _m_ciIndex        (a_index),
    _m_ciDbRecordIndex(a_dbRecordIndex),
    _m_lblLabel       (a_label),
    _m_cszSize        (a_size),
    _m_dmMapper       (NULL),
    _m_baBuffer       ()
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(NULL != a_tableModel);
    Q_ASSERT(!a_dbFieldName.isEmpty());
    Q_ASSERT(- 1 < a_index);
    Q_ASSERT(- 1 < a_dbRecordIndex);
    Q_ASSERT(NULL != a_label);

    _m_dmMapper = _map();
}
//------------------------------------------------------------------------------
CDbImageLabel::~CDbImageLabel() {

}
//------------------------------------------------------------------------------


/*******************************************************************************
*   public, data
*
*******************************************************************************/

//------------------------------------------------------------------------------
cQString &
CDbImageLabel::dbFieldName() const {
    Q_ASSERT(!_m_csDbFieldName.isEmpty());

    return _m_csDbFieldName;
}
//------------------------------------------------------------------------------
cint &
CDbImageLabel::index() const {
    Q_ASSERT(- 1 < _m_ciIndex);

    return _m_ciIndex;
}
//------------------------------------------------------------------------------
cint &
CDbImageLabel::dbRecordIndex() const {
    Q_ASSERT(- 1 < _m_ciDbRecordIndex);

    return _m_ciDbRecordIndex;
}
//------------------------------------------------------------------------------
QLabel *
CDbImageLabel::label() const {
    Q_ASSERT(NULL != _m_lblLabel);

    return _m_lblLabel;
}
//------------------------------------------------------------------------------
cQSize &
CDbImageLabel::size() const {
    Q_ASSERT(_m_cszSize.isValid());

    return _m_cszSize;
}
//------------------------------------------------------------------------------
QDataWidgetMapper *
CDbImageLabel::map() {
    Q_ASSERT(NULL != _m_dmMapper);

    return _m_dmMapper;
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   public, actions
*
*******************************************************************************/

//------------------------------------------------------------------------------
bool
CDbImageLabel::isEmpty() const {
    qCHECK_RET(label()->pixmap() == NULL,   true);
    qCHECK_RET(label()->pixmap()->isNull(), true);

    return false;
}
//------------------------------------------------------------------------------
void
CDbImageLabel::loadFromFile() {
    QFileDialog fdlgDialog(_m_wdParent);

    fdlgDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fdlgDialog.setFileMode(QFileDialog::AnyFile);

    QStringList slFilters;

    slFilters << "Image files (" IMAGE_FORMATS ")";
    slFilters << "All   files (*)";

    fdlgDialog.setNameFilters(slFilters);
    fdlgDialog.setDirectory( QDir() );

    cint ciRv = fdlgDialog.exec();
    switch (ciRv) {
        case QDialog::Accepted:
            _loadFromFile( fdlgDialog.selectedFiles().first() );
            break;
        case QDialog::Rejected:
        default:
            break;
    }

    emit signal_DataChanged( index() );
}
//------------------------------------------------------------------------------
void
CDbImageLabel::saveToFile() {
    QFileDialog fdlgDialog(_m_wdParent);

    fdlgDialog.setAcceptMode(QFileDialog::AcceptSave);
    fdlgDialog.setFileMode(QFileDialog::AnyFile);
    // fdlgDialog.selectFile( QFileInfo(psbtnParent->filePath()).baseName() );
    // fdlgDialog.setDefaultSuffix(SHORTCUT_EXT);

    cint ciRv = fdlgDialog.exec();
    switch (ciRv) {
        case QDialog::Accepted:
            _saveToFile( fdlgDialog.selectedFiles().first() );
            break;
        case QDialog::Rejected:
        default:
            break;
    }
}
//------------------------------------------------------------------------------
void
CDbImageLabel::remove() {
    QMessageBox msgBox;

    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(tr("Removing image."));
    msgBox.setInformativeText(tr("Do you want to remove image?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    cint ciRv = msgBox.exec();
    switch (ciRv) {
        case QMessageBox::Yes:
            _remove();
            break;
        case QMessageBox::Cancel:
        default:
            break;
    }

    emit signal_DataChanged( index() );
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   public, static
*
*******************************************************************************/

//------------------------------------------------------------------------------
int            CDbImageLabel::currentIndex         = - 1;
CDbImageLabel *CDbImageLabel::currentDbImageLabel  = NULL;
//------------------------------------------------------------------------------
/* static */
CDbImageLabel *
CDbImageLabel::find(
    cdb_images_t &a_dbItems,
    const QLabel *a_label
)
{
    Q_ASSERT(!a_dbItems.empty());
    Q_ASSERT(NULL != a_label);

    foreach (CDbImageLabel *item, a_dbItems) {
        if (a_label == item->label()) {
            return item;
        }
    }

    return NULL;
}
//------------------------------------------------------------------------------
/* static */
CDbImageLabel *
CDbImageLabel::find(
    cdb_images_t &a_dbItems,
    cint         &a_index
)
{
    Q_ASSERT(!a_dbItems.empty());
    Q_ASSERT(- 1 < a_index);

    foreach (CDbImageLabel *item, a_dbItems) {
        if (a_index == item->index()) {
            return item;
        }
    }

    return NULL;
}
//------------------------------------------------------------------------------
/* static */
bool
CDbImageLabel::isLabelsEmpty(
    cdb_images_t &a_dbItems
)
{
    // a_dbItems - n/a

    foreach (CDbImageLabel *item, a_dbItems) {
        if (NULL != item->label()->pixmap()) {
            return true;
        }
    }

    return false;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
QDataWidgetMapper *
CDbImageLabel::_map() {
    QDataWidgetMapper *wmRv = new QDataWidgetMapper(this);
    wmRv->setModel(_m_tmModel);
    wmRv->setItemDelegate(new CDelegateDbImage(
                                wmRv,
                                _m_tmModel->fieldIndex( dbFieldName() ),
                                size(),
                                NULL));
    wmRv->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    wmRv->addMapping(label(), _m_tmModel->fieldIndex( dbFieldName() ));
    wmRv->setCurrentIndex( dbRecordIndex() );

    return wmRv;
}
//------------------------------------------------------------------------------
void
CDbImageLabel::_loadFromFile(
    cQString &a_filePath   ///< image file path
)
{
    Q_ASSERT(!a_filePath.isEmpty());

    // TODO: ensure rewrite image

    _m_baBuffer.clear();

    // file to buffer
    {
        if (IMAGE_IS_CONVERT) {
            CUtils::imageConvert(a_filePath, &_m_baBuffer);
        } else {
            QFile file(a_filePath);

            bool bRv = file.open(QIODevice::ReadOnly);
            Q_ASSERT(bRv);

            _m_baBuffer = file.readAll();
        }

        Q_ASSERT(!_m_baBuffer.isEmpty());
    }

    // _m_lblLabel
    {
        if (_m_baBuffer.isEmpty()) {
            _m_lblLabel->setText(TEXT_NO_PHOTO);
        } else {
            QPixmap pixOriginal;

            bool bRv = pixOriginal.loadFromData(_m_baBuffer);
            Q_ASSERT(bRv);

            QPixmap pixScaled = pixOriginal.scaled(
                                        size(),
                                        Qt::KeepAspectRatio,
                                        Qt::FastTransformation);

            _m_lblLabel->setPixmap(pixScaled);
        }
    }

    _flush();
}
//------------------------------------------------------------------------------
void
CDbImageLabel::_saveToFile(
    cQString &a_filePath   ///< image file path
)
{
    Q_ASSERT(!a_filePath.isEmpty());

    cQByteArray baImage = _m_tmModel->record( dbRecordIndex() )
                            .value(_m_csDbFieldName).toByteArray();

    QFile file(a_filePath);
    bool bRv = file.open(QIODevice::WriteOnly);
    Q_ASSERT(bRv);

    QDataStream stream(&file);
    cint ciRv = stream.writeRawData(baImage.constData(), baImage.size());
    Q_ASSERT(ciRv == baImage.size());
}
//------------------------------------------------------------------------------
void
CDbImageLabel::_remove() {
    _m_baBuffer.clear();
    _flush();
    _m_lblLabel->clear();
}
//------------------------------------------------------------------------------
void
CDbImageLabel::_flush() {
#if 0
    #error "BUG: QSqlTableModel::setRecord - not work"

    QSqlRecord srRecord = _m_tmModel->record( dbRecordIndex() );
    srRecord.setValue(dbFieldName(), _m_baBuffer);

    bool bRv = _m_tmModel->setRecord(dbRecordIndex(), srRecord);
    Q_ASSERT(bRv);
#else
    cint              column = _m_tmModel->fieldIndex( dbFieldName() );
    Q_ASSERT(- 1 < column);
    const QModelIndex index  = _m_tmModel->index(dbRecordIndex(), column);

    bool bRv = _m_tmModel->setData(index, _m_baBuffer);
    Q_ASSERT(bRv);
#endif

    _m_baBuffer.clear();
}
//------------------------------------------------------------------------------
