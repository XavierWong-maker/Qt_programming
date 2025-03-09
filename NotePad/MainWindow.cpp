#include "MainWindow.h"
#include <QMenu>
#include <QKeySequence>
#include <QKeyCombination>

MainWindow::MainWindow(){}

MainWindow* MainWindow::NewInstance(){

    MainWindow* ret = new MainWindow();
    if(!ret || !ret->construct()){
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool MainWindow::construct(){
    bool ret = true;
    ret = ret && initMenuBar();
    return ret;
}

bool MainWindow::initMenuBar(){
    bool ret = true;
    QMenuBar* mb = menuBar();
    ret = ret && initFileMenu(mb);
    return ret;
}

bool MainWindow::initFileMenu(QMenuBar* mb){
    if(!mb){
        return false;
    }

    QMenu* fileMenu = new QMenu("&File", mb);

    QAction* newAction = nullptr;
    if(!makeAction(newAction, "&New", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_N)))){
        return false;
    }

    fileMenu->addAction(newAction);
    fileMenu->addSeparator();

    QAction* exitAction = nullptr;
    if(!makeAction(exitAction, "&Exit",QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_X)))){
        return false;
    }
    fileMenu->addAction(exitAction);
    mb->addMenu(fileMenu);
    return true;
}

bool MainWindow::makeAction(QAction* &action, const QString text, const QKeySequence& shortcut){
    bool ret = true;
    action = new QAction(text, nullptr);
    if(action){
        action->setShortcut(shortcut);
    }else{
        ret = false;
    }
    return ret;
}

MainWindow::~MainWindow() {}
