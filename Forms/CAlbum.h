/**
 * \file   CAlbum.h
 * \brief  photo album
 */


#ifndef XXXDb_CAlbumH
#define XXXDb_CAlbumH
//------------------------------------------------------------------------------
#include "ui_CAlbum.h"

#include "../QtLib/Common.h"
#include "../QtLib/CSqlNavigator.h"
#include "../Config.h"
#include "../Classes/CDbImageLabel.h"
//------------------------------------------------------------------------------
class CSettings;

class CAlbum :
    public QMainWindow
{
    Q_OBJECT

public:
    friend class CSettings;

    Ui::CAlbum      ui;

                    CAlbum              (QWidget *parent,
                                         QSqlTableModel *tableModel,
                                         CSqlNavigator *sqlNavigator);

protected:
    virtual bool    eventFilter         (QObject *obj, QEvent *event);
    virtual void    showEvent           (QShowEvent *event);
    virtual void    resizeEvent         (QResizeEvent *event);
    virtual void    keyPressEvent       (QKeyEvent *event);
    virtual void    closeEvent          (QCloseEvent *event);

private:
    CSettings      *_stApp;
    QSqlTableModel *_tmModel;
    CSqlNavigator  *_snSqlNavigator;
    cint            _ciDbRecordIndex;
    db_images_t     _viDbItems;
    QPixmap         _pixPhoto;

    void            _construct          ();
    void            _destruct           ();
    void            _initMain           ();
    void            _initActions        ();

    void            _photoUpdate        ();

    // slots
    // group "Exit"
    void            slot_OnExit         ();

    // group "Edit"
    void            slot_OnSaveAs       ();
    void            slot_OnFirst        ();
    void            slot_OnPrior        ();
    void            slot_OnNext         ();
    void            slot_OnLast         ();
    void            slot_OnGoTo         ();
    void            slot_OnInsert       ();
    void            slot_OnRemove       ();
    void            slot_OnEdit         ();
    void            slot_OnSetPrimary   ();

    // photo
    void            slot_OnLoop         ();
    void            slot_OnPhotoUpdate  (cint &index);
    void            slot_photoMini_OnClicked(QLabel *label, cQString &dbFieldName);

Q_SIGNALS:
    void            signal_photo_clicked();
    void            signal_photoMini_clicked(QLabel *label, cQString &dbFieldName);
};
//------------------------------------------------------------------------------
#endif // XXXDb_CAlbumH
