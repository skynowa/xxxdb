/**
 * \file   CAbout.cpp
 * \brief  about widget
 */


#include "CAbout.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CAbout::CAbout(
    QWidget *a_parent
) :
    QDialog(a_parent)
{
    _construct();
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CAbout::_construct()
{
    _initMain();
}
//------------------------------------------------------------------------------
void
CAbout::_destruct()
{

}
//------------------------------------------------------------------------------
void
CAbout::_initMain()
{
    ui.setupUi(this);

    //  signals, slots
    {
        connect(ui.bbxButtons, &QDialogButtonBox::clicked,
                this,          &CAbout::bbxButtons_onClicked);
    }
}
//------------------------------------------------------------------------------
void
CAbout::bbxButtons_onClicked(
    QAbstractButton *a_button
)
{
    QDialogButtonBox::StandardButton sbRv = ui.bbxButtons->standardButton(a_button);
    switch (sbRv) {
        case QDialogButtonBox::Ok:
            close();
            break;
        default:
            Q_ASSERT(false);
            break;
    }
}
//------------------------------------------------------------------------------
