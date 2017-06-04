#include "qbotnet.h"
#include <QtCore/QString>


QBotNet::QBotNet(QObject *parent)
{
}

void QBotNet::onLoad()
{
    log("Starting qBotNet");
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
