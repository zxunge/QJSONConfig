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

    QTextStream out(stdout);
    // Empty or not
    out << cfg.empty() << Qt::endl;
    
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

    // Syncronize the config file
    cfg.sync();

    // Read
    // Similarly we support getValue(QString key)
    out << QString(cfg["String"]) << Qt::endl;
    out << int(cfg["Integer"]) << Qt::endl;
    out << bool(cfg["Boolean"]) << Qt::endl;
    out << double(cfg["Float"]) << Qt::endl;
    out << int(cfg["Foo/Bar"]) << Qt::endl;
    out << int(cfg["Foo/Boo"]) << Qt::endl;
    out << int(cfg["Foo/Bar/Boo"]) << Qt::endl;

    // Clear all the configuration
    // cfg.clear();

    // Now use another to read those confug items
    QJSONConfig cfgRead("conf.json");
    out << QString(cfgRead["String"]) << Qt::endl;
    out << int(cfgRead["Integer"]) << Qt::endl;
    out << bool(cfgRead["Boolean"]) << Qt::endl;
    out << double(cfgRead["Float"]) << Qt::endl;
    out << int(cfgRead["Foo/Bar"]) << Qt::endl;
    out << int(cfgRead["Foo/Boo"]) << Qt::endl;
    out << int(cfgRead["Foo/Bar/Boo"]) << Qt::endl;

    return 0;
}
