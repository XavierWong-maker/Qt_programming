#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include <QFileSystemWatcher>

class Watcher : public QObject
{
    Q_OBJECT

private:
    QFileSystemWatcher m_watcher;

private slots:
    void statusChanged(const QString &path);
public:
    explicit Watcher(QObject *parent = nullptr);
    void addPath(QString path);
};

#endif // WATCHER_H
