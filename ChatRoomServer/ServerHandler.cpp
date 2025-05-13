#include "ServerHandler.h"

ServerHandler::ServerHandler() {

    m_handlerMap = {
        {"CONN", &ServerHandler::CONN_Handler},
        {"DSCN", &ServerHandler::DSCN_Handler},
        {"LGIN", &ServerHandler::LGIN_Handler},
        {"MSGA", &ServerHandler::MSGA_Handler},
        {"MSGP", &ServerHandler::MSGP_Handler},
        {"ADMN", &ServerHandler::ADMN_Handler}
    };

    static Node admin;
    admin.id = "Admin";
    admin.pwd = "dt0919";
    admin.level = "admin";
    m_nodeList.append(admin);
}


void ServerHandler::handle(QTcpSocket &socket, TextMessage &message){
    auto it = m_handlerMap.find(message.type());
    if(it != m_handlerMap.end()){
        MsgHandler handler = it.value();
        (this->*handler)(socket, message);
    }else{
        qDebug() << "Unhandled message tyep:" << QString::fromUtf8(message.type());
    }
}

QString ServerHandler::getOnlineUserId() const{
    QStringList onlineUsers;
    for(const Node& node : m_nodeList){
        if(node.socket){
            onlineUsers << node.id;
        }
    }
    return onlineUsers.join('\r');
}

void ServerHandler::sendToAllOnlineUser(TextMessage& message){
    const QByteArray ba = message.serialize();
    for(const Node& node : m_nodeList){
        if(node.socket){
            node.socket->write(ba);
        }
    }
}

void ServerHandler::CONN_Handler(QTcpSocket&, TextMessage&){}

void ServerHandler::DSCN_Handler(QTcpSocket& socket, TextMessage&){
    for(Node& node : m_nodeList){
        if(node.socket == &socket){
            node.socket = nullptr;
            break;
        }
    }
    TextMessage tm(QByteArrayLiteral("USER"), getOnlineUserId().toUtf8());
    sendToAllOnlineUser(tm);
}

void ServerHandler::LGIN_Handler(QTcpSocket& socket, TextMessage& message){
    const QString data = QString::fromUtf8(message.data());
    QStringList parts = data.split('\r', Qt::SkipEmptyParts);
    if(parts.size() < 2){
        socket.write(TextMessage(QByteArrayLiteral("LIER"), QByteArray()).serialize());
        return;
    }

    QString id = parts[0];
    QString pwd = parts[1];
    Node* targetNode = nullptr;

    // Check if user already exists
    for(Node& node : m_nodeList){
        if(node.id == id){
            targetNode = &node;
            break;
        }
    }

    QByteArray result;
    QString status;
    QString level;

    if(!targetNode){
        Node* newNode = new Node(id, pwd, &socket);
        m_nodeList.append(*newNode);
        result = QByteArrayLiteral("LIOK");
        status = newNode->status;
        level = newNode->level;

    }else if(targetNode->pwd == pwd){
        // Existing user with correct password
        targetNode->socket = &socket;
        result = QByteArrayLiteral("LIOK");
        status = targetNode->status;
        level = targetNode->level;

    }else{
        // Incorrect password
        result = QByteArrayLiteral("LIER");
    }

    socket.write(TextMessage(result, QStringLiteral("%1\r%2\r%3").arg(id, status, level).toUtf8()).serialize());

    if(result == QByteArrayLiteral("LIOK")){
        TextMessage tm(QByteArrayLiteral("USER"), getOnlineUserId().toUtf8());
        sendToAllOnlineUser(tm);
    }
}

void ServerHandler::MSGA_Handler(QTcpSocket&, TextMessage& message){
    sendToAllOnlineUser(message);
}

void ServerHandler::MSGP_Handler(QTcpSocket &, TextMessage& message){
    QStringList parts = QString::fromUtf8(message.data()).split('\r', Qt::SkipEmptyParts);
    if(parts.isEmpty()){
        return;
    }

    QByteArray messageData = parts.takeLast().toUtf8();
    TextMessage tm(QByteArrayLiteral("MSGA"), messageData);
    const QByteArray ba = tm.serialize();

    for(const QString& userId : parts){
        for(const Node& node : m_nodeList){
            if(node.id == userId && node.socket){
                node.socket->write(ba);
                break;
            }
        }
    }
}

void ServerHandler::ADMN_Handler(QTcpSocket &, TextMessage &message){
    const QStringList data = QString::fromUtf8(message.data()).split('\r', Qt::SkipEmptyParts);
    if(data.size() < 2){
        qDebug() << "Invalid ADMN message format";
        return;
    }

    const QString op = data[0];
    const QString id = data[1];

    for(Node& node : m_nodeList){
        if(node.id == id && node.socket && node.level == "user"){
            node.socket->write(TextMessage(QByteArrayLiteral("CTRL"), op.toUtf8()).serialize());
            node.status = op;
            break;
        }
    }
}


