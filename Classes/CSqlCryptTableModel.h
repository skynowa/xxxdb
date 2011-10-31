/**
 * \file   CSqlCryptTableModel.h
 * \brief  main widget
 */


#ifndef CSQLCRYPTTABLEMODEL_H
#define CSQLCRYPTTABLEMODEL_H
//---------------------------------------------------------------------------
#include <QSqlTableModel>

#include <QtGlobal>
#include <QDebug>
//---------------------------------------------------------------------------
class CSqlCryptTableModel :
    public QSqlTableModel
{
    public:
        explicit CSqlCryptTableModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());

        virtual bool	 setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
        virtual QVariant data   (const QModelIndex &item, int role = Qt::DisplayRole) const;

};
//---------------------------------------------------------------------------
#endif // CSQLCRYPTTABLEMODEL_H
