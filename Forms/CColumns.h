/**
 * \file   CColumns.h
 * \brief  select QTableView columns
 */


#ifndef XXXDb_CColumnsH
#define XXXDb_CColumnsH
//------------------------------------------------------------------------------
#include "ui_CColumns.h"

#include "../QtLib/Common.h"
#include "../Config.h"
#include "CMain.h"
//------------------------------------------------------------------------------
class CColumns :
    public QDialog
{
    Q_OBJECT

public:
    friend class CSettings;

    Ui::CColumns    ui;

                    CColumns(QWidget *parent, QSqlTableModel *model);

private:
    QSqlTableModel *_tmModel;

    void            _construct();
    void            _destruct ();
    void            _initMain ();
    void            _saveAll  ();

    // slots
    void            slot_bbxButtons_OnClicked(QAbstractButton *button);
};
//------------------------------------------------------------------------------
#endif // XXXDb_CColumnsH