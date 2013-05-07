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
#include "../Classes/CConfig.h"
#include "../Classes/CDbImageLabel.h"
//------------------------------------------------------------------------------
class CAlbum :
    public QMainWindow
{
    Q_OBJECT

public:
    Ui::CAlbum      ui;

                    CAlbum(QWidget *parent, QSqlTableModel *tableModel,
                           CSqlNavigator *sqlNavigator);

protected:
    virtual bool    eventFilter(QObject *obj, QEvent *event);
    virtual void    showEvent(QShowEvent *event);
    virtual void    resizeEvent(QResizeEvent *event);
    virtual void    keyPressEvent(QKeyEvent *event);
    virtual void    closeEvent(QCloseEvent *event);

private:
    QSqlTableModel *_tmModel;
    CSqlNavigator  *_snSqlNavigator;
    cint            _ciDbRecordIndex;
    db_images_t     _viDbItems;
    QPixmap         _pixPhoto;

    void            _construct();
    void            _destruct();
    void            _initMain();
    void            _initActions();

    void            _photoUpdate();

    // slots
    // group "Exit"
    void            actFile_onExit();

    // group "Edit"
    void            actEdit_onSaveAs();
    void            actEdit_onFirst();
    void            actEdit_onPrior();
    void            actEdit_onNext();
    void            actEdit_onLast();
    void            actEdit_onGoTo();
    void            actEdit_onInsert();
    void            actEdit_onRemove();
    void            actEdit_onEdit();
    void            actEdit_onSetPrimary();

    // photo
    void            photo_onLoop();
    void            photoMini_onUpdate(cint &index);
    void            photoMini_onClicked(QLabel *label, cQString &dbFieldName);

Q_SIGNALS:
    void            sig_photo_clicked();
    void            sig_photoMini_clicked(QLabel *label, cQString &dbFieldName);

    friend class CIni;
};
//------------------------------------------------------------------------------
#endif // XXXDb_CAlbumH
