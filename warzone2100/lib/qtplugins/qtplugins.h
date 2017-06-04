#ifndef QTPLUGINS_H
#define QTPLUGINS_H

#include <QObject>
#include <QList>
#include <QString>
#include "qtpluginsinterface.h"

//#define PLUGINS_INTERFACE_VERSION "net.wz2100.Plugin.IHostInterface/0.0.2"

class QtPluginsEngine;
extern QtPluginsEngine* qtPlugins;

bool initPlugins();
bool preparePlugins();
bool shutdownPlugins();
bool updatePlugins();

class QtPluginsEngine : public QObject, public IHostInterface
//class QtPluginsEngine : public IHostInterface
{
    Q_OBJECT
    Q_INTERFACES(IHostInterface)

public:
    QtPluginsEngine();
    ~QtPluginsEngine();
    void log(QString msg);
    void err(QString msg);

    // game info
    QString gameVersion();

private:
    IPluginInterface *iPluginInterface;
    bool loadPlugin();

public slots:
    void getPluginVersion();
};
#endif // QTPLUGINS_H
