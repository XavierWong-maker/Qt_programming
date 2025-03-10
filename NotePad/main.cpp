#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = MainWindow::NewInstance();
    int ret = -1;
    if( w != NULL ){
        w->resize(800, 600);
        w->show();
        ret = a.exec();
    }
    delete w;
    return ret;
}
