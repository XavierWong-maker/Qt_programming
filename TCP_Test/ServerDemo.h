#ifndef SERVERDEMO_H
#define SERVERDEMO_H

#include <QObject>
#include <QTcpServer>

class ServerDemo : public QObject
{
    Q_OBJECT

    QTcpServer m_server;

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
    ~ServerDemo();

signals:
};

#endif // SERVERDEMO_H
