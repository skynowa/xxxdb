/**
 * \file   CDelegateDbImage.h
 * \brief
 */


#ifndef XXXDb_CDelegateDbImageH
#define XXXDb_CDelegateDbImageH
//------------------------------------------------------------------------------
#include "../QtLib/Common.h"
#include "../QtLib/CUtils.h"
#include "../Config.h"
//------------------------------------------------------------------------------
class CDelegateDbImage :
    public QSqlRelationalDelegate
{
    Q_OBJECT

public:
                 CDelegateDbImage(QObject *parent, cint &imageFieldIndex,
                                  cQSize &size, QLabel *infoPanel);

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
                              const QModelIndex &index) const;

private:
    cint         _ciImageFieldIndex;
    cQSize       _cszSize;
    QLabel      *_lblInfoPanel;
};
//------------------------------------------------------------------------------
#endif // XXXDb_CDelegateDbImageH
