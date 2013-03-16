/**
 * \file   CPersonEdit.h
 * \brief  edit person data
 */


#ifndef PickupDB_CPersonEditH
#define PickupDB_CPersonEditH
//------------------------------------------------------------------------------
#include "ui_CPersonEdit.h"

#include "../QtLib/Common.h"
#include "../Config.h"
#include "CMain.h"
//------------------------------------------------------------------------------
class CPhotoAlbum;
class CDbImageLabel;

class CPersonEdit :
    public QDialog
{
    Q_OBJECT

public:
    Ui::CPersonEdit    m_Ui;

                       CPersonEdit(QWidget *parent, QSqlTableModel *tableModel,
                                   CSqlNavigator *sqlNavigator);
    virtual           ~CPersonEdit();

    CPhotoAlbum       *m_wndPhotoAlbum;

private:
    QSqlTableModel    *_m_tmModel;
    CSqlNavigator     *_m_snSqlNavigator;
    db_items_t         _m_hsDbItems;
    QDataWidgetMapper *_m_dmText;           ///< one mapper for all text items
    QDataWidgetMapper *_m_dmImage;          ///< mapper for image item
    cint               _m_ciDbRecordIndex;
    CDbImageLabel     *_m_dbImageLabel;

    void               _construct();
    void               _destruct ();
    void               _initMain ();

    void               _resetAll ();
    void               _saveAll  ();

private Q_SLOTS:
    // photo
    void               slot_OnPhotoAlbum();

    void               slot_bbxButtons_OnClicked(QAbstractButton *button);
    void               slot_twGroups_OnActivated(const QModelIndex &index);
};
//------------------------------------------------------------------------------
#endif // PickupDB_CPersonEditH
