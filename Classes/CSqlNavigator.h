/**
 * \file   CSqlNavigator.h
 * \brief
 */


#ifndef xLib_CSqlNavigatorH
#define xLib_CSqlNavigatorH
//---------------------------------------------------------------------------
#include "Common.h"
//---------------------------------------------------------------------------
class CSqlNavigator :
    public QObject
{
        Q_OBJECT

    public:
                        CSqlNavigator();
                            ///< constructor
        virtual        ~CSqlNavigator();

        void            Setup        (QSqlTableModel *tmTableModel, QTableView *tabvTableView);

    public slots:
        void            First        ();
        void            Prior        ();
        void            Next         ();
        void            Last         ();
        void            Insert       ();
        void            Delete       ();
        void            Edit         ();
        void            Post         ();
        void            Cancel       ();
        void            Refresh      ();

    private:
        QSqlTableModel *_m_tmTableModel;
        QTableView     *_m_tabvTableView;

};
//---------------------------------------------------------------------------
#endif //xLib_CSqlNavigatorH
