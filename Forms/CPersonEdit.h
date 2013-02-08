/**
 * \file   CPersonEdit.h
 * \brief  edit person data
 */


#ifndef PickupDB_CPersonEditH
#define PickupDB_CPersonEditH
//---------------------------------------------------------------------------
#include "ui_CPersonEdit.h"

#include "../QtLib/Common.h"
#include "../Config.h"
#include "../Classes/CDbImage.h"

#include "CMain.h"
//---------------------------------------------------------------------------
class CPersonEdit :
    public QDialog
{
    Q_OBJECT

public:
    Ui::CPersonEdit           m_Ui;

                              CPersonEdit(QWidget *parent, QSqlTableModel *tableModel,
                                          const int &currentRow);
    virtual                  ~CPersonEdit();

private:
    typedef QHash<QWidget *, QString> db_controls_t;

    QList<QTreeWidgetItem *>  _m_ltwGroups;
    QSqlTableModel           *_m_tmModel;
    db_controls_t             _m_hsDbControls;
    QDataWidgetMapper        *_m_dmMapper;
    const int                 _m_ciCurrentRow;
    CDbImage                 *_m_dbImage;

    void                      _construct();
    void                      _destruct ();
    void                      _initMain ();

    void                      _resetAll ();
    void                      _saveAll  ();

private Q_SLOTS:
    void                      slot_tbtnPhotoChange_OnClicked();
    void                      slot_tbtnPhotoDelete_OnClicked();
    void                      slot_tbtnPhotoSaveAs_OnClicked();

    void                      slot_bbxButtons_OnClicked(QAbstractButton *button);
    void                      slot_twGroups_OnActivated(const QModelIndex &index);
};
//---------------------------------------------------------------------------
#endif // PickupDB_CPersonEditH
