#ifndef ANOTHERTHREAD_H
#define ANOTHERTHREAD_H

#include <QObject>
#include <QThread>

class AnotherThread : public QObject
{
    Q_OBJECT

    QThread m_thread;

signals:

protected slots:
    void tmain();

public:
    explicit AnotherThread(QObject *parent = nullptr);
    void start();
    void terminate();
    void exit(int c);
    ~AnotherThread();
};

#endif // ANOTHERTHREAD_H
