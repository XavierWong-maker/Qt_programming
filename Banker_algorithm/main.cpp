#include <QCoreApplication>
#include <QThread>
#include <QMutex>
#include <QList>
#include <QDebug>
#include <QSharedPointer>
#include <QWaitCondition>

class Customer : public QThread{

    int m_need;
    int m_current;
    mutable QMutex m_mutex;
    QWaitCondition m_waitCondition;

protected:
    void run() override{
        qDebug() << objectName() << "begins applying for money";

        while (true) {
            {
                QMutexLocker locker(&m_mutex);
                if(m_current >= m_need)
                    break;
                m_waitCondition.wait(&m_mutex);
            }
            msleep(10);
        }
        qDebug() << objectName() << "ends (got enough money)";
    }

public:
    Customer(int current, int need) : m_need(need), m_current(current) {}

    void addMoney(int amount){
        QMutexLocker locker(&m_mutex);
        m_current += amount;
        m_waitCondition.wakeAll();
    }

    int backMoney(){
        QMutexLocker locker(&m_mutex);
        int amout = m_current;
        m_current = 0;
        return amout;
    }

    int current() const{
        QMutexLocker locker(&m_mutex);
        return m_current;
    }

    int need() const{
        return m_need;
    }
};

class Bank : public QThread{

    QList<QSharedPointer<Customer>> m_customers;
    int m_total;
    QMutex m_mutex;

protected:
    void run() override{
        qDebug() << objectName() << "begins with total:" << m_total;

        while (true) {
            QSharedPointer<Customer> targetCustomer;
            int minToGet = std::numeric_limits<int>::max();
            {
                QMutexLocker locker(&m_mutex);

                for(auto it = m_customers.begin(); it != m_customers.end();){
                    if(!(*it)->isRunning() || (*it)->current() >= (*it)->need()){
                        qDebug() << objectName() << "reclaims" << (*it)->current()
                        << "from" << (*it)->objectName();
                        m_total += (*it)->backMoney();
                        it = m_customers.erase(it);

                    }else{
                        ++it;
                    }
                }

                if(m_customers.isEmpty())
                    break;

                for(const auto& customer : m_customers){
                    int needed = customer->need() - customer->current();
                    if(needed < minToGet){
                        minToGet = needed;
                        targetCustomer = customer;
                    }
                }
            }

            if(targetCustomer){
                if(minToGet <= m_total){
                    qDebug() << objectName() << "gives 1 unit to" << targetCustomer->objectName();
                    m_total--;
                    targetCustomer->addMoney(1);

                }else{
                    qDebug() << objectName() << "cannot fulfill" << targetCustomer->objectName()
                    << "- reclaiming" << targetCustomer->current();
                    m_total += targetCustomer->backMoney();
                    targetCustomer->terminate();
                }
            }
            qDebug() << objectName() << "current total:" << m_total;
            sleep(1);
        }
        qDebug() << objectName() << "ends with total:" << m_total;
    }

public:
    Bank(int total) : m_total(total){}

    void addCustomer(QSharedPointer<Customer> customer){
        QMutexLocker locker(&m_mutex);
        m_customers.append(customer);
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto p = QSharedPointer<Customer>::create(4, 8);
    auto q = QSharedPointer<Customer>::create(2, 3);
    auto r = QSharedPointer<Customer>::create(2, 11);

    Bank bank(2);

    p->setObjectName("P");
    q->setObjectName("Q");
    r->setObjectName("R");
    bank.setObjectName("Bank");

    bank.addCustomer(p);
    bank.addCustomer(q);
    bank.addCustomer(r);

    p->start();
    q->start();
    r->start();
    bank.start();

    return a.exec();
}
