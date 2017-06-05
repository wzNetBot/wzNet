#ifndef QTPLUGINSINTERFACE_H
#define QTPLUGINSINTERFACE_H
//#include <QString>

#define IHOST_INTERFACE_VERSION "net.wz2100.Plugins.IHostInterface/0.0.2"
#define PLUGINS_INTERFACE_VERSION "net.wz2100.Plugins.IPluginInterface/0.0.2"

typedef int Player;

class IHostInterface
{
public:
    virtual ~IHostInterface() {}
    virtual void log(QString msg) = 0;
    virtual void err(QString msg) = 0;

    // wz callbacks
    virtual void update() = 0;

    // game info
    virtual QString gameVersion() = 0;
};

class IPluginInterface
{
public:
    virtual ~IPluginInterface() {}
    //virtual QString version() = 0;
    virtual void setHostInterface(IHostInterface*) = 0;

    // engine event callbacks
    virtual void onLoad() = 0;
    virtual void onStart() = 0;
    virtual void onEnd(bool isWinner) = 0; // i'm win?
    virtual void onFrame() = 0;

    // inGame events callbacks

    // inGame actions

};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(IHostInterface, IHOST_INTERFACE_VERSION);
Q_DECLARE_INTERFACE(IPluginInterface, PLUGINS_INTERFACE_VERSION);
QT_END_NAMESPACE

#endif // QTPLUGINSINTERFACE_H
