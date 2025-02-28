#include "Widget.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.resize(300,200);
    w.move(1200,500);

    w.show();

    qDebug() << "QWidget:";
    qDebug() << w.x();
    qDebug() << w.y();
    qDebug() << w.width();
    qDebug() << w.height();
    qDebug() << "geometry()";
    qDebug() << w.geometry().x();
    qDebug() << w.geometry().y();
    qDebug() << w.geometry().width();
    qDebug() << w.geometry().height();
    qDebug() << "frameGeometry";
    qDebug() << w.frameGeometry().x();
    qDebug() << w.frameGeometry().y();
    qDebug() << w.frameGeometry().width();
    qDebug() << w.frameGeometry().height();


    return a.exec();
}
