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
class CDbImageLabel :
    public QObject
    /// DB image label
{
Q_OBJECT

public:
                    CDbImageLabel(QWidget *parent, QSqlTableModel *tableModel,
                                  cQString &dbField, cint &recordIndex,
                                  QLabel *label);
        ///< constructor
    virtual        ~CDbImageLabel();
        ///< destructor

    void            loadFromFile ();
        ///< load image from file
    void            saveToFile   ();
        ///< save image to file
    void            remove       ();
        ///< remove image

private:
    QWidget        *_m_wdParent;        ///< parent QWidget
    QSqlTableModel *_m_tmModel;         ///< QSqlTableModel
    cQString        _m_csDbField;       ///< DB field name
    cint            _m_ciRecordIndex;   ///< DB record index
    QLabel         *_m_lblLabel;        ///< QLabel for display image
    QByteArray      _m_baBuffer;        ///< buffer for store image

    void            _loadFromFile(cQString &filePath, cSize &photoSize);
        ///< load image from file
    void            _saveToFile  (cQString &filePath);
        ///< save image to file
    void            _remove      ();
        ///< remove image
    void            _flush       ();
        ///< flush image buffer

};
//------------------------------------------------------------------------------
#endif // PickupDb_CDbImageLabelH
