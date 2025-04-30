#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QString>

class MyThread : public QThread
{
    Q_OBJECT

    void run() override;

signals:
    void UpdataUI(QString text);

public:
    explicit MyThread(QObject *parent = nullptr);
};

#endif // MYTHREAD_H
