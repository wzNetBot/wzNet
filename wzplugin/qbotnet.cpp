#include "qbotnet.h"
#include <QString>
#include <QThread>
#include <thread>
#include <capnp/ez-rpc.h>
#include <kj/debug.h>
#include "../common/capnp/wzNet.capnp.h"

class WzNetImpl final: public WzNet::Host::Server {
public:
    WzNetImpl(IHostInterface* p){ iHost = p; }

  kj::Promise<void> wzVersion(WzVersionContext context) {
    context.getResults().setValue(iHost->gameVersion().toLatin1().data());
    return kj::READY_NOW;
  }
private:
  IHostInterface *iHost;
};

void startRPC(IHostInterface *iHost)
{
    capnp::EzRpcServer server(kj::heap<WzNetImpl>(iHost), "127.0.0.1", 5566);
    auto& waitScope = server.getWaitScope();
    iHost->err("test from srv");
    kj::NEVER_DONE.wait(waitScope);
}

QBotNet::QBotNet(QObject *parent)
{
}

void QBotNet::startRPCServer()
{
    std::thread t(startRPC, iHost);
    t.detach();
}

void QBotNet::evAttacked()
{
    log("Attacked");
}

void QBotNet::onLoad()
{
    log("Starting qBotNet");
    startRPCServer();
    log(QString("Warzone version: %1").arg(iHost->gameVersion()));
}

void QBotNet::err(QString msg)
{
    iHost->err(msg);
}

void QBotNet::log(QString msg)
{
    iHost->log(msg);
}

//#if QT_VERSION < 0x050000
//SAQ_EXPORT_PLUGIN2(qBotNet, QBotNet)
//#endif // QT_VERSION < 0x050000
