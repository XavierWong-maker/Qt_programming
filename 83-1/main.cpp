#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include "AnotherThread.h"

void another_Test(){
    AnotherThread at;
    at.start();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "main() tid : " << QThread::currentThreadId();

    another_Test();


    return a.exec();
}
