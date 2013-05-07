/**
 * \file   CEditor.h
 * \brief  edit person data
 */


#ifndef XXXDb_CEditorH
#define XXXDb_CEditorH
//------------------------------------------------------------------------------
#include "ui_CEditor.h"

#include "../QtLib/Common.h"
#include "../Classes/CConfig.h"
#include "CMain.h"
//------------------------------------------------------------------------------
class CAlbum;
class CDbImageLabel;

class CEditor :
    public QDialog
{
    Q_OBJECT

public:
    Ui::CEditor        ui;
    CAlbum            *wndAlbum;

                       CEditor(QWidget *parent, QSqlTableModel *tableModel,
                               CSqlNavigator *sqlNavigator);

protected:
    virtual void       closeEvent(QCloseEvent *event);

private:
    cint               _ciDbRecordIndex;
    QSqlTableModel    *_tmModel;
    CSqlNavigator     *_snNavigator;
    db_items_t         _hsDbItems;
    QDataWidgetMapper *_dmText;           ///< one mapper for all text items
    CDbImageLabel     *_dbImageLabel;

    void               _construct();
    void               _destruct();
    void               _initMain();

    void               _resetAll();
    void               _saveAll();

    // slots
    void               onAlbum();
    void               bbxButtons_onClicked(QAbstractButton *button);
    void               twGroups_onCurrentItemChanged(QTreeWidgetItem *current,
                                                     QTreeWidgetItem *previous);

    friend class CIni;
};
//------------------------------------------------------------------------------
#endif // XXXDb_CEditorH
