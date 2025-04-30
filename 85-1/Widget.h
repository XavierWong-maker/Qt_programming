#ifndef WIDGET_H
#define WIDGET_H

#include "UpdataThread.h"
#include <QWidget>
#include <QPlainTextEdit>

class Widget : public QWidget
{
    Q_OBJECT

    UpdataThread m_thread;
    QPlainTextEdit m_plainTextEdit;

public:
    Widget(QWidget *parent = nullptr);
    bool event(QEvent *evt);
    ~Widget();
};
#endif // WIDGET_H
