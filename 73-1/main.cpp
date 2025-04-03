#include <QCoreApplication>
#include <QThread>

class MyThread : public QThread{

protected:
    void run(){
        qDebug() << objectName() << "run() begin";
        for (int i = 0; i < 5; ++i) {
            qDebug() << objectName() << i;
            sleep(i);
        }
        qDebug() << objectName() << "run() end";
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<< "main() begin";

    MyThread t1;
    t1.setObjectName("t1");
    t1.start();

    MyThread t2;
    t2.setObjectName("t2");
    t2.start();

    qDebug() << "main() end";

    return a.exec();
}
