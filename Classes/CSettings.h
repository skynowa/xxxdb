/**
 * \file   CSettings.h
 * \brief  application settings
 */


#ifndef XXXDb_CSettingsH
#define XXXDb_CSettingsH
//------------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "../Config.h"
//------------------------------------------------------------------------------
class CMain;
class CEditor;
class CAlbum;

class CSettings
    /// application settings
{
public:
             CSettings   (CMain *, CEditor *, CAlbum *);
        ///< constructor
    virtual ~CSettings   ();
        ///< destructor

private:
    CMain   *_wndMain;
    CEditor *_wndEditor;
    CAlbum  *_wndAlbum;

    template <typename T>
    void     _commonRead (T *);
        ///< read data
    template <typename T>
    void     _commonWrite(T *);
        ///< write data

    void     _read       (CMain *);
        ///< read data
    void     _write      (CMain *);
        ///< write data

    void     _read       (CEditor *);
        ///< read data
    void     _write      (CEditor *);
        ///< write data

    void     _read       (CAlbum *);
        ///< read data
    void     _write      (CAlbum *);
        ///< write data
};
//------------------------------------------------------------------------------
#endif // XXXDb_CSettingsH
