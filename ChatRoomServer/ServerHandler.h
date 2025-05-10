#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QMap>
#include <QList>
#include "TxtMsgHandler.h"

class ServerHandler : public TxtMsgHandler
{
    using MsgHandler = void (ServerHandler::*)(QTcpSocket&, TextMessage&);

    struct Node{
        QString id;
        QString pwd;
        QTcpSocket* socket;

        Node(QString id, QString pwd, QTcpSocket* socket)
            :id(std::move(id)), pwd(std::move(pwd)), socket(socket){}
    };

    QList<Node> m_nodeList;
    QMap<QString, MsgHandler> m_handlerMap;

    void CONN_Handler(QTcpSocket&, TextMessage&);
    void DSCN_Handler(QTcpSocket&, TextMessage&);
    void LGIN_Handler(QTcpSocket&, TextMessage&);
    void MSGA_Handler(QTcpSocket&, TextMessage&);

public:
    ServerHandler();
    void handle(QTcpSocket& obj, TextMessage& message);
};

#endif // SERVERHANDLER_H
