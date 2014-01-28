/**
 * \file   CAbout.h
 * \brief  about widget
 */


#ifndef XXXDb_CAboutH
#define XXXDb_CAboutH
//-------------------------------------------------------------------------------------------------
#include "ui_CAbout.h"

#include "../QtLib/Common.h"
#include "../Classes/CConfig.h"
#include "CMain.h"
//-------------------------------------------------------------------------------------------------
class CAbout :
    public QDialog
{
    Q_OBJECT

public:
    Ui::CAbout ui;

    explicit   CAbout(QWidget *parent);

private:
    void       _construct();
    void       _destruct();
    void       _initMain();

    // slots
    void       bbxButtons_onClicked(QAbstractButton *button);

    friend class CIni;
};
//-------------------------------------------------------------------------------------------------
#endif // XXXDb_CAboutH
