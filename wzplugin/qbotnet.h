#ifndef QBOTNET_H
#define QBOTNET_H

#include "../warzone2100/lib/qtplugins/qtpluginsinterface.h"

class QBotNet : public IPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGINS_INTERFACE_VERSION FILE "qBotNet.json")
    Q_INTERFACES(IPluginInterface)

public:
    QBotNet(QObject *parent = 0);
    void err(QString);
    void log(QString);
    void onLoad();

    void setHostInterface(IHostInterface *host) {iHost = host;}

    // game events
    void onStart() {}
    void onEnd(bool) {}
    void onFrame() {}


private:
    IHostInterface *iHost;
};

#endif // QBOTNET_H
