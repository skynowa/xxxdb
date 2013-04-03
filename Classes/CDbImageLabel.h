/**
 * \file   CDbImageLabel.h
 * \brief  DB image label
 */


#ifndef XXXDb_CDbImageLabelH
#define XXXDb_CDbImageLabelH
//------------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "CConfig.h"
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
                                        cint &dbRecordIndex,
                                        QLabel *label, cQSize &size,
                                        QLabel *info);
        ///< constructor
    virtual              ~CDbImageLabel();
        ///< destructor

    // data
    cQString &            dbFieldName() const;
        ///< get DB field name
    cint &                index() const;
        ///< get index
    cint &                dbRecordIndex() const;
        ///< get DB record index
    QLabel *              label() const;
        ///< get QLabel
    cQSize &              size() const;
        ///< get image sizes
    QLabel *              info() const;
        ///< get info QLabel
    QDataWidgetMapper    *mapper();
        ///< get data widget mapper

    // actions
    bool                  isEmpty() const;
        ///< is empty image
    void                  loadFromFile();
        ///< load image from file
    void                  saveToFile();
        ///< save image to file
    void                  remove();
        ///< remove image

    // static
    static int            currentIndex;         ///< get current index
    static CDbImageLabel *currentDbImageLabel;  ///< get current CDbImageLabel

    static CDbImageLabel *find(cdb_images_t &dbItems, const QLabel *label);
        ///< find CDbImageLabel by QLabel
    static CDbImageLabel *find(cdb_images_t &dbItems, cint &index);
        ///< find CDbImageLabel by index
    static bool           isEmpty(cdb_images_t &dbItems);
        ///< is all QLabels empty

Q_SIGNALS:
    void                  sig_dataChanged(cint &index);

private:
    QWidget              *_wdParent;        ///< parent QWidget
    QSqlTableModel       *_tmModel;         ///< QSqlTableModel
    cQString              _csDbFieldName;   ///< DB field name
    cint                  _ciIndex;         ///< index
    cint                  _ciDbRecordIndex; ///< DB record index
    QLabel               *_lblLabel;        ///< QLabel for display image
    cQSize                _cszSize;         ///< image sizes
    QLabel               *_lblInfo;         ///< QLabel for display image info
    QDataWidgetMapper    *_dmMapper;        ///< data widget mapper
    QByteArray            _baBuffer;        ///< buffer for store image

    QDataWidgetMapper    *_map();
        ///< map QWidget to DB field
    void                  _loadFromFile(cQString &filePath);
        ///< load image from file
    void                  _saveToFile(cQString &filePath);
        ///< save image to file
    void                  _remove();
        ///< remove image
    void                  _flush();
        ///< flush image buffer

};
//------------------------------------------------------------------------------
#endif // XXXDb_CDbImageLabelH
