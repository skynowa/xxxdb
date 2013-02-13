/**
 * \file   CDbImage.h
 * \brief  DB image
 */


#ifndef PickupDb_CDbImageH
#define PickupDb_CDbImageH
//-----------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "../Config.h"
//-----------------------------------------------------------------------------
class CDbImage :
    public QObject
{
Q_OBJECT

public:
                    CDbImage     (QWidget *parent, QSqlTableModel *tableModel,
                                  cQString &dbField, cint &currentIndex,
                                  QLabel *label);
    virtual        ~CDbImage     ();

    void            loadFromFile ();
    void            saveToFile   ();
    void            remove       ();

private:
    QWidget        *_m_wdParent;
    QSqlTableModel *_m_tmModel;
    const QString   _m_csDbField;
    const int       _m_ciCurrentIndex;
    QLabel         *_m_lblLabel;
    QByteArray      _m_baBuffer;

    void            _loadFromFile(cQString &filePath);
    void            _saveToFile  (cQString &filePath);
    void            _flush       ();

};
//-----------------------------------------------------------------------------
#endif // PickupDb_CDbImageH
