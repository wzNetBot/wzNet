#include "qtplugins.h"
#include <QString>
#include <QDir>
#include <QPluginLoader>
#include "../framework/frame.h"
#include "../../src/version.h"
#include "../../src/objects.h"
#include "../../src/objmem.h"

QtPluginsEngine *pe;

bool initPlugins()
{
    debug(LOG_INFO, "initialize plugins");
    pe = new QtPluginsEngine();
    debug(LOG_INFO, version_getVersionString());
    return true;
}

bool preparePlugins()
{
    debug(LOG_INFO, "plugins preparations");
    return true;
}

bool shutdownPlugins()
{
    return true;
}

bool updatePlugins()
{
//    debug(LOG_INFO,"updatePlugins called");
    if (pe) pe->update();
    return true;
}

QString QtPluginsEngine::gameVersion()
{
    return QString(version_getVersionString());
}

void QtPluginsEngine::update()
{
//    log("update engine");
    BASE_OBJECT *psCurr;
    BASE_OBJECT *psList = (BASE_OBJECT*)apsDroidLists[0];

    for (psCurr = psList; psCurr; psCurr = psCurr->psNext)
    {
        if (psCurr->type == OBJ_DROID)
        {
            log(objInfo(psCurr));
        }
    }
}

QtPluginsEngine::QtPluginsEngine()
{
    loadPlugin();
    return;
}

QtPluginsEngine::~QtPluginsEngine()
{
    return;
}

bool QtPluginsEngine::loadPlugin()
{
    log("Trying to load plugins");
    QDir pluginsDir("/home/scor/tmp/warzone-plugins/");
    pluginsDir.cd("plugins");
    const QString filter = "lib*.so";
    foreach (QString fileName, pluginsDir.entryList(QStringList() << filter, QDir::NoDotAndDotDot | QDir::Files)) {
        log(QString("found plugin: %1").arg(pluginsDir.absoluteFilePath(fileName)));
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            log("cast plugin pointer to IPluginInterface...");
            iPluginInterface = qobject_cast<IPluginInterface *>(plugin);
            if (iPluginInterface){
                log("OK");
                iPluginInterface->setHostInterface(qobject_cast<IHostInterface *>(this));
                iPluginInterface->onLoad();
                return true;
            }else{
                err("FAILED");
            }
        }else{
            err("plugin instancing failed");
            err(QString("err: %1").arg(pluginLoader.errorString()));
        }
    }
    return false;
}

void QtPluginsEngine::err(QString msg)
{
    debug(LOG_ERROR, QString("[PluginsEngine] ERROR: %1").arg(msg).toLatin1());
    return;
}

void QtPluginsEngine::log(QString msg)
{
    debug(LOG_INFO, QString("[PluginsEngine] INFO: %1").arg(msg).toLatin1());
    return;
}

void QtPluginsEngine::getPluginVersion()
{
    return;
}
