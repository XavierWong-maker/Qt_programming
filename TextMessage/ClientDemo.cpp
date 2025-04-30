#include "ClientDemo.h"

ClientDemo::ClientDemo(QObject *parent)
    : QObject{parent}
{
    connect(&m_client, &QTcpSocket::connected, this, &ClientDemo::onConnected);
    connect(&m_client, &QTcpSocket::disconnected, this, &ClientDemo::onDisconnected);
    connect(&m_client, &QTcpSocket::readyRead, this, &ClientDemo::onDataReady);
    connect(&m_client, &QTcpSocket::bytesWritten, this, &ClientDemo::onBytesWritten);
}

void ClientDemo::onConnected(){
    qDebug() << "Connected to server";
}

void ClientDemo::onDisconnected(){
    qDebug() << "Disconnected from server";
    m_assembler.reset();
}

void ClientDemo::onDataReady(){
    char buf[256] = {0};
    int len = 0;

    while ((len = m_client.read(buf, sizeof(buf))) > 0) {
        QSharedPointer<TextMessage> ptm = m_assembler.assemble(buf, len);
        if(ptm && m_handler){
            m_handler->handle(m_client, *ptm);
        }
    }
}

void ClientDemo::onBytesWritten(qint64 bytes){
    qDebug() << "onBytesWritten:" << bytes;
}

bool ClientDemo::connectTo(QString ip, int port){
    m_client.connectToHost(ip, port);
    return m_client.waitForConnected();
}

qint64 ClientDemo::send(TextMessage& message){
    QByteArray ba = message.serialize();
    return m_client.write(ba.data(), ba.length());
}

qint64 ClientDemo::available(){
    return m_client.bytesAvailable();
}

void ClientDemo::setHandler(TxtMsgHandler* handler){
    m_handler = handler;
}

void ClientDemo::close(){
    m_client.close();
}
