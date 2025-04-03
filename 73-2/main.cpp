#include <QCoreApplication>
#include <QThread>

class Sample : public QThread {

protected:
    QAtomicInteger<bool> m_toStop;

    void run() override {
        qDebug() << objectName() << " : begin";
        auto p = new int[1000];

        for (int i = 0; !m_toStop && (i < 10); ++i) {
            qDebug() << objectName() << ":" << i;
            p[i] = i*i*i;
            msleep(500);
        }
        delete[] p;
        qDebug() << objectName() << ": end";
    }
public:
    Sample() : m_toStop(false) {}

    void stop() { m_toStop = true; }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "main begin";
    Sample t;
    t.setObjectName("t");
    t.start();

    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {

        }
    }

    t.stop();
    //t.terminate();
    qDebug() << "main end";

    return a.exec();
}
