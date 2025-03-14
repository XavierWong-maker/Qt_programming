#include "MyEdit.h"
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

MyEdit::MyEdit(QWidget* parent) : QLineEdit(parent) {}

bool MyEdit::event(QEvent* e){
    if(e->type() == QEvent::KeyPress){
        qDebug() << "MyEdit::event";
    }
    return QLineEdit::event(e);
}

void MyEdit::keyPressEvent(QKeyEvent* e){
    qDebug() << "MyEdit::keyPressEvent";
    QLineEdit::keyPressEvent(e);
    //e->ignore();
}

