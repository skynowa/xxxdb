/**
 * \file   CImageItem.h
 * \brief  DB image item
 */


#ifndef PickupDb_CImageItemH
#define PickupDb_CImageItemH
//------------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "../Config.h"
#include "../Classes/CDbImage.h"
//------------------------------------------------------------------------------
class CImageItem;

typedef QVector<CImageItem *> db_items_t;
typedef const db_items_t      cdb_items_t;

class CImageItem :
    public QObject
{
public:
    int                index;
    QLabel            *photoMini;
    QString            dbFieldName;
    CDbImage          *dbImage;

    static int         currentDbIndex;
    static CDbImage   *currentDbImage;

                       CImageItem   ();
    virtual           ~CImageItem   ();

    static CImageItem *find         (cdb_items_t &dbItems, const QLabel *photoMini);
    static CImageItem *find         (cdb_items_t &dbItems, cint &index);
    static bool        isLabelsEmpty(cdb_items_t &dbItems);

private:

};
//------------------------------------------------------------------------------
#endif // PickupDb_CImageItemH
