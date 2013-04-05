/**
 * \file   CIni.h
 * \brief  application settings
 */


#ifndef XXXDb_CIniH
#define XXXDb_CIniH
//------------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "CConfig.h"
//------------------------------------------------------------------------------
class CMain;
class CEditor;
class CAlbum;

class CIni
    /// application settings
{
public:
              CIni(CMain *wndMain, CEditor *wndEditor, CAlbum *wndAlbum);
    virtual  ~CIni();

private:
    QSettings _stApp;
    CMain    *_wndMain;
    CEditor  *_wndEditor;
    CAlbum   *_wndAlbum;

    template <typename T>
    void      _commonGet(T *wnd);
    template <typename T>
    void      _commonSet(T *wnd);

    void      _get(CMain *wnd);
    void      _set(CMain *wnd);

    void      _get(CEditor *wnd);
    void      _set(CEditor *wnd);

    void      _get(CAlbum *wnd);
    void      _set(CAlbum *wnd);
};
//------------------------------------------------------------------------------
#endif // XXXDb_CIniH
