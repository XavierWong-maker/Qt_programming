#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>

class TestThread : public QThread
{
    Q_OBJECT

protected:
    void run();

public:
    explicit TestThread(QObject *parent = nullptr);

signals:
    void testsignal();

};

#endif // TESTTHREAD_H
