/**
 * \file   CSettings.h
 * \brief  application settings
 */


#ifndef XXXDb_CSettingsH
#define XXXDb_CSettingsH
//------------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "CConfig.h"
//------------------------------------------------------------------------------
class CMain;
class CEditor;
class CAlbum;

class CSettings
    /// application settings
{
public:
              CSettings(CMain *wndMain, CEditor *wndEditor, CAlbum *wndAlbum);
        ///< constructor
    virtual  ~CSettings();
        ///< destructor

private:
    QSettings _stApp;
    CMain    *_wndMain;
    CEditor  *_wndEditor;
    CAlbum   *_wndAlbum;

    template <typename T>
    void      _commonGet(T *wnd);
        ///< read data
    template <typename T>
    void      _commonSet(T *wnd);
        ///< write data

    void      _get(CMain *wnd);
        ///< read data
    void      _set(CMain *wnd);
        ///< write data

    void      _get(CEditor *wnd);
        ///< read data
    void      _set(CEditor *wnd);
        ///< write data

    void      _get(CAlbum *wnd);
        ///< read data
    void      _set(CAlbum *wnd);
        ///< write data
};
//------------------------------------------------------------------------------
#endif // XXXDb_CSettingsH
