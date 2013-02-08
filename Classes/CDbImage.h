/**
 * \file   CDbImage.h
 * \brief  DB image
 */


#ifndef PickupDb_CDbImageH
#define PickupDb_CDbImageH
//---------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "../Config.h"
//---------------------------------------------------------------------------
class CDbImage :
    public QObject
{
Q_OBJECT

public:
                    CDbImage      (QObject *parent, QSqlTableModel *tableModel,
                                   const QString &dbField, const int &currentIndex,
                                   QLabel *label);
    virtual        ~CDbImage      ();

    void            importFromFile(const QString &filePath);
    void            exportToFile  (const QString &filePath);
    void            changeFromFile(const QString &filePath);
    void            clear         ();
    void            remove        ();
    void            save          ();

private:
    QSqlTableModel *_m_tmModel;
    const QString   _m_csDbField;
    const int       _m_ciCurrentIndex;
    QLabel         *_m_lblLabel;
    QByteArray      _m_baBuffer;
};
//---------------------------------------------------------------------------
#endif // PickupDb_CDbImageH
