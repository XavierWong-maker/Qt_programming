#include <QCoreApplication>
#include <QThread>
#include <QMutex>
#include <QDebug>

#define MAXSTORAGE 10

static QString g_store;
static QMutex g_mutex;

class Producer : public QThread{

protected:
    void run() override{
        int count {0};
        while (true) {
            g_mutex.lock();
            if(g_store.size() <= MAXSTORAGE){

                g_store.append(QString::number((count++) % 10));
                qDebug() << objectName() << ":" + g_store;
            }
            g_mutex.unlock();
            msleep(1);
        }
    }
};

class Customer : public QThread{

protected:
    void run() override{
        while (true) {
            g_mutex.lock();
            if(g_store.size() > 0){
                g_store.remove(0,1);
                qDebug() << objectName() << ":" + g_store;
            }
            g_mutex.unlock();
            msleep(1);
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "main begin";

    Producer p;
    Customer c;

    p.setObjectName("Produer");
    c.setObjectName("Customer");

    p.start();
    c.start();

    qDebug() << "main end";

    return a.exec();
}

