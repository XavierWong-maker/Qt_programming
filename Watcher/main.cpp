#include <QApplication>
#include <QString>
#include "Watcher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Watcher watcher;
    QString dirPath("C:/Users/Administrator/Desktop/qt");
    QString filePath("C:/Users/Administrator/Desktop/qt/file_watcher.txt");
    watcher.addPath(dirPath);
    watcher.addPath(filePath);
    return a.exec();
}
