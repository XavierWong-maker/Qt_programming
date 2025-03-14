#include "Widget.h"
#include "qevent.h"
#include <QEvent>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),myEdit(this)
{
    myEdit.installEventFilter(this);
}

bool Widget::event(QEvent* e){
    if(e->type() == QEvent::KeyPress){
        qDebug() << "Widget::event";
    }
    return QWidget::event(e);
}

void Widget::keyPressEvent(QKeyEvent* e){
    qDebug() << "Widget::keyPressEvent";
    QWidget::keyPressEvent(e);
}

bool Widget::eventFilter(QObject* obj, QEvent* e){
    if((obj != &myEdit) || (e->type() != QEvent::KeyPress)){
        return QWidget::eventFilter(obj, e);
    }

    auto keyEvent = static_cast<QKeyEvent*>(e);
    int key = keyEvent->key();
    if(key >= Qt::Key_0 && key <= Qt::Key_9){
        qDebug() << "Widget::eventFilter - Digit key pressed:" << key;
        return false;
    }
    if (key == Qt::Key_Backspace || key == Qt::Key_Delete) {
        return false;
    }

    return true;
}

Widget::~Widget() {}
