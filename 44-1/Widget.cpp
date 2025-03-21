#include "Widget.h"
#include "StringEvent.h"
#include <QApplication>
#include <QMouseEvent>
#include <qDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent),m_LineEdit(this){

    m_LineEdit.installEventFilter(this);
}

bool Widget::event(QEvent* e){
    if(e->type() == QMouseEvent::MouseButtonDblClick){
        qDebug() << "event: Before sentEvent";
        StringEvent se("SantaClaus");
        QApplication::sendEvent(&m_LineEdit, &se);
        qDebug() << "event: After sendEvent";
    }
    return QWidget::event(e);
}

bool Widget::eventFilter(QObject* obj, QEvent* event){
    if(obj == &m_LineEdit && (event->type() == StringEvent::TYPE)){
        StringEvent* se = dynamic_cast<StringEvent*>(event);
        m_LineEdit.insert(se->data());
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

Widget::~Widget() {}
