#include "Widget.h"
#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent){

    QVBoxLayout* vbLayout = new QVBoxLayout();
    QHBoxLayout* hbLayout = new QHBoxLayout();

    preButton.setText("Pre");
    preButton.setMinimumSize(80,30);
    preButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    nextButton.setText("Next");
    nextButton.setMinimumSize(80,30);
    nextButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(&preButton, &QPushButton::clicked, this, &Widget::pre);
    connect(&nextButton, &QPushButton::clicked, this, &Widget::next);
    hbLayout->addWidget(&preButton);
    hbLayout->addWidget(&nextButton);
    sLayout.addWidget(get1stPage());
    sLayout.addWidget(get2ndPage());
    sLayout.addWidget(get3rdPage());
    vbLayout->addLayout(&sLayout);
    vbLayout->addLayout(hbLayout);
    setLayout(vbLayout);
}

Widget::~Widget() {}

QWidget* Widget::get1stPage(){
    QWidget* ret = new QWidget();
    QGridLayout* gLayout = new QGridLayout();
    label1.setText("Hello");
    label2.setText("word");
    label3.setText("This is");
    label4.setText("1st page");
    gLayout->addWidget(&label1, 0, 0);
    gLayout->addWidget(&label2, 0, 1);
    gLayout->addWidget(&label3, 1, 0, 1, 2);
    gLayout->addWidget(&label4, 2, 0, 1, 2);
    ret->setLayout(gLayout);
    return ret;
}

QWidget* Widget::get2ndPage(){
    QWidget* ret = new QWidget();
    QFormLayout* fLayout = new QFormLayout();
    fLayout->addRow("username:", &edit);
    edit.setText("hello");
    ret->setLayout(fLayout);
    return ret;
}

QWidget * Widget::get3rdPage()
{
    QWidget * ret = new QWidget();

    QVBoxLayout *vbLayout = new QVBoxLayout();
    button1.setText("hello");
    button2.setText("world");
    button3.setText("3rd");
    button4.setText("page");

    vbLayout->addWidget(&button1);
    vbLayout->addWidget(&button2);
    vbLayout->addWidget(&button3);
    vbLayout->addWidget(&button4);

    ret->setLayout(vbLayout);

    return ret;
}

void Widget::pre(){
    int index = ((sLayout.currentIndex() - 1) + 3) % 3;
    sLayout.setCurrentIndex(index);
}

void Widget::next(){
    int index = ((sLayout.currentIndex() + 1) + 3) % 3;
    sLayout.setCurrentIndex(index);
}
