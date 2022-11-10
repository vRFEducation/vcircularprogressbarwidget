#include "VCircularProgressBar.h"
#include "VCircularProgressBarPlugin.h"

#include <QtPlugin>

VCircularProgressBarPlugin::VCircularProgressBarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void VCircularProgressBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool VCircularProgressBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *VCircularProgressBarPlugin::createWidget(QWidget *parent)
{
    return new VCircularProgressBar(parent);
}

QString VCircularProgressBarPlugin::name() const
{
    return QLatin1String("VCircularProgressBar");
}

QString VCircularProgressBarPlugin::group() const
{
    return QLatin1String("vrfEducation Widgets");
}

QIcon VCircularProgressBarPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon.jpg"));
}

QString VCircularProgressBarPlugin::toolTip() const
{
    return QLatin1String("This is a ProgressBar");
}

QString VCircularProgressBarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool VCircularProgressBarPlugin::isContainer() const
{
    return false;
}

QString VCircularProgressBarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"VCircularProgressBar\" name=\"vCircularProgressBar\">\n"
                         "<property name=\"geometry\"><rect><width>320</width><height>320</height></rect></property>"
                         "</widget>\n");
}

QString VCircularProgressBarPlugin::includeFile() const
{
    return QLatin1String("VCircularProgressBar.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(VCircularProgressBarPlugin, VCircularProgressBarPlugin)
#endif // QT_VERSION < 0x050000
