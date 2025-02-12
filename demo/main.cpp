// QJSONConfig Demo

#include <QApplication>
#include "qjsonconfig.h"
#include <QTextStream>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set information for QSettings.
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
    cfg["Foo/Boo"] = 150;
    cfg["Foo/Bar/Boo"] = 200;
    cfg["B/F/G/K"] = 200;

    // Syncronize the config file
    cfg.sync();

    // Read
    // Similarly we support getValue(QString key).
    QTextStream out(stdout);
    out << QString(cfg["String"]) << Qt::endl;
    out << int(cfg["Integer"]) << Qt::endl;
    out << bool(cfg["Boolean"]) << Qt::endl;
    out << double(cfg["Float"]) << Qt::endl;
    out << int(cfg["Foo/Bar"]) << Qt::endl;
    out << int(cfg["Foo/Boo"]) << Qt::endl;
    out << int(cfg["Foo/Bar/Boo"]) << Qt::endl;

    // Clear all the configuration
    // cfg.clear();

    return 0;
}
