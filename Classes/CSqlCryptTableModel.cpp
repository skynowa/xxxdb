/**
 * \file   CSqlCryptTableModel.cpp
 * \brief  SQL crypt table model
 */


#include "CSqlCryptTableModel.h"


//---------------------------------------------------------------------------
CSqlCryptTableModel::CSqlCryptTableModel(
    QObject               *parent            /* = 0 */,
    QSqlDatabase           db                /* = QSqlDatabase()*/,
    const ECryptAlgorithm  ccaCryptAlgorithm /* = caBlowfish*/
) :
    QSqlTableModel     (parent, db),
    _m_caCryptAlgorithm(ccaCryptAlgorithm),
    _m_bfBlowFish      ()
{

}
//---------------------------------------------------------------------------
bool
CSqlCryptTableModel::setCryptKey(
    const std::tstring_t &csKey
)
{
    return _m_bfBlowFish.bSetKey(csKey);
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
    //qDebug() << "[setData] index: " << index.column();
    //qDebug() << "[setData] value: " << value.toString();


    QVariant vOut;

    if (1 == index.column() && !value.isNull()) {
        QByteArray baIn = value.toByteArray();
        QByteArray baOut; baOut.resize(baIn.size());
        int        iNum = 0; // must be zero

        _m_bfBlowFish.bEncryptCfb64((uchar_t *)baIn.data(), (uchar_t *)baOut.data(), baIn.size(), &iNum, CxBlowfish::cmEncrypt);

        vOut = baOut;
    } else {
        vOut = value;
    }

    return QSqlTableModel::setData(index, vOut, role);
}
//---------------------------------------------------------------------------
/*virtual*/
QVariant
CSqlCryptTableModel::data(
    const QModelIndex &index,
    int                role /* = Qt::DisplayRole */
) const
{
    //qDebug() << "[data] index: " << index.column();
    //qDebug() << "[data] value: " << QSqlTableModel::data(index, role).toString();


    QVariant vRes;

    //TODO: which fields should be encrypted
    if (1 == index.column() && !QSqlTableModel::data(index, role).isNull()) {
        QByteArray baIn = QSqlTableModel::data(index, role).toByteArray();
        QByteArray baOut; baOut.resize(baIn.size());
        int        iNum = 0; // must be zero

        _m_bfBlowFish.bEncryptCfb64((uchar_t *)baIn.data(), (uchar_t *)baOut.data(), baIn.size(), &iNum, CxBlowfish::cmDecrypt);

        vRes = baOut;
    } else {
        vRes = QSqlTableModel::data(index, role);
    }

    return vRes;
}
//---------------------------------------------------------------------------
