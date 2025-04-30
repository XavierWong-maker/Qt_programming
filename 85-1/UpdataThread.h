#ifndef UPDATATHREAD_H
#define UPDATATHREAD_H

#include <QThread>

class UpdataThread : public QThread
{
    Q_OBJECT

    void run() override;

public:
    explicit UpdataThread(QObject *parent = nullptr);
};

#endif // UPDATATHREAD_H
