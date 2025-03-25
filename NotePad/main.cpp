#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = MainWindow::NewInstance();
    int ret = -1;
    if( w != NULL ){
        if(argc > 1){
            QFileInfo fi(argv[1]);
            if(fi.exists()){
                w->openFile(fi.absoluteFilePath());
            }
        }

        w->show();
        ret = a.exec();
    }
    delete w;
    return ret;
}
