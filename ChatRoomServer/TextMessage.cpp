#include "TextMessage.h"
#include <cstdio>
#include <QDebug>


TextMessage::TextMessage(QObject *parent)
    : QObject(parent), m_type(""), m_data("")
{}

TextMessage::TextMessage(QByteArray type, QByteArray data, QObject *parent)
    :QObject(parent)
{
    m_type = type.left(4);
    m_type.resize(4, ' ');
    m_data = data.left(0xFFFF);
}

QByteArray TextMessage::serialize() const{
    QByteArray result;
    result.reserve(HeaderSize + m_data.length());

    // Append type (4 bytes)
    result.append(m_type);
    // Append length as 4-char hex
    char lenBuf[5];
    snprintf(lenBuf, sizeof(lenBuf), "%04X", static_cast<unsigned int>(m_data.length()));
    result.append(lenBuf, 4);
    // Append data
    result.append(m_data);

    return result;
}

bool TextMessage::unserialize(QByteArrayView buffer){
    if(buffer.size() < HeaderSize){
        return false;
    }

    m_type = buffer.mid(0, 4).toByteArray();

    bool ok;
    QByteArray lenBytes = buffer.mid(4, 4).toByteArray();
    int len = lenBytes.toInt(&ok, 16);
    if(!ok || len != buffer.size() - HeaderSize){
        return false;
    }

    m_data = buffer.mid(HeaderSize, len).toByteArray();
    return true;
}

