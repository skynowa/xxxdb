/**
 * \file   CPhotoAlbum.h
 * \brief  photo album
 */


#ifndef PickupDB_CPhotoAlbumH
#define PickupDB_CPhotoAlbumH
//---------------------------------------------------------------------------
#include "ui_CPhotoAlbum.h"

#include "../QtLib/Common.h"
#include "../Config.h"
//---------------------------------------------------------------------------
class CPhotoAlbum :
    public QDialog
{
        Q_OBJECT

    public:
        Ui::CPhotoAlbum     m_Ui;

                            CPhotoAlbum (QWidget *parent, QSqlTableModel *tableModel,
                                         const int &currentRow);
        virtual            ~CPhotoAlbum ();

        QSqlTableModel     *_m_tmModel;
        const int           _m_ciCurrentRow;

    private:
        void                _construct  ();
        void                _destruct   ();
        void                _initMain   ();

        QDataWidgetMapper  *_dbWidgetMap(QWidget *widget, const QString &dbFieldName,
                                         const QSize &size);

    private Q_SLOTS:

};
//---------------------------------------------------------------------------
#endif // PickupDB_CPhotoAlbumH

