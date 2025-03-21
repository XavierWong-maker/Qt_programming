#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>

class Widget : public QWidget
{
    Q_OBJECT

    QLineEdit m_LineEdit;

public:
    bool eventFilter(QObject* obj, QEvent* event);
    Widget(QWidget *parent = nullptr);
    bool event(QEvent* e);
    ~Widget();
};
#endif // WIDGET_H
