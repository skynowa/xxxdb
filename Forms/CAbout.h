/**
 * \file   CAbout.h
 * \brief  about widget
 */


#ifndef XXXDb_CAboutH
#define XXXDb_CAboutH
//------------------------------------------------------------------------------
#include "ui_CAbout.h"

#include "../QtLib/Common.h"
#include "../Config.h"
#include "CMain.h"
//------------------------------------------------------------------------------
class CAbout :
    public QDialog
{
    Q_OBJECT

public:
    Ui::CAbout ui;

    explicit   CAbout    (QWidget *parent = NULL);

private:
    void       _construct();
    void       _destruct ();
    void       _initMain ();

    // slots
    void       slot_bbxButtons_OnClicked(QAbstractButton *button);
};
//------------------------------------------------------------------------------
#endif // XXXDb_CAboutH
