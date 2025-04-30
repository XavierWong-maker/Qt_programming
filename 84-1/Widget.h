#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include "MyThread.h"

class Widget : public QWidget
{
    Q_OBJECT

    QPlainTextEdit* m_plaintext;
    MyThread m_thread;

protected slots:
    void setInfo(QString text);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};

#endif // WIDGET_H
