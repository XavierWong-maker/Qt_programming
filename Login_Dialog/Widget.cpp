#include "Widget.h"
#include "QLogindialog.h"
#include <QPrintDialog>
#include <QDebug>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent), TestBtn(this), PrintBtn(this){

    QVBoxLayout* layout = new QVBoxLayout(this);
    TestBtn.setText("Test Login Dialog");
    PrintBtn.setText("Progress Dialog");

    layout->addWidget(&TestBtn);
    layout->addWidget(&PrintBtn);

    setLayout(layout);

    connect(&TestBtn, &QPushButton::clicked, this, &Widget::TestBtn_Clicked);
    connect(&PrintBtn, &QPushButton::clicked, this, &Widget::PrintBtn_clicked);
}

void Widget::TestBtn_Clicked(){
    QLoginDialog dlg;
    if(dlg.exec() == QDialog::Accepted){
        qDebug() << "User:" + dlg.getUser();
        qDebug() << "Pwd:" + dlg.getPwd();
    }
}

void Widget::PrintBtn_clicked(){
    QPrintDialog prdialog(this);

    prdialog.setWindowTitle("Setting the Printer");
    prdialog.exec();
}

Widget::~Widget() {}

