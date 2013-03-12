/**
 * \file   CImageItem.cpp
 * \brief  DB image item
 */


#include "CImageItem.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
int            CImageItem::currentDbIndex = - 1;
CDbImageLabel *CImageItem::currentDbImage = NULL;
//------------------------------------------------------------------------------
CImageItem::CImageItem() :
    index      (- 1),
    photoMini  (NULL),
    dbFieldName(),
    dbImage    (NULL)
{
}
//------------------------------------------------------------------------------
CImageItem::~CImageItem() {

}
//------------------------------------------------------------------------------
/* static */
CImageItem *
CImageItem::find(
    cdb_items_t  &dbItems,
    const QLabel *photoMini
)
{
    foreach (CImageItem *item, dbItems) {
        if (photoMini == item->photoMini) {
            return item;
        }
    }

    return NULL;
}
//------------------------------------------------------------------------------
/* static */
CImageItem *
CImageItem::find(
    cdb_items_t &dbItems,
    cint        &index
)
{
    foreach (CImageItem *item, dbItems) {
        if (index == item->index) {
            return item;
        }
    }

    return NULL;
}
//------------------------------------------------------------------------------
/* static */
bool
CImageItem::isLabelsEmpty(
    cdb_items_t &dbItems
)
{
    foreach (CImageItem *item, dbItems) {
        if (NULL != item->photoMini->pixmap()) {
            return true;
        }
    }

    return false;
}
//------------------------------------------------------------------------------

