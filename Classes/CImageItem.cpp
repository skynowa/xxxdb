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
int       CImageItem::currentDbIndex = - 1;
CDbImage *CImageItem::currentDbImage = NULL;
//------------------------------------------------------------------------------
CImageItem::CImageItem() :
    index      (- 1),
    imageLabel (NULL),
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
    const QLabel *imageLabel
)
{
    foreach (CImageItem *item, dbItems) {
        if (imageLabel == item->imageLabel) {
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
        if (NULL != item->imageLabel->pixmap()) {
            return true;
        }
    }

    return false;
}
//------------------------------------------------------------------------------

