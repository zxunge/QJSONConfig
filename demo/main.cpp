// QJSONConfig Demo

#include <QApplication>

// If you want to use the unreliable Proxy class to 
// acheive "convenient access"(i.e. use operator[] to acheive both reading and writing), you need to
// define QJSONCFG_PROXY_USED before including the header.
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
    // It is not suggested to directly use operator[] (if QJSONCFG_PROXY_USED is defined)
    cfg.setValue("String", "name");
    cfg.setValue("Integer", 1);
    cfg.setValue("Boolean", true);
    cfg.setValue("Float", 1.8);

    // We also support sub-configuration
    cfg.setValue("Foo/Bar", 250);
    cfg.setValue("Foo/Boo", 150);
    cfg.setValue("Foo/Bar/Boo", 200);

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

    // Now use another to read those config items
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
