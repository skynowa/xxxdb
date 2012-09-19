/**
 * \file   CPersonEdit.h
 * \brief  edit person data
 */


#ifndef PickupDB_CPersonEditH
#define PickupDB_CPersonEditH
//---------------------------------------------------------------------------
#include "ui_CPersonEdit.h"

#include "../Config.h"
#include "../QtLib/Common.h"
//---------------------------------------------------------------------------
class CPersonEdit :
    public QDialog
{
        Q_OBJECT

    public:
        Ui::CPersonEdit          m_Ui;

        explicit                 CPersonEdit(QWidget *parent = 0);
        virtual                 ~CPersonEdit();

    private:
        QList<QTreeWidgetItem *> _m_ltwGroups;

        void                     _construct ();
        void                     _destruct  ();
        void                     _initMain  ();

    private Q_SLOTS:
        void                     slot_bbxButtons_OnClicked(QAbstractButton *button);
};
//---------------------------------------------------------------------------
#endif // PickupDB_CPersonEditH
