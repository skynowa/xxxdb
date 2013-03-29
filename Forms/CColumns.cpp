/**
 * \file   CColumns.cpp
 * \brief  select QTableView columns
 */


#include "CColumns.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CColumns::CColumns(
    QWidget        *a_parent,
    QSqlTableModel *a_model
) :
    QDialog (a_parent),
    _tmModel(a_model)
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
CColumns::_construct() {
    _initMain();
}
//------------------------------------------------------------------------------
void
CColumns::_destruct() {

}
//------------------------------------------------------------------------------
void
CColumns::_initMain() {
    ui.setupUi(this);

    {
        // set caption for DB fields
        Q_ASSERT(qARRAY_LENGTH(g_dbRecords) == (size_t)_tmModel->columnCount());

        CMain *wnd = static_cast<CMain *>(parent());

        for (size_t i = 0; i < qARRAY_LENGTH(g_dbRecords); ++ i) {
            cbool isVisible = !wnd->ui.tvInfo->isColumnHidden(i);

            QListWidgetItem *item = new QListWidgetItem(ui.lwItems);
            item->setCheckState( isVisible ? Qt::Checked : Qt::Unchecked);
            item->setText(g_dbRecords[i].caption);

            ui.lwItems->addItem(item);
        }
    }

    // signals, slots
    {
        connect(ui.bbxButtons, &QDialogButtonBox::clicked,
                this,          &CColumns::slot_bbxButtons_OnClicked);
    }
}
//------------------------------------------------------------------------------
void
CColumns::_saveAll() {
    CMain *wnd = static_cast<CMain *>(parent());

    for (int i = 0; i < _tmModel->columnCount(); ++ i) {
        cbool isVisible = (ui.lwItems->item(i)->checkState() == Qt::Checked) ? true : false;

        wnd->ui.tvInfo->setColumnHidden(i, !isVisible);
    }
}
//------------------------------------------------------------------------------
void
CColumns::slot_bbxButtons_OnClicked(
    QAbstractButton *a_button
)
{
    QDialogButtonBox::StandardButton sbRv = ui.bbxButtons->standardButton(a_button);
    switch (sbRv) {
        case QDialogButtonBox::Ok:
            _saveAll();
            close();
            break;
        case QDialogButtonBox::Cancel:
            close();
            break;
        case QDialogButtonBox::Apply:
            _saveAll();
            break;
        default:
            Q_ASSERT(false);
            break;
    }
}
//------------------------------------------------------------------------------
