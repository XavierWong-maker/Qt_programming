#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "MyEdit.h"

class Widget : public QWidget
{
    Q_OBJECT
    MyEdit myEdit;
public:
    bool event(QEvent* e);
    void keyPressEvent(QKeyEvent* e);
    bool eventFilter(QObject* obj, QEvent* e);
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H

