#include "Widget.h"
#include "QLogindialog.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent), TestBtn(this){

    TestBtn.setText("Test Login Dialog");
    setFixedSize(200, 50);
    connect(&TestBtn, &QPushButton::clicked, this, &Widget::TestBtn_Clicked);
}

void Widget::TestBtn_Clicked(){
    QLoginDialog dlg;
    if(dlg.exec() == QDialog::Accepted){
        qDebug() << "User:" + dlg.getUser();
        qDebug() << "Pwd:" + dlg.getPwd();
    }
}

Widget::~Widget() {}
