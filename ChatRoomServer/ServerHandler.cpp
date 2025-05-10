#include "ServerHandler.h"

ServerHandler::ServerHandler() {

    m_handlerMap = {
        {"CONN", &ServerHandler::CONN_Handler},
        {"DSCN", &ServerHandler::DSCN_Handler},
        {"LGIN", &ServerHandler::LGIN_Handler},
        {"MSGA", &ServerHandler::MSGA_Handler}
    };
}


void ServerHandler::handle(QTcpSocket &socket, TextMessage &message){
    auto it = m_handlerMap.find(message.type());
    if(it != m_handlerMap.end()){
        MsgHandler handler = it.value();
        (this->*handler)(socket, message);
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
}

void ServerHandler::LGIN_Handler(QTcpSocket& socket, TextMessage& message){
    const QString data = message.data();
    const int separatorIndex = data.indexOf('\r');
    const QString id = data.left(separatorIndex);
    const QString pwd = data.mid(separatorIndex + 1);

    auto it = std::find_if(m_nodeList.begin(), m_nodeList.end(),
                           [&id](const Node& node)  {return node.id == id; });

    QString result;
    if(it == m_nodeList.end()){
        m_nodeList.append(Node(id, pwd, &socket));
        result = QStringLiteral("LIOK");
    }else{
        if(it->pwd == pwd){
            it->socket = &socket;
            result = QStringLiteral("LIOK");
        }else{
            result = QStringLiteral("LIER");
        }
    }

    socket.write(TextMessage(result.toUtf8(), id.toUtf8()).serialize());
}

void ServerHandler::MSGA_Handler(QTcpSocket&, TextMessage& message){
    const QByteArray data = message.serialize();
    for(const Node& node : m_nodeList){
        if(node.socket){
            node.socket->write(data);
        }
    }
}


