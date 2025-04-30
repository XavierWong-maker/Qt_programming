#include "Widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_plaintext = new QPlainTextEdit(this);
    m_plaintext->resize(160, 160);
    m_plaintext->setReadOnly(true);

    connect(&m_thread, &MyThread::UpdataUI, this, &Widget::setInfo);
    m_thread.start();
}

void Widget::setInfo(QString text){
    m_plaintext->appendPlainText(text);
}

Widget::~Widget() {}
