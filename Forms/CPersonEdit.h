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
#include "../Classes/CDbImage.h"

#include "CMain.h"
//------------------------------------------------------------------------------
class CPhotoAlbum;

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
    typedef QHash<QWidget *, QString> db_controls_t;
    typedef const db_controls_t       cdb_controls_t;

    QSqlTableModel    *_m_tmModel;
    CSqlNavigator     *_m_snSqlNavigator;
    db_controls_t      _m_hsDbControls;
    QDataWidgetMapper *_m_dmMapper;
    cint               _m_ciCurrentRow;
    CDbImage          *_m_dbImage;

    void               _construct();
    void               _destruct ();
    void               _initMain ();

    void               _resetAll ();
    void               _saveAll  ();

private Q_SLOTS:
    // photo
    void               slot_OnPhotoAlbum        ();

    void               slot_bbxButtons_OnClicked(QAbstractButton *button);
    void               slot_twGroups_OnActivated(const QModelIndex &index);
};
//------------------------------------------------------------------------------
#endif // PickupDB_CPersonEditH
