/**
 * \file   CDbImagePlugin.cpp
 * \brief
 */


#include "CDbImage.h"
#include "CDbImagePlugin.h"

#include <QtPlugin>

//------------------------------------------------------------------------------
CDbImagePlugin::CDbImagePlugin() :
    _initialized(false)
{
}
//------------------------------------------------------------------------------
QWidget *
CDbImagePlugin::construct(
    QWidget        *a_parent,           ///< parent QWidget
    QSqlTableModel *a_tableModel,       ///< QSqlTableModel
    cQString       &a_dbFieldName,      ///< DB field name
    cint           &a_index,            ///< index
    cint           &a_dbRecordIndex,    ///< DB record index
    cQSize         &a_size,             ///< image sizes
    QLabel         *a_info              ///< QLabel for display image
)
{
    return new CDbImage(a_parent, a_tableModel, a_dbFieldName, a_index,
                        a_dbRecordIndex, a_size, a_info);
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
    QWidget *a_parent /* = NULL */
)
{
    return new CDbImage(a_parent);
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
    return QLatin1String(
           "<widget class=\"CDbImage\" name=\"cDbImage\">\n"
           " <property name=\"geometry\">\n"
           "  <rect>\n"
           "   <x>0</x>\n"
           "   <y>0</y>\n"
           "   <width>120</width>\n"
           "   <height>80</height>\n"
           "  </rect>\n"
           " </property>\n"
           " <property name=\"toolTip\" >\n"
           "  <string>CDbImage</string>\n"
           " </property>\n"
           " <property name=\"whatsThis\" >\n"
           "  <string>CDbImage</string>\n"
           " </property>\n"
           " </widget>\n");
}
//------------------------------------------------------------------------------
QString
CDbImagePlugin::includeFile() const
{
    return QLatin1String("CDbImage.h");
}
//------------------------------------------------------------------------------