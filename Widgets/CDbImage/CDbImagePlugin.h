/**
 * \file   CDbImagePlugin.h
 * \brief
 */


#ifndef CDBIMAGEPLUGIN_H
#define CDBIMAGEPLUGIN_H
//------------------------------------------------------------------------------
#include "../../QtLib/Common.h"
#include "../../QtLib/CUtils.h"
#include "../../Classes/CConfig.h"

#include <QDesignerCustomWidgetInterface>
//------------------------------------------------------------------------------
class CDbImagePlugin :
    public QObject,
    public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")

public:
             CDbImagePlugin(QObject *parent = 0);

    bool     isContainer() const;
    bool     isInitialized() const;
    QIcon    icon() const;
    QString  domXml() const;
    QString  group() const;
    QString  includeFile() const;
    QString  name() const;
    QString  toolTip() const;
    QString  whatsThis() const;
    QWidget *createWidget(QWidget *parent = NULL);
#if 0
    QWidget *createWidget(QWidget *parent, QSqlTableModel *tableModel,
                          cQString &dbFieldName, cint &index,
                          cint &dbRecordIndex,
                          QLabel *label, cQSize &size,
                          QLabel *info);
#endif
    void     initialize(QDesignerFormEditorInterface *core);

private:
    bool     _initialized;
};
//------------------------------------------------------------------------------
#endif
