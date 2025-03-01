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
    out << cfg["String"].toString() << Qt::endl;
    out << cfg["Integer"].toInt() << Qt::endl;
    out << cfg["Boolean"].toBool() << Qt::endl;
    out << cfg["Float"].toDouble() << Qt::endl;
    out << cfg["Foo/Bar"].toInt() << Qt::endl;
    out << cfg["Foo/Boo"].toInt() << Qt::endl;
    out << cfg["Foo/Bar/Boo"].toInt() << Qt::endl;

    // Clear all the configuration
    // cfg.clear();

    // Now use another to read those config items
    QJSONConfig cfgRead("conf.json");
    out << cfgRead["String"].toString() << Qt::endl;
    out << cfgRead["Integer"].toInt() << Qt::endl;
    out << cfgRead["Boolean"].toBool() << Qt::endl;
    out << cfgRead["Float"].toDouble() << Qt::endl;
    out << cfgRead["Foo/Bar"].toInt() << Qt::endl;
    out << cfgRead["Foo/Boo"].toInt() << Qt::endl;
    out << cfgRead["Foo/Bar/Boo"].toInt() << Qt::endl;

    // All keys, including sub-keys
    for (const QString &str : cfgRead.allFinalKeys())
        out << str << Qt::endl;

    // All keys, excluding sub-keys
    for (const QString &str : cfgRead.allKeys())
        out << str << Qt::endl;

    // Child keys, including sub-keys
    for (const QString &str : cfgRead.childKeys("Foo"))
        out << str << Qt::endl;

    return 0;
}
