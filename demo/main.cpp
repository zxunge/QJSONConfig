// QJSONConfig Demo

#include <QApplication>

// If you want to use the unreliable Proxy class to 
// acheive "convenient access"(i.e. use operator[] for both reading and writing), you need to
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

    // Clear all the configuration
    // cfg.clear();

    // Now use another object to read those config items
    QJSONConfig cfgRead("conf.json");
    
    // Read
    // Similarly we support getValue(QString key)
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

    // Remove a specific key
    cfgRead.remove("Foo/Bar/Boo");
    for (const QString &str : cfgRead.allFinalKeys())
        out << str << Qt::endl;
        
    // Contains the key?
    out << cfgRead.contains("Foo") << Qt::endl;
    out << cfgRead.contains("Foo/Bar") << Qt::endl;
    
    // What's the configuration file's name?
    out << cfgRead.fileName() << Qt::endl;

    return 0;
}
