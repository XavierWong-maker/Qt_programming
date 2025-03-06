#include "Widget.h"
#include "QLogindialog.h"
#include <QPrintDialog>
#include <QDebug>
#include <QStackedLayout>
#include <QtCore>

Widget::Widget(QWidget *parent)
    : QWidget(parent), TestBtn(this), PrintBtn(this){

    QStackedLayout* sLayout = new QStackedLayout(this);
    TestBtn.setText("Test Login Dialog");
    PrintBtn.setText("Progress Dialog");

    sLayout->addWidget(&TestBtn);
    sLayout->addWidget(&PrintBtn);
    sLayout->setCurrentIndex(0);
    setLayout(sLayout);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::timer);
    timer->start(2000);

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

void Widget::timer(){
    QStackedLayout* sLayout = qobject_cast<QStackedLayout*>(layout());
    if(!sLayout || sLayout->count() < 2){
        return;
    }
    sLayout->setCurrentIndex(!sLayout->currentIndex());
}

Widget::~Widget() {}

