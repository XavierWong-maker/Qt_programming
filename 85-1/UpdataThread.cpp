#include "UpdataThread.h"
#include "StringEvent.h"
#include <QApplication>
#include <QDebug>

UpdataThread::UpdataThread(QObject *parent)
    : QThread{parent}
{}

void UpdataThread::run() {

    QApplication::postEvent(parent(), new StringEvent("begin"));
    for(int i {0}; i < 10; ++i){
        QApplication::postEvent(parent(), new StringEvent(QString::number(i)));
        sleep(2);
    }
    QApplication::postEvent(parent(), new StringEvent("end"));
}
