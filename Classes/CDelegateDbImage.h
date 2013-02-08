/**
 * \file   CDelegateDbImage.h
 * \brief
 */


#ifndef PickupDb_CDelegateDbImageH
#define PickupDb_CDelegateDbImageH
//---------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "../Config.h"
//---------------------------------------------------------------------------
class CDelegateDbImage :
    public QSqlRelationalDelegate
{
    Q_OBJECT

public:
                 CDelegateDbImage(QObject *parent, const int &imageFieldIndex,
                                  const QSize &size, QLabel *infoPanel = NULL);

    virtual void setEditorData   (QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData    (QWidget *editor, QAbstractItemModel *model,
                                  const QModelIndex &index) const;

private:
    const int    _m_ciImageFieldIndex;
    const QSize  _m_cszSize;
    QLabel      *_m_lblInfoPanel;
};
//---------------------------------------------------------------------------
#endif // PickupDb_CDelegateDbImageH
