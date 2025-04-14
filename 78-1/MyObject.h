#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

class MyObject : public QObject
{
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = nullptr);

public slots:
    void startslot();
    void testSlot();
};

#endif // MYOBJECT_H
