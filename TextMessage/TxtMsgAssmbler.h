#ifndef TXTMSGASSMBLER_H
#define TXTMSGASSMBLER_H

#include <QObject>
#include <QSharedPointer>
#include "TextMessage.h"

class TxtMsgAssmbler : public QObject
{
    Q_OBJECT

    QByteArray m_buffer;
    QByteArray m_type;
    int m_length {0};
    QByteArray m_data;

    QSharedPointer<TextMessage> tryAssemble();
    bool parseHeader();
    void clear();

public:
    explicit TxtMsgAssmbler(QObject *parent = nullptr);
    QSharedPointer<TextMessage> assemble();
    QSharedPointer<TextMessage> assemble(const char* data, int len);
    void append(QByteArrayView data);
    void reset();

};

#endif // TXTMSGASSMBLER_H
