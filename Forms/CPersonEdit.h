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

#include "CMain.h"
//---------------------------------------------------------------------------
class CPersonEdit :
    public QDialog
{
        Q_OBJECT

    public:
        Ui::CPersonEdit          m_Ui;

                                 CPersonEdit(QWidget *parent, QSqlTableModel *tableModel,
                                             const int &currentRow);
        virtual                 ~CPersonEdit();

    private:
        QList<QTreeWidgetItem *> _m_ltwGroups;
        QSqlTableModel          *_m_tmModel;
        QDataWidgetMapper       *_m_dmMapper;
        const int                _m_ciCurrentRow;
        QByteArray               _m_baPhoto;

        void                     _construct();
        void                     _destruct ();
        void                     _initMain ();

        void                     _resetAll ();
        void                     _saveAll  ();

    private Q_SLOTS:
        void                     slot_tbtnPhotoChange_OnClicked();
        void                     slot_tbtnPhotoDelete_OnClicked();
        void                     slot_tbtnPhotoSaveAs_OnClicked();

        void                     slot_bbxButtons_OnClicked(QAbstractButton *button);
        void                     slot_twGroups_OnActivated(const QModelIndex &index);
};
//---------------------------------------------------------------------------
#endif // PickupDB_CPersonEditH
