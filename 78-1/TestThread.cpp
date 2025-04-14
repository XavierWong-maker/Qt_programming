#include "TestThread.h"
#include <QDebug>

TestThread::TestThread(QObject *parent)
    : QThread{parent}
{

}


void TestThread::run() {
    qDebug() << "void TestThread::run() tid = " << currentThreadId();

    for(int i=0; i<5; i++){
        qDebug() << "TestThread::run() i=" << i;
        sleep(1);
    }

    emit testsignal();

    exec();

    qDebug() << "void TestThread::run() end";
}
