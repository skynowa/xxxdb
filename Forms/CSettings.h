/**
 * \file   CSettings.h
 * \brief  edit person data
 */


#ifndef XXXDb_CSettingsH
#define XXXDb_CSettingsH
//-------------------------------------------------------------------------------------------------
#include "ui_CSettings.h"

#include "../QtLib/Common.h"
#include "../Classes/CConfig.h"
#include "CMain.h"
//-------------------------------------------------------------------------------------------------
class CSettings :
    public QDialog
{
    Q_OBJECT

public:
                  CSettings(QWidget *parent);

protected:
    virtual void  closeEvent(QCloseEvent *event);

private:
    Ui::CSettings ui;

    void          _construct();
    void          _destruct();
    void          _initMain();

    void          _resetAll();
    void          _saveAll();

    // slots
    void          bbxButtons_onClicked(QAbstractButton *button);
    void          twGroups_onCurrentItemChanged(QTreeWidgetItem *current,
                      QTreeWidgetItem *previous);

    friend class CIni;
};
//-------------------------------------------------------------------------------------------------
#endif // XXXDb_CSettingsH
