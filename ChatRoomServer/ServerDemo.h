#ifndef SERVERDEMO_H
#define SERVERDEMO_H

#include <QObject>
#include <QTcpServer>
#include "TxtMsgAssmbler.h"
#include "TxtMsgHandler.h"

class ServerDemo : public QObject
{
    Q_OBJECT

    QTcpServer m_server;
    QMap<QTcpSocket*, TxtMsgAssmbler*> m_map;
    TxtMsgHandler* m_handler;

protected slots:
    void onNewConnection();
    void onConnected();
    void onDisconnected();
    void onDataReady();
    void onBytesWritten(qint64 bytes);

public:
    explicit ServerDemo(QObject *parent = nullptr);
    bool start (int port);
    void stop();
    void setHandler(TxtMsgHandler* handler);
    ~ServerDemo();
};

#endif // SERVERDEMO_H
