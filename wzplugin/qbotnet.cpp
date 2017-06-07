#include "qbotnet.h"
#include <QString>
#include <QThread>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <capnp/ez-rpc.h>
#include <kj/debug.h>
#include "../common/capnp/wzNet.capnp.h"

std::mutex m;
std::condition_variable cv;
std::string evPayload;
bool stopEvListener(false);
bool ready(false);
bool done(false);

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

void evListener()
{
    while(!stopEvListener){
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return ready;});
        std::cout << "event triggered: " << evPayload << std::endl;
        done = true;
        ready = false;
        lk.unlock();
        cv.notify_one();
    }
}

void startRPC(IHostInterface *iHost)
{
    capnp::EzRpcServer server(kj::heap<WzNetImpl>(iHost), "127.0.0.1", 5566);
    auto& waitScope = server.getWaitScope();
    iHost->log("RPC server started...");
    std::thread cb(evListener);
    kj::NEVER_DONE.wait(waitScope);
}

QBotNet::QBotNet(QObject *parent)
{
}
QBotNet::~QBotNet()
{
    stopEvListener = true;
}

void QBotNet::startRPCServer()
{
    std::thread t(startRPC, iHost);
    t.detach();
}

void QBotNet::evAttacked()
{
    {
    std::lock_guard<std::mutex> lk(m);
    evPayload = "event: attacked!";
    ready = true;
    done = false;
    }
    cv.notify_one();
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return done;});
    }
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
