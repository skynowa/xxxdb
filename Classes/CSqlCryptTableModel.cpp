/**
 * \file   CSqlCryptTableModel.cpp
 * \brief  main widget
 */


#include "CSqlCryptTableModel.h"


//---------------------------------------------------------------------------
CSqlCryptTableModel::CSqlCryptTableModel(
    QObject     *parent /* = 0 */,
    QSqlDatabase db     /* = QSqlDatabase()*/
) :
    QSqlTableModel(parent, db)
{

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CSqlCryptTableModel::setData(
    const QModelIndex &index,
    const QVariant    &value,
    int                role /* = Qt::EditRole */
)
{
    qDebug() << "[setData] index: " << index.column();
    qDebug() << "[setData] value: " << value.toString();

    return QSqlTableModel::setData(index, value, role);
}
//---------------------------------------------------------------------------
/*virtual*/
QVariant
CSqlCryptTableModel::data(
    const QModelIndex &item,
    int                role /* = Qt::DisplayRole */
) const
{
    QVariant vRes;

    vRes = QSqlTableModel::data(item, role);
    qDebug() << "[data] item: " << vRes.toString();


    return vRes;
}
//---------------------------------------------------------------------------
