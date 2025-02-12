// QJSONConfig Demo

#include <QApplication>
#include "qjsonconfig.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set information gor QSettings.
    QCoreApplication::setOrganizationName("MySoft");
    QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Star Runner");

    // Declare your config instance
    QJSONConfig cfg("conf.json" /* File Name */);

    // Write configurations
    // Currently we only support 4 types of the value of each config item:
    // int, QString, double, bool
    // It is ok by setValue(QString key, QVariant val).
    cfg["String"] = "name";
    cfg["Integer"] = 1;
    cfg["Boolean"] = true;
    cfg["Float"] = 1.8;

    // We also support sub-configuration
    cfg["Foo/Bar"] = 250;

    // Syncronize the config file
    cfg.sync();

    // Read
    // Similarly we support getValue(QString key).
    qDebug() << QString(cfg["String"]);
    qDebug() << int(cfg["Integer"]);
    qDebug() << bool(cfg["Boolean"]);
    qDebug() << double(cfg["Float"]);
    qDebug() << int(cfg["Foo/Bar"]);

    // Clear all the configuration
    // cfg.clear();

    return 0;
}
