/**
 * \file   CSettings.h
 * \brief  application settings
 */


#ifndef PickupDb_CSettingsH
#define PickupDb_CSettingsH
//------------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "../Config.h"
//------------------------------------------------------------------------------
class CMain;
class CPersonEdit;
class CPhotoAlbum;

class CSettings
    /// application settings
{
public:
                 CSettings   (CMain *, CPersonEdit *, CPhotoAlbum *);
        ///< constructor
    virtual     ~CSettings   ();
        ///< destructor

private:
    CMain       *_m_wndMain;
    CPersonEdit *_m_wndPersonEdit;
    CPhotoAlbum *_m_wndPhotoAlbum;

    template <typename T>
    void         _commonRead (T *);
        ///< read data
    template <typename T>
    void         _commonWrite(T *);
        ///< write data

    void         _read       (CMain *);
        ///< read data
    void         _write      (CMain *);
        ///< write data

    void         _read       (CPersonEdit *);
        ///< read data
    void         _write      (CPersonEdit *);
        ///< write data

    void         _read       (CPhotoAlbum *);
        ///< read data
    void         _write      (CPhotoAlbum *);
        ///< write data
};
//------------------------------------------------------------------------------
#endif // PickupDb_CSettingsH
