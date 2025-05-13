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
        QString status;
        QString level;
        QTcpSocket* socket;

        Node() = default;
        Node(QString id, QString pwd, QTcpSocket* socket)
            :id(std::move(id)), pwd(std::move(pwd)), status("ok"), level("user"), socket(socket){}
    };

    QList<Node> m_nodeList;
    QMap<QString, MsgHandler> m_handlerMap;

    QString getOnlineUserId() const;
    void sendToAllOnlineUser(TextMessage&);

    void CONN_Handler(QTcpSocket&, TextMessage&);
    void DSCN_Handler(QTcpSocket&, TextMessage&);
    void LGIN_Handler(QTcpSocket&, TextMessage&);
    void MSGA_Handler(QTcpSocket&, TextMessage&);
    void MSGP_Handler(QTcpSocket&, TextMessage&);
    void ADMN_Handler(QTcpSocket&, TextMessage&);

public:
    ServerHandler();
    void handle(QTcpSocket& obj, TextMessage& message);
};

#endif // SERVERHANDLER_H
