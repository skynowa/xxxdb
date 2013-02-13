/**
 * \file   CImageItem.cpp
 * \brief  DB image item
 */


#include "CImageItem.h"


/******************************************************************************
*   public
*
******************************************************************************/

//-----------------------------------------------------------------------------
int       CImageItem::currentDbIndex = - 1;
CDbImage *CImageItem::currentDbImage = NULL;
//-----------------------------------------------------------------------------
CImageItem::CImageItem() :
    index      (- 1),
    imageLabel (NULL),
    dbFieldName(),
    dbImage    (NULL)
{
}
//-----------------------------------------------------------------------------
CImageItem::~CImageItem() {

}
//-----------------------------------------------------------------------------
/* static */
CImageItem *
CImageItem::find(
    cdb_items_t  &dbItems,
    const QLabel *imageLabel
)
{
    CImageItem *iiRv = NULL;

    foreach (CImageItem *item, dbItems) {
        if (imageLabel == item->imageLabel) {
            iiRv = item;
            break;
        }
    }

    return iiRv;
}
//-----------------------------------------------------------------------------
/* static */
CImageItem *
CImageItem::find(
    cdb_items_t &dbItems,
    cint        &index
)
{
    CImageItem *iiRv = NULL;

    foreach (CImageItem *item, dbItems) {
        if (index == item->index) {
            iiRv = item;
            break;
        }
    }

    return iiRv;
}
//-----------------------------------------------------------------------------

