/**
 * \file   CEditor.h
 * \brief  edit person data
 */


#ifndef XXXDb_CEditorH
#define XXXDb_CEditorH
//------------------------------------------------------------------------------
#include "ui_CEditor.h"

#include "../QtLib/Common.h"
#include "../Config.h"
#include "CMain.h"
//------------------------------------------------------------------------------
class CSettings;
class CAlbum;
class CDbImageLabel;

class CEditor :
    public QDialog
{
    Q_OBJECT

public:
    Ui::CEditor        m_Ui;
    CAlbum            *m_wndAlbum;

                       CEditor     (QWidget *parent, QSqlTableModel *tableModel,
                                    CSqlNavigator *sqlNavigator);

protected:
    virtual void       closeEvent  (QCloseEvent *event);

private:
    CSettings         *_m_stApp;
    QSqlTableModel    *_m_tmModel;
    CSqlNavigator     *_m_snSqlNavigator;
    db_items_t         _m_hsDbItems;
    QDataWidgetMapper *_m_dmText;           ///< one mapper for all text items
    QDataWidgetMapper *_m_dmImage;          ///< mapper for image item
    cint               _m_ciDbRecordIndex;
    CDbImageLabel     *_m_dbImageLabel;

    void               _construct  ();
    void               _destruct   ();
    void               _initMain   ();

    void               _resetAll   ();
    void               _saveAll    ();

private Q_SLOTS:
    // photo
    void               slot_OnAlbum();

    void               slot_bbxButtons_OnClicked(QAbstractButton *button);
    void               slot_twGroups_OnActivated(const QModelIndex &index);
};
//------------------------------------------------------------------------------
#endif // XXXDb_CEditorH
