#ifndef TXTMSGHANDLER_H
#define TXTMSGHANDLER_H

#include <QTcpSocket>
#include "TextMessage.h"


class TxtMsgHandler
{
public:
    virtual void handle(QTcpSocket&, TextMessage&) = 0;
    virtual ~TxtMsgHandler() = default;
};

#endif // TXTMSGHANDLER_H
