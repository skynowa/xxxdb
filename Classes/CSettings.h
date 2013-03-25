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
              CSettings   (CMain *wndMain, CEditor *wndEditor, CAlbum *wndAlbum);
        ///< constructor
    virtual  ~CSettings   ();
        ///< destructor

private:
    QSettings _stApp;
    CMain    *_wndMain;
    CEditor  *_wndEditor;
    CAlbum   *_wndAlbum;

    template <typename T>
    void      _commonRead (T *wnd);
        ///< read data
    template <typename T>
    void      _commonWrite(T *wnd);
        ///< write data

    void      _read       (CMain *wnd);
        ///< read data
    void      _write      (CMain *wnd);
        ///< write data

    void      _read       (CEditor *wnd);
        ///< read data
    void      _write      (CEditor *wnd);
        ///< write data

    void      _read       (CAlbum *wnd);
        ///< read data
    void      _write      (CAlbum *wnd);
        ///< write data
};
//------------------------------------------------------------------------------
#endif // XXXDb_CSettingsH
