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

class CImageItem {
public:
    int                index;
    QLabel            *imageLabel;
    QString            dbFieldName;
    CDbImage          *dbImage;
    static int         currentDbIndex;
    static CDbImage   *currentDbImage;

                       CImageItem();
                      ~CImageItem();

    static CImageItem *find      (cdb_items_t &dbItems, const QLabel *imageLabel);
    static CImageItem *find      (cdb_items_t &dbItems, cint &index);

private:

};
//------------------------------------------------------------------------------
#endif // PickupDb_CImageItemH
