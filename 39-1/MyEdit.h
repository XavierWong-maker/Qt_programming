#ifndef MYEDIT_H
#define MYEDIT_H

#include <QLineEdit>

class MyEdit : public QLineEdit
{
    Q_OBJECT
public:
    bool event(QEvent* e);
    void keyPressEvent(QKeyEvent* e);
    explicit MyEdit(QWidget* parent = 0);
};

#endif // MYEDIT_H
