/**
 * \file   CPhotoAlbum.h
 * \brief  photo album
 */


#ifndef PickupDB_CPhotoAlbumH
#define PickupDB_CPhotoAlbumH
//-----------------------------------------------------------------------------
#include "ui_CPhotoAlbum.h"

#include "../QtLib/Common.h"
#include "../Config.h"
#include "../Classes/CDbImage.h"
#include "../Classes/CImageItem.h"
//-----------------------------------------------------------------------------
class CPhotoAlbum :
    public QMainWindow
{
    Q_OBJECT

public:
    Ui::CPhotoAlbum    m_Ui;

                       CPhotoAlbum        (QWidget *parent, QSqlTableModel *tableModel,
                                           const int &currentRow);
    virtual           ~CPhotoAlbum        ();

protected:
    virtual bool       eventFilter        (QObject *obj, QEvent *event);
    virtual void       showEvent          (QShowEvent *event);
    virtual void       resizeEvent        (QResizeEvent *event);

private:
    QSqlTableModel    *_m_tmModel;
    const int          _m_ciCurrentRow;
    db_items_t         _m_viDbItems;
    QPixmap            _m_pixPixmap;

    void               _construct         ();
    void               _destruct          ();
    void               _initMain          ();
    void               _initActions       ();

    QDataWidgetMapper *_dbWidgetMap       (QWidget *widget, const QString &dbFieldName,
                                           const QSize &size);

private Q_SLOTS:
    // group "Exit"
    void               slot_OnExit        ();

    // group "Edit"
    void               slot_OnSaveAs      ();
    void               slot_OnFirst       ();
    void               slot_OnPrior       ();
    void               slot_OnNext        ();
    void               slot_OnLast        ();
    void               slot_OnTo          ();
    void               slot_OnInsert      ();
    void               slot_OnRemove      ();
    void               slot_OnEdit        ();
    void               slot_OnSetPrimary  ();

    // photo
    void               photoMini_OnClicked(QLabel *label, const QString &dbFieldName);
};
//-----------------------------------------------------------------------------
#endif // PickupDB_CPhotoAlbumH
