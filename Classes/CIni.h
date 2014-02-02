/**
 * \file   CIni.h
 * \brief  application settings
 */


#ifndef XXXDb_CIniH
#define XXXDb_CIniH
//-------------------------------------------------------------------------------------------------
#include <QtLib/Common.h>
#include <QtLib/CUtils.h>
#include <xLib/xLib.h>
#include "CConfig.h"
//-------------------------------------------------------------------------------------------------
class CMain;
class CEditor;
class CAlbum;

class CIni
    /// application settings
{
private:
               CIni();
              ~CIni();

public:
    static
    void       construct();
    static
    void       destruct();

    static
    void       get(CMain *wnd);
    static
    void       set(CMain *wnd);

    static
    void       get(CAlbum *wnd);
    static
    void       set(CAlbum *wnd);

public:
    static
    bool       photos_isDeleteFromDisk();
    static
    void       setPhotos_isDeleteFromDisk(const bool &value);

private:
    static
    QSettings *_iniApp;

    static
    void       _load();
    static
    void       _save();

    // group "Photos"
    static
    bool       _photos_isDeleteFromDisk;  ///< is delete photo from disk after import

    template <typename T>
    static
    void       _commonGet(T *wnd);
    template <typename T>
    static
    void       _commonSet(T *wnd);
};
//-------------------------------------------------------------------------------------------------
#endif // XXXDb_CIniH
