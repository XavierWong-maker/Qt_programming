#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <QObject>

class TextMessage : public QObject
{
    Q_OBJECT

    QByteArray m_type;
    QByteArray m_data;

    static constexpr int HeaderSize {8};

public:
    explicit TextMessage(QObject *parent = nullptr);
    TextMessage(QByteArray type, QByteArray data, QObject *parent= nullptr);

    QByteArray type() const { return m_type; }
    int length() const { return m_data.length(); }
    QByteArray data() const { return m_data; }

    QByteArray serialize() const;
    bool unserialize(QByteArrayView buffer);

};

#endif // TEXTMESSAGE_H
