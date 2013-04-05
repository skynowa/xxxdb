/**
 * \file   CSettings.h
 * \brief  edit person data
 */


#include "CSettings.h"

#include "../QtLib/CUtils.h"
#include "../Classes/CIni.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CSettings::CSettings(
    QWidget *a_parent
) :
    QDialog(a_parent)

{
    Q_ASSERT(NULL != a_parent);

    _construct();

    _iniApp = new CIni(NULL, NULL, NULL);
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   protected
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* virtual */
void
CSettings::closeEvent(
    QCloseEvent *a_event
)
{
    _destruct();
    a_event->accept();
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CSettings::_construct() {
    _initMain();
}
//------------------------------------------------------------------------------
void
CSettings::_destruct() {
    qPTR_DELETE(_iniApp);
}
//------------------------------------------------------------------------------
void
CSettings::_initMain() {
    ui.setupUi(this);

    // signals
    {
        connect(ui.bbxButtons, &QDialogButtonBox::clicked,
                this,          &CSettings::bbxButtons_onClicked);
        connect(ui.twGroups,   &QTreeWidget::currentItemChanged,
                this,          &CSettings::twGroups_onCurrentItemChanged);
    }
}
//------------------------------------------------------------------------------
void
CSettings::_resetAll() {

}
//------------------------------------------------------------------------------
void
CSettings::_saveAll() {

}
//------------------------------------------------------------------------------

/*******************************************************************************
*   private slots
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CSettings::bbxButtons_onClicked(
    QAbstractButton *a_button
)
{
    QDialogButtonBox::StandardButton sbRv = ui.bbxButtons->standardButton(a_button);
    switch (sbRv) {
        case QDialogButtonBox::Reset:
            _resetAll();
            break;
        case QDialogButtonBox::Ok:
            _saveAll();
            close();
            break;
        default:
            Q_ASSERT(false);
            break;
    }
}
//------------------------------------------------------------------------------
void
CSettings::twGroups_onCurrentItemChanged(
    QTreeWidgetItem *a_current,
    QTreeWidgetItem *a_previous
)
{
    Q_UNUSED(a_current);
    Q_UNUSED(a_previous);

    cint index = ui.twGroups->currentIndex().row();

    ui.tabwGroupsDetail->setCurrentIndex(index);
}
//------------------------------------------------------------------------------
