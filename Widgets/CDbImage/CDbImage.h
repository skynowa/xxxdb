/**
 * \file   CDbImage.h
 * \brief
 */


#ifndef CDBIMAGE_H
#define CDBIMAGE_H
//------------------------------------------------------------------------------
#include <QLabel>
//------------------------------------------------------------------------------
class CDbImage :
    public QLabel
{
    Q_OBJECT

public:
    CDbImage(QWidget *parent = NULL);
};
//------------------------------------------------------------------------------
#endif
