/**
 * \file   CDbImage.cpp
 * \brief
 */


#include "CDbImage.h"

#include "../../Classes/CIni.h"
#include "../../Classes/CDelegateDbImage.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CDbImage::CDbImage(
    QWidget *a_parent /* = NULL */
) :
    QLabel          (a_parent),
    _wdParent       (a_parent),
    _tmModel        (NULL),
    _csDbFieldName  (),
    _ciIndex        (- 1),
    _ciDbRecordIndex(- 1),
    _lblLabel       (NULL),
    _cszSize        (),
    _lblInfo        (NULL),
    _dmMapper       (NULL),
    _baBuffer       ()
{
}
//------------------------------------------------------------------------------
CDbImage::CDbImage(
    QWidget        *a_parent,           ///< parent QWidget
    QSqlTableModel *a_tableModel,       ///< QSqlTableModel
    cQString       &a_dbFieldName,      ///< DB field name
    cint           &a_index,            ///< index
    cint           &a_dbRecordIndex,    ///< DB record index
    QLabel         *a_label,            ///< QLabel for display image
    cQSize         &a_size,             ///< image sizes
    QLabel         *a_info              ///< QLabel for display image
) :
    QLabel          (a_parent),
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
    qTEST(NULL != a_parent);
    qTEST(NULL != a_tableModel);
    qTEST(!a_dbFieldName.isEmpty());
    qTEST(- 1 < a_index);
    // a_dbRecordIndex - n/a
    qTEST(NULL != a_label);
    qTEST(a_size.isValid());
    // a_info - n/a

    _dmMapper = _map();
}
//------------------------------------------------------------------------------
/* virtual */
CDbImage::~CDbImage() {

}
//------------------------------------------------------------------------------


/*******************************************************************************
*   public, data
*
*******************************************************************************/

//------------------------------------------------------------------------------
cQString &
CDbImage::dbFieldName() const
{
    qTEST(!_csDbFieldName.isEmpty());

    return _csDbFieldName;
}
//------------------------------------------------------------------------------
cint &
CDbImage::index() const
{
    qTEST(- 1 < _ciIndex);

    return _ciIndex;
}
//------------------------------------------------------------------------------
cint &
CDbImage::dbRecordIndex() const
{
    // _ciDbRecordIndex - n/a;

    return _ciDbRecordIndex;
}
//------------------------------------------------------------------------------
QLabel *
CDbImage::label() const
{
    qTEST(NULL != _lblLabel);

    return _lblLabel;
}
//------------------------------------------------------------------------------
cQSize &
CDbImage::size() const
{
    qTEST(_cszSize.isValid());

    return _cszSize;
}
//------------------------------------------------------------------------------
QLabel *
CDbImage::info() const
{
    qTEST(NULL != _lblInfo);

    return _lblInfo;
}
//------------------------------------------------------------------------------
QDataWidgetMapper *
CDbImage::mapper()
{
    qTEST(NULL != _dmMapper);

    return _dmMapper;
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   public, actions
*
*******************************************************************************/

//------------------------------------------------------------------------------
bool
CDbImage::isEmpty() const
{
    qCHECK_RET(label()->pixmap() == NULL,   true);
    qCHECK_RET(label()->pixmap()->isNull(), true);

    return false;
}
//------------------------------------------------------------------------------
void
CDbImage::loadFromFile()
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
            qTEST(false);
            break;
    }

    Q_EMIT sig_dataChanged( index() );
}
//------------------------------------------------------------------------------
void
CDbImage::saveToFile()
{
    QFileDialog fdlgDialog(_wdParent);

    fdlgDialog.setAcceptMode(QFileDialog::AcceptSave);
    fdlgDialog.setFileMode(QFileDialog::AnyFile);
    fdlgDialog.setDefaultSuffix(IMAGE_EXT_DEAFULT);
    fdlgDialog.setConfirmOverwrite(true);

    cint ciRv = fdlgDialog.exec();
    switch (ciRv) {
        case QDialog::Accepted:
            _saveToFile( fdlgDialog.selectedFiles().first() );
            break;
        case QDialog::Rejected:
            break;
        default:
            qTEST(false);
            break;
    }
}
//------------------------------------------------------------------------------
void
CDbImage::remove()
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
            qTEST(false);
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
int       CDbImage::currentIndex         = - 1;
CDbImage *CDbImage::currentDbImageLabel  = NULL;
//------------------------------------------------------------------------------
/* static */
CDbImage *
CDbImage::find(
    cdb_images_t &a_dbItems,
    const QLabel *a_label
)
{
    qTEST(!a_dbItems.empty());
    qTEST(NULL != a_label);

    Q_FOREACH (CDbImage *item, a_dbItems) {
        qCHECK_RET(a_label == item->label(), item);
    }

    return NULL;
}
//------------------------------------------------------------------------------
/* static */
CDbImage *
CDbImage::find(
    cdb_images_t &a_dbItems,
    cint         &a_index
)
{
    qTEST(!a_dbItems.empty());
    qTEST(- 1 < a_index);

    Q_FOREACH (CDbImage *item, a_dbItems) {
        qCHECK_RET(a_index == item->index(), item);
    }

    return NULL;
}
//------------------------------------------------------------------------------
/* static */
bool
CDbImage::isEmpty(
    cdb_images_t &a_dbItems
)
{
    // a_dbItems - n/a

    Q_FOREACH (CDbImage *item, a_dbItems) {
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
CDbImage::_map()
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
CDbImage::_loadFromFile(
    cQString &a_filePath   ///< image file path
)
{
    qTEST(!a_filePath.isEmpty());

    // TODO: ensure rewrite image

    _baBuffer.clear();

    // file to buffer
    {
        if (IMAGE_IS_CONVERT) {
            CUtils::imageConvert(a_filePath, &_baBuffer);
        } else {
            QFile file(a_filePath);

            bool bRv = file.open(QIODevice::ReadOnly);
            qTEST(bRv);

            _baBuffer = file.readAll();
        }

        qTEST(!_baBuffer.isEmpty());
    }

    // _lblLabel
    {
        if (_baBuffer.isEmpty()) {
            _lblLabel->setText(TEXT_NO_PHOTO);
        } else {
            QPixmap pixOriginal;

            bool bRv = pixOriginal.loadFromData(_baBuffer);
            qTEST(bRv);

            QPixmap pixScaled = pixOriginal.scaled(
                                        size(),
                                        Qt::KeepAspectRatio,
                                        Qt::FastTransformation);

            _lblLabel->setPixmap(pixScaled);
        }
    }

    _flush();

    // use CIni
    if (CIni::photos_isDeleteFromDisk()) {
        bool bRv = QFile::remove(a_filePath);
        qTEST(bRv);
    }
}
//------------------------------------------------------------------------------
void
CDbImage::_saveToFile(
    cQString &a_filePath   ///< image file path
)
{
    qTEST(!a_filePath.isEmpty());

    cQByteArray baImage = _tmModel->record( dbRecordIndex() )
                                .value(_csDbFieldName).toByteArray();

    QFile file(a_filePath);
    bool bRv = file.open(QIODevice::WriteOnly);
    qTEST(bRv);

    QDataStream stream(&file);
    cint ciRv = stream.writeRawData(baImage.constData(), baImage.size());
    qTEST(ciRv == baImage.size());
}
//------------------------------------------------------------------------------
void
CDbImage::_remove()
{
    _baBuffer.clear();
    _flush();
    _lblLabel->clear();
}
//------------------------------------------------------------------------------
void
CDbImage::_flush()
{
#if 0
    #error "BUG: QSqlTableModel::setRecord - not work"

    QSqlRecord srRecord = _tmModel->record( dbRecordIndex() );
    srRecord.setValue(dbFieldName(), _baBuffer);

    bool bRv = _tmModel->setRecord(dbRecordIndex(), srRecord);
    qTEST(bRv);
#else
    cint              column = _tmModel->fieldIndex( dbFieldName() );
    qTEST(- 1 < column);
    const QModelIndex index  = _tmModel->index(dbRecordIndex(), column);

    bool bRv = _tmModel->setData(index, _baBuffer);
    qTEST(bRv);
#endif

    _baBuffer.clear();
}
//------------------------------------------------------------------------------
