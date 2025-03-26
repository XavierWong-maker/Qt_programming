#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QPlainTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QFileSystemModel m_fileModel;
    QPlainTextEdit  m_edit;

protected slots:
    void onDirectoryLoaded(const QString& path);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
