#ifndef CLIENTDEMO_H
#define CLIENTDEMO_H

#include <QObject>
#include <QTcpSocket>
#include "TextMessage.h"
#include "TxtMsgAssmbler.h"
#include "TxtMsgHandler.h"

class ClientDemo : public QObject
{
    Q_OBJECT
    QTcpSocket m_client;
    TxtMsgAssmbler m_assembler;
    TxtMsgHandler* m_handler;

protected slots:
    void onConnected();
    void onDisconnected();
    void onDataReady();
    void onBytesWritten(qint64 bytes);

public:
    explicit ClientDemo(QObject *parent = nullptr);
    bool connectTo(QString ip, int port);
    qint64 send(TextMessage& message);
    qint64 available();
    void setHandler(TxtMsgHandler* handler);
    void close();

signals:
};

#endif // CLIENTDEMO_H
