#include "TxtMsgAssmbler.h"
#include <QDebug>
#include <algorithm>

TxtMsgAssmbler::TxtMsgAssmbler(QObject *parent) : QObject{parent}{}

QSharedPointer<TextMessage> TxtMsgAssmbler::tryAssemble(){
    if(m_type.isEmpty() && !parseHeader()){
        return nullptr;
    }

    // Accumulate data
    int needed = m_length - m_data.size();
    int available = std::min(needed, static_cast<int>(m_buffer.size()));
    m_data.append(m_buffer.left(available));
    m_buffer.remove(0, available);

    if(m_data.size() == m_length){
        auto msg = QSharedPointer<TextMessage>::create(m_type, m_data);
        clear();
        return msg;
    }

    return nullptr;
}

bool TxtMsgAssmbler::parseHeader(){
    if(m_buffer.size() < 8){
        return false;
    }

    m_type = m_buffer.mid(0, 4);
    bool ok;
    QByteArray lenBytes = m_buffer.mid(4 ,4);
    m_length = lenBytes.toInt(&ok, 16);
    if(!ok){
        clear();
        return false;
    }

    m_buffer.remove(0, 8);
    return true;
}

QSharedPointer<TextMessage> TxtMsgAssmbler::assemble(){
    return tryAssemble();
}

QSharedPointer<TextMessage> TxtMsgAssmbler::assemble(const char* data, int len){
    m_buffer.append(data, len);
    return tryAssemble();
}

void TxtMsgAssmbler::clear(){
    m_type.clear();
    m_data.clear();
    m_length = 0;
}

void TxtMsgAssmbler::reset(){
    clear();
    m_buffer.clear();
}

void TxtMsgAssmbler::append(QByteArrayView data){
    m_buffer.append(data);
}

