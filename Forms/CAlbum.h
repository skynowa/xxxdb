/**
 * \file   CAlbum.h
 * \brief  photo album
 */


#ifndef XXXDb_CAlbumH
#define XXXDb_CAlbumH
//-------------------------------------------------------------------------------------------------
#include "ui_CAlbum.h"

#include <QtLib/Common.h>
#include <QtLib/CSqlNavigator.h>
#include <xLib/xLib.h>
#include "../Classes/CConfig.h"
//-------------------------------------------------------------------------------------------------
class CAlbum :
    public QMainWindow
{
    Q_OBJECT

public:
    Ui::CAlbum      ui;

                    CAlbum(QWidget *parent, QSqlTableModel *tableModel,
                        CSqlNavigator *sqlNavigator);

protected:
    virtual void    showEvent(QShowEvent *event);
    virtual void    resizeEvent(QResizeEvent *event);
    virtual void    keyPressEvent(QKeyEvent *event);
    virtual void    closeEvent(QCloseEvent *event);

private:
    QSqlTableModel *_tmModel;
    CSqlNavigator  *_snSqlNavigator;
    cint            _ciDbRecordIndex;
    CDbImageCollection _dbItems;
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
    void            photoMini_onUpdate(cint &index);        // FIX:
    void            photoMini_onClicked(QObject *sender);   // FIX:

    friend class CIni;
};
//-------------------------------------------------------------------------------------------------
#endif // XXXDb_CAlbumH
