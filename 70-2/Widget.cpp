#include "Widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_fontSize{0}, m_timer{this}{

    // connect(&m_timer, &QTimer::timeout, this, qOverload<>(&QWidget::update));
    connect(&m_timer, &QTimer::timeout, this, [this](){update();});

    m_timer.start(30);
}

void Widget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    const QString text = "Software";
    QFont font("Comic Sans MS", 5 + (m_fontSize++) % 100);
    QFontMetrics metrics(font);
    const int w = metrics.horizontalAdvance(text);
    const int h = metrics.height();
    QRect rect((width() - w) / 2, (height() - h) / 2, w, h);

    painter.setPen(Qt::blue);
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignCenter, text);
}

Widget::~Widget() {}
