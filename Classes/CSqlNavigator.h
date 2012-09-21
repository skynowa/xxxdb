/**
 * \file   CSqlNavigator.h
 * \brief
 */


#ifndef PickupDb_CSqlNavigatorH
#define PickupDb_CSqlNavigatorH
//---------------------------------------------------------------------------
#include "../QtLib/Common.h"
//---------------------------------------------------------------------------
class CSqlNavigator :
    public QObject
{
        Q_OBJECT

    public:
        explicit        CSqlNavigator(QWidget *parent);
        virtual        ~CSqlNavigator();

        void            setup        (QSqlTableModel *tmTableModel, QTableView *tabvTableView);

        void            first        ();
        void            prior        ();
        void            next         ();
        void            last         ();
        void            insert       ();
        void            remove       ();
        void            edit         ();
        void            post         ();
        void            cancel       ();
        void            refresh      ();

    private:
        QSqlTableModel *_m_tmTableModel;
        QTableView     *_m_tabvTableView;

};
//---------------------------------------------------------------------------
#endif // PickupDb_CSqlNavigatorH
