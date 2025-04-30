#include "ServerDemo.h"
#include <QTcpSocket>

ServerDemo::ServerDemo(QObject *parent)
    : QObject{parent}
{
    connect(&m_server, &QTcpServer::newConnection, this, &ServerDemo::onNewConnection);
}

void ServerDemo::onNewConnection(){
    qDebug() << "onNewConnection";

    while (m_server.hasPendingConnections()) {
        QTcpSocket *tcp = m_server.nextPendingConnection();
        tcp->setParent(this);

        connect(tcp, &QTcpSocket::connected, this, &ServerDemo::onConnected);
        connect(tcp, &QTcpSocket::disconnected, this, &ServerDemo::onDisconnected);
        connect(tcp, &QTcpSocket::readyRead, this, &ServerDemo::onDataReady);
        connect(tcp, &QTcpSocket::bytesWritten, this, &ServerDemo::onBytesWritten);
    }
}

void ServerDemo::onConnected(){
    auto *tcp = qobject_cast<QTcpSocket*>(sender());
    if(tcp){
        qDebug() << "onConnected";
        qDebug() << "Local Address:" << tcp->localAddress();
        qDebug() << "Local Port:" << tcp->localPort();
    }
}

void ServerDemo::onDisconnected(){
    auto *tcp = qobject_cast<QTcpSocket*>(sender());
    if(tcp){
        qDebug() << "onDisconnected";
        tcp->deleteLater();
    }
}

void ServerDemo::onDataReady(){
    auto *tcp = qobject_cast<QTcpSocket*>(sender());
    if(tcp){
        QByteArray data = tcp->readAll();
        qDebug() << "onDataReady:" << data.size();
        qDebug() << "Data:" << data;
    }
}

void ServerDemo::onBytesWritten(qint64 bytes){
    qDebug() << "onBytesWritten:" << bytes;
}

bool ServerDemo::start (int port){
    if(m_server.isListening()){
        return true;
    }
    return m_server.listen(QHostAddress::LocalHost, port);
}

void ServerDemo::stop(){
    if(m_server.isListening()){
        m_server.close();
    }
}

ServerDemo::~ServerDemo(){}
