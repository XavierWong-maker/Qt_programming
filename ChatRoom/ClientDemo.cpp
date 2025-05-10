#include "ClientDemo.h"

ClientDemo::ClientDemo(QObject *parent)
    : QObject{parent}, m_handler(nullptr)
{
    connect(&m_client, &QTcpSocket::connected, this, &ClientDemo::onConnected);
    connect(&m_client, &QTcpSocket::disconnected, this, &ClientDemo::onDisconnected);
    connect(&m_client, &QTcpSocket::readyRead, this, &ClientDemo::onDataReady);
    connect(&m_client, &QTcpSocket::bytesWritten, this, &ClientDemo::onBytesWritten);
}

void ClientDemo::onConnected(){
    if(nullptr == m_handler){
        return;
    }

    QString address = m_client.peerAddress().toString();
    QString port = QString::number(m_client.peerPort());
    QString combined = address + ":" + port;
    QByteArray data = combined.toUtf8();
    TextMessage conn("CONN", data);
    m_handler->handle(m_client, conn);
}

void ClientDemo::onDisconnected(){
    m_assembler.reset();
    if(nullptr == m_handler){
        return;
    }

    TextMessage dscn("DSCN", "");
    m_handler->handle(m_client, dscn);
}

void ClientDemo::onDataReady(){
    char buf[256] = {0};
    int len = 0;

    while ((len = m_client.read(buf, sizeof(buf))) > 0) {
        QSharedPointer<TextMessage> ptm = nullptr;
        m_assembler.append(QByteArrayView(buf, len));
        while((ptm = m_assembler.assemble())){
            if(m_handler){
                m_handler->handle(m_client, *ptm);
            }
        }
    }
}

void ClientDemo::onBytesWritten(qint64 bytes){
    Q_UNUSED(bytes);
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

bool ClientDemo::isValid(){
    return m_client.isValid();
}

void ClientDemo::close(){
    m_client.close();
}
