/**
 * \file   CDbImageLabel.h
 * \brief  DB image label
 */


#ifndef PickupDb_CDbImageLabelH
#define PickupDb_CDbImageLabelH
//------------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "../Config.h"
//------------------------------------------------------------------------------
class CDbImageLabel;

typedef QVector<CDbImageLabel *> db_images_t;
typedef const db_images_t        cdb_images_t;

class CDbImageLabel :
    public QObject
    /// DB image label
{
Q_OBJECT

public:
                          CDbImageLabel(QWidget *parent, QSqlTableModel *tableModel,
                                        cQString &dbFieldName, cint &index,
                                        cint &dbRecordIndex, QLabel *label);
        ///< constructor
    virtual              ~CDbImageLabel();
        ///< destructor

    // data
    cQString &            dbFieldName  () const;
        ///< get DB field name
    cint &                index        () const;
        ///< get index
    cint &                dbRecordIndex() const;
        ///< get DB record index
    QLabel *              label        () const;
        ///< get QLabel

    // actions
    void                  loadFromFile ();
        ///< load image from file
    void                  saveToFile   ();
        ///< save image to file
    void                  remove       ();
        ///< remove image

    // static
    static int            currentIndex;         ///< get current index
    static CDbImageLabel *currentDbImageLabel;  ///< get current CDbImageLabel

    static CDbImageLabel *find         (cdb_images_t &dbItems, const QLabel *label);
        ///< find CDbImageLabel by QLabel
    static CDbImageLabel *find         (cdb_images_t &dbItems, cint &index);
        ///< find CDbImageLabel by index
    static bool           isLabelsEmpty(cdb_images_t &dbItems);
        ///< is all QLabels empty

Q_SIGNALS:
    void                  signal_DataChanged(cint &index);

private:
    QWidget              *_m_wdParent;        ///< parent QWidget
    QSqlTableModel       *_m_tmModel;         ///< QSqlTableModel
    cQString              _m_csDbFieldName;   ///< DB field name
    cint                  _m_ciIndex;         ///< index
    cint                  _m_ciDbRecordIndex; ///< DB record index
    QLabel               *_m_lblLabel;        ///< QLabel for display image
    QByteArray            _m_baBuffer;        ///< buffer for store image

    void                  _loadFromFile(cQString &filePath, cSize &imageSize);
        ///< load image from file
    void                  _saveToFile  (cQString &filePath);
        ///< save image to file
    void                  _remove      ();
        ///< remove image
    void                  _flush       ();
        ///< flush image buffer

};
//------------------------------------------------------------------------------
#endif // PickupDb_CDbImageLabelH
