#include "ClientDemo.h"
#include "ServerDemo.h"
#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>
#include <QThread>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerDemo server;
    server.start(8080);

    return a.exec();
}
