/**
 * \file   CPhotoAlbum.h
 * \brief  photo album
 */


#ifndef PickupDB_CPhotoAlbumH
#define PickupDB_CPhotoAlbumH
//------------------------------------------------------------------------------
#include "ui_CPhotoAlbum.h"

#include "../QtLib/Common.h"
#include "../QtLib/CSqlNavigator.h"
#include "../Config.h"
#include "../Classes/CDbImageLabel.h"
//------------------------------------------------------------------------------
class CPhotoAlbum :
    public QMainWindow
{
    Q_OBJECT

public:
    Ui::CPhotoAlbum    m_Ui;

                       CPhotoAlbum        (QWidget *parent,
                                           QSqlTableModel *tableModel,
                                           CSqlNavigator *sqlNavigator);
    virtual           ~CPhotoAlbum        ();

protected:
    virtual bool       eventFilter        (QObject *obj, QEvent *event);
    virtual void       showEvent          (QShowEvent *event);
    virtual void       resizeEvent        (QResizeEvent *event);

private:
    QSqlTableModel    *_m_tmModel;
    CSqlNavigator     *_m_snSqlNavigator;
    cint               _m_ciDbRecordIndex;
    db_images_t        _m_viDbItems;
    QPixmap            _m_pixPixmap;

    void               _construct         ();
    void               _destruct          ();
    void               _initMain          ();
    void               _initActions       ();

private Q_SLOTS:
    // group "Exit"
    void               slot_OnExit        ();

    // group "Edit"
    void               slot_OnSaveAs      ();
    void               slot_OnFirst       ();
    void               slot_OnPrior       ();
    void               slot_OnNext        ();
    void               slot_OnLast        ();
    void               slot_OnGoTo        ();
    void               slot_OnInsert      ();
    void               slot_OnRemove      ();
    void               slot_OnEdit        ();
    void               slot_OnSetPrimary  ();

    // photo
    void               slot_OnLoop        ();
    void               slot_OnPhotoUpdate (cint &index);
    void               slot_photoMini_OnClicked(QLabel *label,
                                                cQString &dbFieldName);
};
//------------------------------------------------------------------------------
#endif // PickupDB_CPhotoAlbumH
