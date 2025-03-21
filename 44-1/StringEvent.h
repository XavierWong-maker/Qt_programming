#ifndef STRINGEVENT_H
#define STRINGEVENT_H

#include <QEvent>
#include <QString>

class StringEvent : public QEvent
{
    QString m_data;

public:

    static const Type TYPE = static_cast<Type>(QEvent::User + 0xFF);
    explicit StringEvent(QString data = "");
    QString data();
};

#endif // STRINGEVENT_H
