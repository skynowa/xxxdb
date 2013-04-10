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
*   protected
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CColumns::changeEvent(
    QEvent *a_event
)
{
    // retranslation
    if (a_event->type() == QEvent::LanguageChange) {
        _retranslateUi();
    }

    QWidget::changeEvent(a_event);
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CColumns::_construct()
{
    _initMain();
}
//------------------------------------------------------------------------------
void
CColumns::_destruct()
{

}
//------------------------------------------------------------------------------
void
CColumns::_initMain()
{
    ui.setupUi(this);

    {
        // set caption for DB fields
        CMain *wnd = static_cast<CMain *>(parent());

        for (int i = 0; i < _tmModel->columnCount(); ++ i) {
            cbool isVisible = !wnd->ui.tvInfo->isColumnHidden(i);

            QListWidgetItem *item = new QListWidgetItem(ui.lwItems);
            item->setCheckState( isVisible ? Qt::Checked : Qt::Unchecked);
            item->setText(CConfig::dbRecords[i].caption);

            ui.lwItems->addItem(item);
        }
    }

    // raise event for retranslation UI
    {
        qApp->sendEvent(this, new QEvent(QEvent::LanguageChange));
    }

    // signals, slots
    {
        connect(ui.bbxButtons, &QDialogButtonBox::clicked,
                this,          &CColumns::bbxButtons_onClicked);
    }
}
//------------------------------------------------------------------------------
void
CColumns::_saveAll()
{
    CMain *wnd = static_cast<CMain *>(parent());

    for (int i = 0; i < _tmModel->columnCount(); ++ i) {
        cbool isVisible = (ui.lwItems->item(i)->checkState() == Qt::Checked) ? true : false;

        wnd->ui.tvInfo->setColumnHidden(i, !isVisible);
    }
}
//------------------------------------------------------------------------------
void
CColumns::_retranslateUi()
{
    // ui.lwItems
    for (int i = 0; i < ui.lwItems->count(); ++ i) {
        ui.lwItems->item(i)->setText(
            qApp->translate("CConfig", CConfig::dbRecords[i].caption)
        );
    }
}
//------------------------------------------------------------------------------
void
CColumns::bbxButtons_onClicked(
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
            qTEST(false);
            break;
    }
}
//------------------------------------------------------------------------------
