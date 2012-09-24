/**
 * \file   CUtils.h
 * \brief
 */


#ifndef PickupDb_CUtilsH
#define PickupDb_CUtilsH
//---------------------------------------------------------------------------
#include "../QtLib/Common.h"
//---------------------------------------------------------------------------
class CUtils {
    public:
        static void widgetAlignCenter(QWidget *widget);
        static void imageConvert     (const QString    &filePathIn,
                                      QByteArray       *baPhoto,
                                      const QByteArray &format = "JPEG");

    private:
                    CUtils      ();
                   ~CUtils      ();
};
//---------------------------------------------------------------------------
#endif // PickupDb_CUtilsH
