#include "CDbImage.h"
#include "CDbImagePlugin.h"

#include <QtPlugin>

CDbImagePlugin::CDbImagePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void CDbImagePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;
    
    // Add extension registrations, etc. here
    
    m_initialized = true;
}

bool CDbImagePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CDbImagePlugin::createWidget(QWidget *parent)
{
    return new CDbImage(parent);
}

QString CDbImagePlugin::name() const
{
    return QLatin1String("CDbImage");
}

QString CDbImagePlugin::group() const
{
    return QLatin1String("");
}

QIcon CDbImagePlugin::icon() const
{
    return QIcon();
}

QString CDbImagePlugin::toolTip() const
{
    return QLatin1String("");
}

QString CDbImagePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CDbImagePlugin::isContainer() const
{
    return false;
}

QString CDbImagePlugin::domXml() const
{
    return QLatin1String("<widget class=\"CDbImage\" name=\"cDbImage\">\n</widget>\n");
}

QString CDbImagePlugin::includeFile() const
{
    return QLatin1String("CDbImage.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(CDbImagePlugin, CDbImagePlugin)
#endif // QT_VERSION < 0x050000
