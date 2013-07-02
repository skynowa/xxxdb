/**
 * \file   CDbImagePlugin.cpp
 * \brief
 */


#include "CDbImage.h"
#include "CDbImagePlugin.h"

#include <QtPlugin>

//------------------------------------------------------------------------------
CDbImagePlugin::CDbImagePlugin(
    QObject *parent
) :
    QObject(parent)
{
    _initialized = false;
}
//------------------------------------------------------------------------------
void
CDbImagePlugin::initialize(
    QDesignerFormEditorInterface * /* core */
)
{
    if (_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    _initialized = true;
}
//------------------------------------------------------------------------------
bool
CDbImagePlugin::isInitialized() const
{
    return _initialized;
}
//------------------------------------------------------------------------------
QWidget *
CDbImagePlugin::createWidget(
    QWidget *parent
)
{
    return new CDbImage(parent);
}
//------------------------------------------------------------------------------
QString
CDbImagePlugin::name() const
{
    return QLatin1String("CDbImage");
}
//------------------------------------------------------------------------------
QString
CDbImagePlugin::group() const
{
    return QLatin1String("");
}
//------------------------------------------------------------------------------
QIcon
CDbImagePlugin::icon() const
{
    return QIcon();
}
//------------------------------------------------------------------------------
QString
CDbImagePlugin::toolTip() const
{
    return QLatin1String("");
}
//------------------------------------------------------------------------------
QString
CDbImagePlugin::whatsThis() const
{
    return QLatin1String("");
}
//------------------------------------------------------------------------------
bool
CDbImagePlugin::isContainer() const
{
    return false;
}
//------------------------------------------------------------------------------
QString
CDbImagePlugin::domXml() const
{
    return QLatin1String("<widget class=\"CDbImage\" name=\"cDbImage\">\n</widget>\n");
}
//------------------------------------------------------------------------------
QString
CDbImagePlugin::includeFile() const
{
    return QLatin1String("CDbImage.h");
}
//------------------------------------------------------------------------------
