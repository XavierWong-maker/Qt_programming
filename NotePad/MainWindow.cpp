#include "MainWindow.h"
#include <QMenu>
#include <QKeySequence>
#include <QKeyCombination>
#include <QIcon>
#include <QSize>
#include <QStatusBar>
#include <QLabel>

MainWindow::MainWindow(){}

MainWindow* MainWindow::NewInstance(){

    auto ret = new MainWindow();
    if(!ret || !ret->construct()){
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool MainWindow::construct(){
    bool ret = true;
    ret = ret && initMenuBar();
    ret = ret && initToolBar();
    ret = ret && initStatusBar();
    ret = ret && initMainEditor();

    return ret;
}

bool MainWindow::initMenuBar(){
    bool ret = true;
    QMenuBar* mb = menuBar();

    ret = ret && initFileMenu(mb);
    ret = ret && initEditMenu(mb);
    ret = ret && initFormatMenu(mb);
    ret = ret && initViewMenu(mb);
    ret = ret && initHelpMenu(mb);

    return ret;
}

bool MainWindow::initToolBar(){
    bool ret = true;
    auto tb = addToolBar("Tool Bar");
    tb->setIconSize(QSize(16, 16));

    ret = ret && initFileToolItem(tb);
    tb->addSeparator();
    ret = ret && initEditToolItem(tb);
    tb->addSeparator();
    ret = ret && initFormatToolItem(tb);
    tb->addSeparator();
    ret = ret && initViewToolItem(tb);

    return ret;
}

bool MainWindow::initStatusBar() {
    QStatusBar* sb = statusBar();
    if (!sb) {
        return false;
    }

    QLabel* label = new QLabel("W.Software", this);
    if (!label) {
        return false;
    }

    statusLbl.setMinimumWidth(200);
    statusLbl.setAlignment(Qt::AlignCenter);
    statusLbl.setText("Ln: 1    Col: 1");

    label->setMinimumWidth(200);
    label->setAlignment(Qt::AlignCenter);

    sb->addPermanentWidget(new QLabel("", this));
    sb->addPermanentWidget(&statusLbl);
    sb->addPermanentWidget(label);

    return true;
}

bool MainWindow::initMainEditor() {

    mainEditor.setParent(this);
    setCentralWidget(&mainEditor);
    return true;
}

bool MainWindow::initFileMenu(QMenuBar* mb){
    if(!mb){
        return false;
    }

    auto fileMenu = new QMenu("&File", mb);
    QAction* action = nullptr;

    if(!makeAction(action, "&New", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_N)))){
        delete fileMenu;
        return false;
    }
    fileMenu->addAction(action);

    if(!makeAction(action, "&Open...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_O)))){
        delete fileMenu;
        return false;
    }
    fileMenu->addAction(action);

    if(!makeAction(action, "&Save", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_S)))){
        delete fileMenu;
        return false;
    }
    fileMenu->addAction(action);

    if(!makeAction(action, "Save &As...", QKeySequence(QKeyCombination()))){
        delete fileMenu;
        return false;
    }
    fileMenu->addAction(action);
    fileMenu->addSeparator();

    if(!makeAction(action, "&Printf...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_P)))){
        delete fileMenu;
        return false;
    }
    fileMenu->addAction(action);
    fileMenu->addSeparator();

    if(!makeAction(action, "&Exit",QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_X)))){
        delete fileMenu;
        return false;
    }
    fileMenu->addAction(action);

    mb->addMenu(fileMenu);
    return true;
}

bool MainWindow::initEditMenu(QMenuBar* mb) {
    if (!mb) {
        return false;
    }

    auto editMenu = new QMenu("&Edit", mb);
    QAction* action = nullptr;

    if (!makeAction(action, "&Undo", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_Z)))) {
        delete editMenu;
        return false;
    }
    editMenu->addAction(action);

    if (!makeAction(action, "&Redo...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_Y)))) {
        delete editMenu;
        return false;
    }
    editMenu->addAction(action);
    editMenu->addSeparator();

    if (!makeAction(action, "Cu&t", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_X)))) {
        delete editMenu;
        return false;
    }
    editMenu->addAction(action);

    if (!makeAction(action, "&Copy...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_C)))) {
        delete editMenu;
        return false;
    }
    editMenu->addAction(action);

    if (!makeAction(action, "&Paste...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_V)))) {
        delete editMenu;
        return false;
    }
    editMenu->addAction(action);

    if (!makeAction(action, "De&lete", QKeySequence(Qt::Key_Delete))) {
        delete editMenu;
        return false;
    }
    editMenu->addAction(action);
    editMenu->addSeparator();

    if (!makeAction(action, "&Find...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_F)))) {
        delete editMenu;
        return false;
    }
    editMenu->addAction(action);

    if (!makeAction(action, "&Replace...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_H)))) {
        delete editMenu;
        return false;
    }
    editMenu->addAction(action);

    if (!makeAction(action, "&Goto...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_G)))) {
        delete editMenu;
        return false;
    }
    editMenu->addAction(action);
    editMenu->addSeparator();

    if (!makeAction(action, "Select &All", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_A)))) {
        delete editMenu;
        return false;
    }
    editMenu->addAction(action);

    mb->addMenu(editMenu);
    return true;
}

bool MainWindow::initFormatMenu(QMenuBar* mb) {
    if (!mb) {
        return false;
    }

    auto formatMenu = new QMenu("F&ormat", mb);
    QAction* action = nullptr;

    if (!makeAction(action, "Auto &Wrap", QKeySequence())) {
        delete formatMenu;
        return false;
    }
    formatMenu->addAction(action);

    if (!makeAction(action, "&Font...", QKeySequence())) {
        delete formatMenu;
        return false;
    }
    formatMenu->addAction(action);

    mb->addMenu(formatMenu);
    return true;
}

bool MainWindow::initViewMenu(QMenuBar* mb) {
    if (!mb) {
        return false;
    }

    auto viewMenu = new QMenu("&View", mb);
    QAction* action = nullptr;

    if (!makeAction(action, "&Tool Bar", QKeySequence())) {
        delete viewMenu;
        return false;
    }
    viewMenu->addAction(action);

    if (!makeAction(action, "&Status Bar", QKeySequence())) {
        delete viewMenu;
        return false;
    }
    viewMenu->addAction(action);

    mb->addMenu(viewMenu);
    return true;
}

bool MainWindow::initHelpMenu(QMenuBar* mb) {
    if (!mb) {
        return false;
    }

    auto helpMenu = new QMenu("&Help", mb);
    QAction* action = nullptr;

    if (!makeAction(action, "User Manual", QKeySequence())) {
        delete helpMenu;
        return false;
    }
    helpMenu->addAction(action);

    if (!makeAction(action, "About NotePad...", QKeySequence())) {
        delete helpMenu;
        return false;
    }
    helpMenu->addAction(action);

    mb->addMenu(helpMenu);
    return true;
}

bool MainWindow::initFileToolItem(QToolBar* tb) {
    if (!tb) {
        return false;
    }
    QAction* action = nullptr;

    if (!makeAction(action, "New", ":/Res/pic/new.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Open", ":/Res/pic/open.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Save", ":/Res/pic/save.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Save As", ":/Res/pic/saveas.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Print", ":/Res/pic/print.png")) {
        return false;
    }
    tb->addAction(action);

    return true;
}

bool MainWindow::initEditToolItem(QToolBar* tb) {
    if (!tb) {
        return false;
    }

    QAction* action = nullptr;
    if (!makeAction(action, "Undo", ":/Res/pic/undo.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Redo", ":/Res/pic/redo.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Cut", ":/Res/pic/cut.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Copy", ":/Res/pic/copy.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Paste", ":/Res/pic/paste.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Find", ":/Res/pic/find.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Replace", ":/Res/pic/replace.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Goto", ":/Res/pic/goto.png")) {
        return false;
    }
    tb->addAction(action);

    return true;
}

bool MainWindow::initFormatToolItem(QToolBar* tb) {
    if (!tb) {
        return false;
    }

    QAction* action = nullptr;
    if (!makeAction(action, "Auto Wrap", ":/Res/pic/wrap.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Font", ":/Res/pic/font.png")) {
        return false;
    }
    tb->addAction(action);

    return true;
}

bool MainWindow::initViewToolItem(QToolBar* tb) {
    if (!tb) {
        return false;
    }

    QAction* action = nullptr;
    if (!makeAction(action, "Tool Bar", ":/Res/pic/tool.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Status Bar", ":/Res/pic/status.png")) {
        return false;
    }
    tb->addAction(action);

    return true;
}

bool MainWindow::makeAction(QAction* &action, const QString text, const QKeySequence& shortcut){
    action = new QAction(text, nullptr);
    if(action){
        action->setShortcut(shortcut);
    }else{
        return false;
    }
    return true;
}

bool MainWindow::makeAction(QAction* &action, const QString tip, const QString icon){
    action = new QAction("", this);
    if(!action){
        return false;
    }

    action->setToolTip(tip);
    action->setIcon(QIcon(icon));
    return true;
}

MainWindow::~MainWindow() {}
