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

typedef QVector<CDbImageLabel *> db_items_t;
typedef const db_items_t         cdb_items_t;

class CDbImageLabel :
    public QObject
    /// DB image label
{
Q_OBJECT

public:
                          CDbImageLabel(QWidget *parent, QSqlTableModel *tableModel,
                                        cQString &dbFieldName, cint &recordIndex,
                                        QLabel *label);
        ///< constructor
    virtual              ~CDbImageLabel();
        ///< destructor

    // data
    const QString &       dbFieldName  () const;
        ///< get DB field name
    const int &           recordIndex  () const;
        ///< get record index
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
    static int            currentDbIndex;
        ///<
    static CDbImageLabel *currentDbImage;
        ///<

    static CDbImageLabel *find         (cdb_items_t &dbItems, const QLabel *photoMini);
        ///< find CDbImageLabel by QLabel
    static CDbImageLabel *find         (cdb_items_t &dbItems, cint &index);
        ///< find CDbImageLabel by record index
    static bool           isLabelsEmpty(cdb_items_t &dbItems);
        ///< is all QLabels empty

private:
    QWidget              *_m_wdParent;        ///< parent QWidget
    QSqlTableModel       *_m_tmModel;         ///< QSqlTableModel
    cQString              _m_csDbFieldName;   ///< DB field name
    cint                  _m_ciRecordIndex;   ///< DB record index
    QLabel               *_m_lblLabel;        ///< QLabel for display image
    QByteArray            _m_baBuffer;        ///< buffer for store image

    void                  _loadFromFile(cQString &filePath, cSize &photoSize);
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