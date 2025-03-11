#include "Watcher.h"
#include <QDebug>

Watcher::Watcher(QObject *parent)
    : QObject{parent}{

    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &Watcher::statusChanged);
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &Watcher::statusChanged);
}

void Watcher::statusChanged(const QString &path){
    qDebug() << path << "is changed.";
}


void Watcher::addPath(QString path){
    m_watcher.addPath(path);
}
