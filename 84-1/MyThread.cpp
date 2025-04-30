#include "MyThread.h"

MyThread::MyThread(QObject *parent)
    : QThread{parent}
{}

void MyThread::run() {
    emit UpdataUI("begin");

    for(int i {0}; i < 10; ++i){
        emit UpdataUI(QString::number(i));
        sleep(1);
    }

    emit UpdataUI("end");
}
