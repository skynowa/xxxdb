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
    QWidget *a_parent /* NULL */
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
CAbout::_construct() {
    _initMain();
}
//------------------------------------------------------------------------------
void
CAbout::_destruct() {

}
//------------------------------------------------------------------------------
void
CAbout::_initMain() {
    m_Ui.setupUi(this);

    // main
    {
        setWindowTitle(APP_ABOUT_TITLE);
    }

    //  signals, slots
    {
        connect(m_Ui.bbxButtons, &QDialogButtonBox::clicked,
                this,            &CAbout::slot_bbxButtons_OnClicked);
    }
}
//------------------------------------------------------------------------------
void
CAbout::slot_bbxButtons_OnClicked(
    QAbstractButton *a_button
)
{
    QDialogButtonBox::StandardButton sbRv = m_Ui.bbxButtons->standardButton(a_button);
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
