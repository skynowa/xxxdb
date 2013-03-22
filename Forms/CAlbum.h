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
    Ui::CAlbum      m_Ui;

                    CAlbum              (QWidget *parent,
                                         QSqlTableModel *tableModel,
                                         CSqlNavigator *sqlNavigator);
    virtual        ~CAlbum              ();

protected:
    virtual bool    eventFilter         (QObject *obj, QEvent *event);
    virtual void    showEvent           (QShowEvent *event);
    virtual void    resizeEvent         (QResizeEvent *event);
    virtual void    closeEvent          (QCloseEvent *event);

private:
    CSettings      *_m_stApp;
    QSqlTableModel *_m_tmModel;
    CSqlNavigator  *_m_snSqlNavigator;
    cint            _m_ciDbRecordIndex;
    db_images_t     _m_viDbItems;
    QPixmap         _m_pixPhoto;

    void            _construct          ();
    void            _destruct           ();
    void            _initMain           ();
    void            _initActions        ();

    void            _photoUpdate        ();

private Q_SLOTS:
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
