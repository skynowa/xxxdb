/**
 * \file   CSqlNavigator.cpp
 * \brief
 */


#include "CSqlNavigator.h"


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CSqlNavigator::CSqlNavigator(

) :
    QObject         (0),
    _m_tmTableModel (NULL),
    _m_tabvTableView(NULL)
{
}
//---------------------------------------------------------------------------
/*virtual*/
CSqlNavigator::~CSqlNavigator() {

}
//---------------------------------------------------------------------------
void
CSqlNavigator::Setup(
    QSqlTableModel *tmTableModel,
    QTableView     *tabvTableView
)
{
    _m_tmTableModel  = tmTableModel;
    _m_tabvTableView = tabvTableView;
}
//---------------------------------------------------------------------------
void
CSqlNavigator::First() {
    int iTargetRow = 0;

    _m_tabvTableView->selectRow(iTargetRow);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::Prior() {
    int iTargetRow = _m_tabvTableView->currentIndex().row() - 1;

    _m_tabvTableView->selectRow(iTargetRow);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::Next() {
    int iTargetRow = _m_tabvTableView->currentIndex().row() + 1;

    _m_tabvTableView->selectRow(iTargetRow);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::Last() {
    int iTargetRow = _m_tmTableModel->rowCount() - 1;

    _m_tabvTableView->selectRow(iTargetRow);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::Insert() {
    bool bRes = _m_tmTableModel->insertRow(_m_tmTableModel->rowCount());
    qCHECK_PTR(bRes, _m_tmTableModel);

    Refresh();
    Edit();
}
//---------------------------------------------------------------------------
void
CSqlNavigator::Delete() {
    int iTargetRow = _m_tabvTableView->currentIndex().row();

    bool bRes = _m_tabvTableView->model()->removeRow(iTargetRow);
    qCHECK_PTR(bRes, _m_tmTableModel);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::Edit() {
    const int   ciTargetCell = 1;

    int         iTargetRow   = _m_tabvTableView->currentIndex().row();
    QModelIndex miIndex      = _m_tmTableModel->index(iTargetRow, ciTargetCell);

    _m_tabvTableView->setCurrentIndex(miIndex);
    _m_tabvTableView->edit(miIndex);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::Post() {
    const int   ciTargetCell = 1;

    int         iTargetRow   = _m_tabvTableView->currentIndex().row();
    QModelIndex miIndex      = _m_tmTableModel->index(iTargetRow, ciTargetCell);

    _m_tabvTableView->setCurrentIndex(miIndex);
    _m_tabvTableView->update(miIndex);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::Cancel() {

}
//---------------------------------------------------------------------------
void
CSqlNavigator::Refresh() {
    bool bRes = _m_tmTableModel->select();
    qCHECK_PTR(bRes, _m_tmTableModel);

    int iTargetRow = _m_tabvTableView->currentIndex().row();

    _m_tabvTableView->selectRow(iTargetRow);
}
//---------------------------------------------------------------------------


