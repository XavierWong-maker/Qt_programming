#include "Dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog d;
    int r = d.exec();
    if( r == QDialog::Accepted )
    {
        qDebug() << "Accepted";
    }
    else if( r == QDialog::Rejected )
    {
        qDebug() << "Rejected";
    }
    else
    {
        qDebug() << r;
    }

    return r;
}
