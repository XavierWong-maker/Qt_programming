#include <QCoreApplication>
#include "ServerDemo.h"
#include "ClientDemo.h"
#include "DefaultTxtMsgHandler.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    //Start server
    ServerDemo server;
    DefaultTxtMsgHandle serverHandler;
    server.setHandler(&serverHandler);
    if(!server.start(8890)){
        qDebug() << "Server failed to start";
        return 1;
    }

    //Start client
    ClientDemo client;
    DefaultTxtMsgHandle clientHandler;
    client.setHandler(&clientHandler);
    if(!client.connectTo("127.0.0.1", 8890)){
        qDebug() << "Client failed to connect";
        return 1;
    }

    //Send a Chinese message from client
    TextMessage tm("TEXT", "建立麦克卢汉");
    qint64 bytesSent = client.send(tm);
    qDebug() << "Client sent" << bytesSent << "bytes";


    // Run event loop
    return a.exec();
}
