/**
 * \file   CSqlCryptTableModel.h
 * \brief  SQL crypt table model
 */


#ifndef CSQLCRYPTTABLEMODEL_H
#define CSQLCRYPTTABLEMODEL_H
//---------------------------------------------------------------------------
#include "Common.h"

#include <xLib/Crypt/OpenSSL/CxBlowfish.h>
//---------------------------------------------------------------------------
class CSqlCryptTableModel :
    public QSqlTableModel
{
    public:
        enum ECryptAlgorithm {
            caUnknown,
            caBlowfish
        };


        explicit           CSqlCryptTableModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase(), const ECryptAlgorithm ccaCryptAlgorithm = caBlowfish);
            ///< constructor

        bool               setCryptKey        (const std::tstring_t &csCryptKey);
            ///< set crypto key
        virtual bool	   setData            (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
            ///< set encrypted data
        virtual QVariant   data               (const QModelIndex &index, int role = Qt::DisplayRole) const;
            ///< get decrypted data

    private:
        ECryptAlgorithm    _m_caCryptAlgorithm;    ///< crypt algorithm
        mutable CxBlowfish _m_bfBlowFish;          ///< implement blowfish algorithm

};
//---------------------------------------------------------------------------
#endif // CSQLCRYPTTABLEMODEL_H
