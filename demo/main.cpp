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
    cfg["name"] = "name";
    cfg["num"] = 1;
    cfg["Boolean"] = true;
    cfg["float"] = 1.8;

    // Syncronize the config file
    cfg.sync();

    // Read
    // Similarly we support getValue(QString key).
    qDebug() << cfg["name"];
    qDebug() << cfg["num"];
    qDebug() << cfg["Boolean"];
    qDebug() << cfg["float"];

    // Clear all the configuration
    // cfg.clear();

    return 0;
}
