#ifndef DEFAULTTXTMSGHANDLER_H
#define DEFAULTTXTMSGHANDLER_H

#include "TxtMsgHandler.h"
#include <QDebug>

class DefaultTxtMsgHandle : public TxtMsgHandler
{
public:
    void handle(QTcpSocket& socket, TextMessage& message) override{

        // Display received message (supports Chinese with UTF-8)
        qDebug() << "Recrived message: ";
        qDebug() << "Type: " << QString::fromUtf8(message.type());
        qDebug() << "Data: " << QString::fromUtf8(message.data());

        // Send response (server-side only, optional for client)
        if(socket.localPort() == 8890){
            TextMessage response("RESP", "收到消息： " + message.data());
            QByteArray responseData = response.serialize();
            socket.write(responseData.data(), responseData.length());
        }
    }
};

#endif // DEFAULTTXTMSGHANDLER_H
