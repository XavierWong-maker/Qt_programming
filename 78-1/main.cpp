#include <QCoreApplication>
#include <QThread>
#include "TestThread.h"
#include "MyObject.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "main() tid = " << QThread::currentThreadId();

    TestThread t;
    MyObject obj;
    QObject::connect(&t, &TestThread::started, &obj, &MyObject::startslot);
    QObject::connect(&t, &TestThread::testsignal, &obj, &MyObject::testSlot);

    obj.moveToThread(&t);
    t.moveToThread(&t);
    t.start();

    t.wait(8*1000);
    t.quit();

    return a.exec();
}
