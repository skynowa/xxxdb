/**
 * \file   CApplication.h
 * \brief  application settings
 */


#ifndef XXXDb_CApplicationH
#define XXXDb_CApplicationH
//------------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "../Config.h"
//------------------------------------------------------------------------------
class CApplication :
    public QApplication
    /// application
{
public:
                CApplication  (int &argc, char **argv);
        ///< constructor
    virtual    ~CApplication  ();
        ///< destructor

    static void windowActivate(cQString &appWndClass, cQString &appName);
        ///< activate main window
    static bool isRunnig      (cQString &appGuid);
        ///< check if application already running
    static bool selfCheck     ();
        ///< self check

private:

};
//------------------------------------------------------------------------------
#endif // XXXDb_CApplicationH
