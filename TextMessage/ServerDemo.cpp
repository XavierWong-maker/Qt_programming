#include "ServerDemo.h"
#include <QTcpSocket>

ServerDemo::ServerDemo(QObject *parent)
    : QObject{parent}, m_handler{nullptr}
{
    connect(&m_server, &QTcpServer::newConnection, this, &ServerDemo::onNewConnection);
}

void ServerDemo::onNewConnection(){

    QTcpSocket *tcp = m_server.nextPendingConnection();
    TxtMsgAssmbler* assembler = new TxtMsgAssmbler(tcp);
    m_map.insert(tcp, assembler);

    connect(tcp, &QTcpSocket::connected, this, &ServerDemo::onConnected);
    connect(tcp, &QTcpSocket::disconnected, this, &ServerDemo::onDisconnected);
    connect(tcp, &QTcpSocket::readyRead, this, &ServerDemo::onDataReady);
    connect(tcp, &QTcpSocket::bytesWritten, this, &ServerDemo::onBytesWritten);

    qDebug() << "New client connected:" << tcp->peerAddress().toString();
}

void ServerDemo::onConnected(){
    qDebug() << "Client connected";
}

void ServerDemo::onDisconnected(){
    auto *tcp = qobject_cast<QTcpSocket*>(sender());
    if(tcp){
        qDebug() << "Client disconnected:" << tcp->peerAddress().toString();
        delete m_map.take(tcp);
    }
}

void ServerDemo::onDataReady(){
    auto *tcp = qobject_cast<QTcpSocket*>(sender());
    if(!tcp){
        return;
    }

    char buf[256] = {0};
    int len {0};
    TxtMsgAssmbler* assmbler = m_map.value(tcp);

    while((len = tcp->read(buf, sizeof(buf))) > 0){
        QSharedPointer<TextMessage> ptm = assmbler ? assmbler->assemble(buf, len) : nullptr;
        if(ptm && m_handler){
            m_handler->handle(*tcp, *ptm);
        }
    }
}

void ServerDemo::onBytesWritten(qint64 bytes){
    qDebug() << "Server wrote:" << bytes;
}

bool ServerDemo::start (int port){
    if(!m_server.isListening()){
        bool ret = m_server.listen(QHostAddress("127.0.0.1"), port);
        qDebug() << (ret ? "Server started on port" : "Failed to start server on port") << port;
        return ret;
    }
    return true;
}

void ServerDemo::stop(){
    if(m_server.isListening()){
        m_server.close();
        qDebug() << "Server stopped";
    }
}

ServerDemo::~ServerDemo(){
    stop();
    for(TxtMsgAssmbler* assembler : m_map){
        delete assembler;
    }
    m_map.clear();
}

void ServerDemo::setHandler(TxtMsgHandler* handler){
    m_handler = handler;
}
