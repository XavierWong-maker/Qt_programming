#include <QApplication>
#include "Calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Calculator* cal = Calculator::newInstance();
    int ret = -1;
    if(cal){
        cal->show();
        ret = a.exec();
        delete cal;
    }

    return ret;
}
