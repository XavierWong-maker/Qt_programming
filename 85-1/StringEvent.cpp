#include "StringEvent.h"
#include <QDebug>

StringEvent::StringEvent(QString data) : QEvent(TYPE) {
    m_data = data;
}

QString StringEvent::data(){
    return m_data;
}

StringEvent::~StringEvent(){
    qDebug() << "StringEvent::~StringEvent()";
}
