#ifndef STRINGEVENT_H
#define STRINGEVENT_H

#include <QEvent>
#include <QString>

class StringEvent : public QEvent
{
    QString m_data;

public:
    static constexpr QEvent::Type TYPE = static_cast<QEvent::Type>(QEvent::User + 0xFF);
    explicit StringEvent(QString data = nullptr);

    QString data();
    ~StringEvent();

};

#endif // STRINGEVENT_H
