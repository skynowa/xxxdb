/**
 * \file   CUtils.cpp
 * \brief
 */


#include "CUtils.h"

#include <QImageWriter>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CUtils::widgetAlignCenter(
    QWidget *widget
)
{
    Q_ASSERT(NULL != widget);

    QDesktopWidget *desktop = QApplication::desktop();

    const int x = (desktop->width()  - widget->width())  / 2;
    const int y = (desktop->height() - widget->height()) / 2;

    widget->setGeometry(x, y, widget->width(), widget->height());
}
//---------------------------------------------------------------------------
void
CUtils::imageConvert(
    const QString    &filePathIn,
    QByteArray       *baPhoto,
    const QByteArray &format /* = "JPEG" */
)
{
    QImage       image (filePathIn);
    QBuffer      buffer(baPhoto);
    QImageWriter writer(&buffer, format);

    /// writer.setCompression(9);

    bool bRv = writer.write(image);
    Q_ASSERT(true == bRv);

    buffer.close();
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CUtils::CUtils() {

}
//---------------------------------------------------------------------------
CUtils::~CUtils() {

}
//---------------------------------------------------------------------------
