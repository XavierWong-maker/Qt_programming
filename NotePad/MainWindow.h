#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeySequence>
#include <QMenuBar>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    MainWindow();
    MainWindow(const MainWindow&);
    MainWindow& operator= (const MainWindow&);

    bool construct();
    bool initMenuBar();
    bool initFileMenu(QMenuBar* mb);
    bool makeAction(QAction* &action, const QString text, const QKeySequence& shortcut);
public:
    static MainWindow* NewInstance();
    ~MainWindow();
};
#endif // MAINWINDOW_H
