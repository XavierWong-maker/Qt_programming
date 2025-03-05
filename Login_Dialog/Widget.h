#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT
private:
    QPushButton TestBtn;
    QPushButton PrintBtn;

private slots:
    void TestBtn_Clicked();
    void PrintBtn_clicked();

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
