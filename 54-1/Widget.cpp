#include "Widget.h"
#include <QPlainTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent){

    m_tabWidget.setParent(this);
    m_tabWidget.move(10, 10);
    m_tabWidget.resize(200, 200);
    m_tabWidget.setTabPosition(QTabWidget::South);
    m_tabWidget.setTabShape(QTabWidget::Triangular);
    m_tabWidget.setTabsClosable(true);

    auto edit = new QPlainTextEdit(&m_tabWidget);
    edit->setPlainText("1st Tab Pag");

    m_tabWidget.addTab(edit, "1st");

    auto widget = new QWidget(&m_tabWidget);
    auto layout = new QVBoxLayout();
    auto lable = new QLabel(widget);
    auto btn = new QPushButton(widget);

    lable->setText("2nd Tab Page");
    lable->setAlignment(Qt::AlignCenter);

    btn->setText("2nd Tab Page");

    layout->addWidget(lable);
    layout->addWidget(btn);

    widget->setLayout(layout);

    m_tabWidget.addTab(widget, "2nd");

    m_tabWidget.setCurrentIndex(1);

    connect(&m_tabWidget, &QTabWidget::currentChanged, this, &Widget::onTabCurrentChanged);
    connect(&m_tabWidget, &QTabWidget::tabCloseRequested, this, &Widget::onTabCloseRequested);
}

void Widget::onTabCurrentChanged(int index){
    qDebug() << "Page change to: " << index;
}

void Widget::onTabCloseRequested(int index){
    m_tabWidget.removeTab(index);
}


Widget::~Widget() {}
