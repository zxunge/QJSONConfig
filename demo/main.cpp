// QJSONConfig Demo

#include <QApplication>
#include "qjsonconfig.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("MySoft");
    QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Star Runner");
   
    QJSONConfig cfg;

    // Write configurations
    cfg["name"] = "name";
    cfg["num"] = 1;
    cfg.sync();

    // Read
    qDebug() << cfg["name"];
    qDebug() << cfg["num"];

    return a.exec();
}
