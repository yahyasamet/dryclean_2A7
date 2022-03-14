// #include "mainwindow.h"

#include <QCoreApplication>
#include "MessengerServer.h"

using namespace AslihanAkbiyik;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MessengerServer Server;
    if(!Server.startServer(3333)) {
        qDebug() << "Error:" << Server.errorString();
        return 1;
    }
    qDebug() << "Server started...";

    return a.exec();
}
