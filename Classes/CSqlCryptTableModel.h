/**
 * \file   CSqlCryptTableModel.h
 * \brief  SQL crypt table model
 */


#ifndef CSQLCRYPTTABLEMODEL_H
#define CSQLCRYPTTABLEMODEL_H
//---------------------------------------------------------------------------
#include "../Common.h"

#include <xLib/Crypt/OpenSSL/CxBlowfish.h>
//---------------------------------------------------------------------------
class CSqlCryptTableModel :
    public QSqlTableModel
{
    public:
        explicit           CSqlCryptTableModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());

        BOOL               setKey             (const std::tstring &csKey);
            ///< set crypto key
        virtual bool	   setData            (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
            ///< set encrypted data
        virtual QVariant   data               (const QModelIndex &index, int role = Qt::DisplayRole) const;
            ///< get decrypted data

    private:
        mutable CxBlowfish _m_bfBlowFish;   ///< implement blowfish algorithm

};
//---------------------------------------------------------------------------
#endif // CSQLCRYPTTABLEMODEL_H
