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
    cQSize         &a_size,             ///< image sizes
    QLabel         *a_info              ///< QLabel for display image
) :
    QObject         (a_parent),
    _wdParent       (a_parent),
    _tmModel        (a_tableModel),
    _csDbFieldName  (a_dbFieldName),
    _ciIndex        (a_index),
    _ciDbRecordIndex(a_dbRecordIndex),
    _lblLabel       (a_label),
    _cszSize        (a_size),
    _lblInfo        (a_info),
    _dmMapper       (NULL),
    _baBuffer       ()
{
    Q_ASSERT(NULL != a_parent);
    Q_ASSERT(NULL != a_tableModel);
    Q_ASSERT(!a_dbFieldName.isEmpty());
    Q_ASSERT(- 1 < a_index);
    // a_dbRecordIndex - n/a
    Q_ASSERT(NULL != a_label);
    Q_ASSERT(a_size.isValid());
    // a_info - n/a

    _dmMapper = _map();
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
CDbImageLabel::dbFieldName() const
{
    Q_ASSERT(!_csDbFieldName.isEmpty());

    return _csDbFieldName;
}
//------------------------------------------------------------------------------
cint &
CDbImageLabel::index() const
{
    Q_ASSERT(- 1 < _ciIndex);

    return _ciIndex;
}
//------------------------------------------------------------------------------
cint &
CDbImageLabel::dbRecordIndex() const
{
    // _ciDbRecordIndex - n/a;

    return _ciDbRecordIndex;
}
//------------------------------------------------------------------------------
QLabel *
CDbImageLabel::label() const
{
    Q_ASSERT(NULL != _lblLabel);

    return _lblLabel;
}
//------------------------------------------------------------------------------
cQSize &
CDbImageLabel::size() const
{
    Q_ASSERT(_cszSize.isValid());

    return _cszSize;
}
//------------------------------------------------------------------------------
QLabel *
CDbImageLabel::info() const
{
    Q_ASSERT(NULL != _lblInfo);

    return _lblInfo;
}
//------------------------------------------------------------------------------
QDataWidgetMapper *
CDbImageLabel::mapper()
{
    Q_ASSERT(NULL != _dmMapper);

    return _dmMapper;
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   public, actions
*
*******************************************************************************/

//------------------------------------------------------------------------------
bool
CDbImageLabel::isEmpty() const
{
    qCHECK_RET(label()->pixmap() == NULL,   true);
    qCHECK_RET(label()->pixmap()->isNull(), true);

    return false;
}
//------------------------------------------------------------------------------
void
CDbImageLabel::loadFromFile()
{
    QFileDialog fdlgDialog(_wdParent);

    fdlgDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fdlgDialog.setFileMode(QFileDialog::AnyFile);

    QStringList slFilters;

    slFilters << "Image files (" IMAGE_FORMATS ")";
    slFilters << "All   files (*)";

    fdlgDialog.setNameFilters(slFilters);
    fdlgDialog.setDirectory( QDir::home() );

    cint ciRv = fdlgDialog.exec();
    switch (ciRv) {
        case QDialog::Accepted:
            _loadFromFile( fdlgDialog.selectedFiles().first() );
            break;
        case QDialog::Rejected:
            break;
        default:
            Q_ASSERT(false);
            break;
    }

    Q_EMIT sig_dataChanged( index() );
}
//------------------------------------------------------------------------------
void
CDbImageLabel::saveToFile()
{
    QFileDialog fdlgDialog(_wdParent);

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
            break;
        default:
            Q_ASSERT(false);
            break;
    }
}
//------------------------------------------------------------------------------
void
CDbImageLabel::remove()
{
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
            break;
        default:
            Q_ASSERT(false);
            break;
    }

    Q_EMIT sig_dataChanged( index() );
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

    Q_FOREACH (CDbImageLabel *item, a_dbItems) {
        qCHECK_RET(a_label == item->label(), item);
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

    Q_FOREACH (CDbImageLabel *item, a_dbItems) {
        qCHECK_RET(a_index == item->index(), item);
    }

    return NULL;
}
//------------------------------------------------------------------------------
/* static */
bool
CDbImageLabel::isEmpty(
    cdb_images_t &a_dbItems
)
{
    // a_dbItems - n/a

    Q_FOREACH (CDbImageLabel *item, a_dbItems) {
        qCHECK_RET(!item->isEmpty(), false);
    }

    return true;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
QDataWidgetMapper *
CDbImageLabel::_map()
{
    QDataWidgetMapper *wmRv = new QDataWidgetMapper(this);
    wmRv->setModel(_tmModel);
    wmRv->setItemDelegate(new CDelegateDbImage(
                                wmRv,
                                _tmModel->fieldIndex( dbFieldName() ),
                                size(),
                                _lblInfo));
    wmRv->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    wmRv->addMapping(label(), _tmModel->fieldIndex( dbFieldName() ));
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

    _baBuffer.clear();

    // file to buffer
    {
        if (IMAGE_IS_CONVERT) {
            CUtils::imageConvert(a_filePath, &_baBuffer);
        } else {
            QFile file(a_filePath);

            bool bRv = file.open(QIODevice::ReadOnly);
            Q_ASSERT(bRv);

            _baBuffer = file.readAll();
        }

        Q_ASSERT(!_baBuffer.isEmpty());
    }

    // _lblLabel
    {
        if (_baBuffer.isEmpty()) {
            _lblLabel->setText(TEXT_NO_PHOTO);
        } else {
            QPixmap pixOriginal;

            bool bRv = pixOriginal.loadFromData(_baBuffer);
            Q_ASSERT(bRv);

            QPixmap pixScaled = pixOriginal.scaled(
                                        size(),
                                        Qt::KeepAspectRatio,
                                        Qt::FastTransformation);

            _lblLabel->setPixmap(pixScaled);
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

    cQByteArray baImage = _tmModel->record( dbRecordIndex() )
                                .value(_csDbFieldName).toByteArray();

    QFile file(a_filePath);
    bool bRv = file.open(QIODevice::WriteOnly);
    Q_ASSERT(bRv);

    QDataStream stream(&file);
    cint ciRv = stream.writeRawData(baImage.constData(), baImage.size());
    Q_ASSERT(ciRv == baImage.size());
}
//------------------------------------------------------------------------------
void
CDbImageLabel::_remove()
{
    _baBuffer.clear();
    _flush();
    _lblLabel->clear();
}
//------------------------------------------------------------------------------
void
CDbImageLabel::_flush()
{
#if 0
    #error "BUG: QSqlTableModel::setRecord - not work"

    QSqlRecord srRecord = _tmModel->record( dbRecordIndex() );
    srRecord.setValue(dbFieldName(), _baBuffer);

    bool bRv = _tmModel->setRecord(dbRecordIndex(), srRecord);
    Q_ASSERT(bRv);
#else
    cint              column = _tmModel->fieldIndex( dbFieldName() );
    Q_ASSERT(- 1 < column);
    const QModelIndex index  = _tmModel->index(dbRecordIndex(), column);

    bool bRv = _tmModel->setData(index, _baBuffer);
    Q_ASSERT(bRv);
#endif

    _baBuffer.clear();
}
//------------------------------------------------------------------------------
