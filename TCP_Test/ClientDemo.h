#ifndef CLIENTDEMO_H
#define CLIENTDEMO_H

#include <QObject>
#include <QTcpSocket>

class ClientDemo : public QObject
{
    Q_OBJECT
    QTcpSocket m_client;

protected slots:
    void onConnected();
    void onDisconnected();
    void onDataReady();
    void onBytesWritten(qint64 bytes);

public:
    explicit ClientDemo(QObject *parent = nullptr);
    void connectTo(QString ip, int port);
    qint64 send(const char* data, int len);
    qint64 available();
    void close();

signals:
};

#endif // CLIENTDEMO_H
