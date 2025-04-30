#include "Widget.h"
#include "StringEvent.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),m_thread(this),m_plainTextEdit(this)
{
    m_plainTextEdit.resize(200, 200);

    m_thread.start();
}

bool Widget::event(QEvent *evt){

    if(evt->type() == StringEvent::TYPE){
        if (auto se = dynamic_cast<StringEvent*>(evt)) {
            m_plainTextEdit.appendPlainText(se->data());
            return true;
        }
    }
    return QWidget::event(evt);
}
Widget::~Widget() {}
