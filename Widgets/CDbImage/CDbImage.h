#ifndef CDBIMAGE_H
#define CDBIMAGE_H

#include <QLabel>
#include <QtDesigner/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT CDbImage : public QLabel
{
    Q_OBJECT

public:
    CDbImage(QWidget *parent = 0);
};

#endif
