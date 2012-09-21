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
    QWidget *parent
) :
    QObject         (parent),
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
CSqlNavigator::setup(
    QSqlTableModel *tmTableModel,
    QTableView     *tabvTableView
)
{
    Q_ASSERT(NULL != tmTableModel);
    Q_ASSERT(NULL != tabvTableView);

    _m_tmTableModel  = tmTableModel;
    _m_tabvTableView = tabvTableView;
}
//---------------------------------------------------------------------------
void
CSqlNavigator::first() {
    int iTargetRow = 0;

    _m_tabvTableView->selectRow(iTargetRow);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::prior() {
    int iTargetRow = _m_tabvTableView->currentIndex().row() - 1;

    _m_tabvTableView->selectRow(iTargetRow);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::next() {
    int iTargetRow = _m_tabvTableView->currentIndex().row() + 1;

    _m_tabvTableView->selectRow(iTargetRow);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::last() {
    int iTargetRow = _m_tmTableModel->rowCount() - 1;

    _m_tabvTableView->selectRow(iTargetRow);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::insert() {
    bool bRes = _m_tmTableModel->insertRow(_m_tmTableModel->rowCount());
    qCHECK_PTR(bRes, _m_tmTableModel);

    refresh();
    edit();
}
//---------------------------------------------------------------------------
void
CSqlNavigator::remove() {
    int iTargetRow = _m_tabvTableView->currentIndex().row();
    qCHECK_DO(- 1 == iTargetRow, return);

    bool bRes = _m_tabvTableView->model()->removeRow(iTargetRow);
    qCHECK_PTR(bRes, _m_tmTableModel);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::edit() {
    const int   ciTargetCell = 1;

    int         iTargetRow   = _m_tabvTableView->currentIndex().row();
    QModelIndex miIndex      = _m_tmTableModel->index(iTargetRow, ciTargetCell);

    _m_tabvTableView->setCurrentIndex(miIndex);
    _m_tabvTableView->edit(miIndex);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::post() {
    const int   ciTargetCell = 1;

    int         iTargetRow   = _m_tabvTableView->currentIndex().row();
    QModelIndex miIndex      = _m_tmTableModel->index(iTargetRow, ciTargetCell);

    _m_tabvTableView->setCurrentIndex(miIndex);
    _m_tabvTableView->update(miIndex);
}
//---------------------------------------------------------------------------
void
CSqlNavigator::cancel() {

}
//---------------------------------------------------------------------------
void
CSqlNavigator::refresh() {
    bool bRes = _m_tmTableModel->select();
    qCHECK_PTR(bRes, _m_tmTableModel);

    int iTargetRow = _m_tabvTableView->currentIndex().row();

    _m_tabvTableView->selectRow(iTargetRow);
}
//---------------------------------------------------------------------------



