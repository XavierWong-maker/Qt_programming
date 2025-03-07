#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QStackedLayout>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT
private:
    QPushButton preButton;
    QPushButton nextButton;
    QStackedLayout sLayout;

    QLabel label1;
    QLabel label2;
    QLabel label3;
    QLabel label4;

    QLineEdit edit;

    QPushButton button1;
    QPushButton button2;
    QPushButton button3;
    QPushButton button4;

    QWidget* get1stPage();
    QWidget* get2ndPage();
    QWidget* get3rdPage();

private slots:
    void pre();
    void next();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
