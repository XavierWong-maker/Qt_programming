#include "MainWindow.h"
#include <QMenu>
#include <QKeySequence>
#include <QKeyCombination>
#include <QIcon>
#include <QSize>
#include <QStatusBar>
#include <QLabel>
#include "AppConfig.h"

MainWindow::MainWindow() :
    statusLbl(this),
    m_FindDlg(new FindDialog(this, &mainEditor)),
    m_ReplaceDlg(new ReplacDialog(this, &mainEditor)){

    m_filePath = "";
    m_isTextChanged = false;
    setWindowTitle("NotePad-[New]");
    mainEditor.setAcceptDrops(false);
}

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
    AppConfig config;

    ret = ret && initMenuBar();
    ret = ret && initToolBar();
    ret = ret && initStatusBar();
    ret = ret && initMainEditor();

    if(config.isValid()){
        mainEditor.setFont(config.editFont());

        if(!config.isAutoWrap()){
            mainEditor.setLineWrapMode(QPlainTextEdit::NoWrap);
            findMenuBarAction("Auto Wrap")->setChecked(false);
            findToolBarAction("Auto Wrap")->setChecked(false);
        }

        if(!config.isToolBarVisible()){
            toolBar()->setVisible(false);
            findMenuBarAction("Tool Bar")->setChecked(false);
            findToolBarAction("Tool Bar")->setChecked(false);
        }

        if(!config.isStatusBarVisible()){
            statusBar()->setVisible(false);
            findMenuBarAction("Status Bar")->setChecked(false);
            findToolBarAction("Status Bar")->setChecked(false);
        }
    }
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

    QLabel* label = new QLabel("X.Software", this);
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
    connect(&mainEditor,&QPlainTextEdit::textChanged, this, &MainWindow::onTextChanged);
    connect(&mainEditor, &QPlainTextEdit::copyAvailable, this, &MainWindow::onCopyAvailable);
    connect(&mainEditor, &QPlainTextEdit::undoAvailable, this, &MainWindow::onUndoAvailable);
    connect(&mainEditor, &QPlainTextEdit::redoAvailable, this, &MainWindow::onRedoAvailable);
    connect(&mainEditor, &QPlainTextEdit::cursorPositionChanged, this, &MainWindow::onCursorPositionChanged);
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
    connect(action, &QAction::triggered, this ,&MainWindow::onFileNew);
    fileMenu->addAction(action);

    if(!makeAction(action, "&Open...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_O)))){
        delete fileMenu;
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onFileOpen);
    fileMenu->addAction(action);

    if(!makeAction(action, "&Save", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_S)))){
        delete fileMenu;
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onFileSave);
    fileMenu->addAction(action);

    if(!makeAction(action, "Save &As...", QKeySequence(QKeyCombination()))){
        delete fileMenu;
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onFileSaveAs);
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
    connect(action, &QAction::triggered, this, &MainWindow::onEditExit);
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
    connect(action, &QAction::triggered, &mainEditor, &QPlainTextEdit::undo);
    action->setEnabled(false);
    editMenu->addAction(action);

    if (!makeAction(action, "&Redo...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_Y)))) {
        delete editMenu;
        return false;
    }
    connect(action, &QAction::triggered, &mainEditor, &QPlainTextEdit::redo);
    action->setEnabled(false);
    editMenu->addAction(action);
    editMenu->addSeparator();

    if (!makeAction(action, "Cu&t", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_X)))) {
        delete editMenu;
        return false;
    }
    connect(action, &QAction::triggered, &mainEditor, &QPlainTextEdit::cut);
    action->setEnabled(false);
    editMenu->addAction(action);

    if (!makeAction(action, "&Copy...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_C)))) {
        delete editMenu;
        return false;
    }
    connect(action, &QAction::triggered, &mainEditor, &QPlainTextEdit::copy);
    action->setEnabled(false);
    editMenu->addAction(action);

    if (!makeAction(action, "&Paste...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_V)))) {
        delete editMenu;
        return false;
    }
    connect(action, &QAction::triggered, &mainEditor, &QPlainTextEdit::paste);
    editMenu->addAction(action);

    if (!makeAction(action, "De&lete", QKeySequence(Qt::Key_Delete))) {
        delete editMenu;
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onEditDelete);
    editMenu->addAction(action);
    editMenu->addSeparator();

    if (!makeAction(action, "&Find...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_F)))) {
        delete editMenu;
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onEditFind);
    editMenu->addAction(action);

    if (!makeAction(action, "&Replace...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_H)))) {
        delete editMenu;
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onEditReplce);
    editMenu->addAction(action);

    if (!makeAction(action, "&Goto...", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_G)))) {
        delete editMenu;
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onEditGoto);
    editMenu->addAction(action);
    editMenu->addSeparator();

    if (!makeAction(action, "Select &All", QKeySequence(QKeyCombination(Qt::CTRL, Qt::Key_A)))) {
        delete editMenu;
        return false;
    }
    connect(action, &QAction::triggered, &mainEditor, &QPlainTextEdit::selectAll);
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

    if (!makeAction(action, "Auto Wrap", QKeySequence())) {
        delete formatMenu;
        return false;
    }
    action->setCheckable(true);
    action->setChecked(true);
    connect(action, &QAction::triggered, this, &MainWindow::onFormatWrap);
    formatMenu->addAction(action);

    if (!makeAction(action, "&Font...", QKeySequence())) {
        delete formatMenu;
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onFontDialog);
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

    if (!makeAction(action, "Tool Bar", QKeySequence())) {
        delete viewMenu;
        return false;
    }
    action->setCheckable(true);
    action->setChecked(true);
    connect(action, &QAction::triggered, this, &MainWindow::onViewToolBar);
    viewMenu->addAction(action);

    if (!makeAction(action, "Status Bar", QKeySequence())) {
        delete viewMenu;
        return false;
    }
    action->setCheckable(true);
    action->setChecked(true);
    connect(action, &QAction::triggered, this, &MainWindow::onViewStatusBar);
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
    connect(action, &QAction::triggered, this, &MainWindow::onFindHelp);
    helpMenu->addAction(action);

    if (!makeAction(action, "About NotePad...", QKeySequence())) {
        delete helpMenu;
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onHelpAbout);
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
    connect(action, &QAction::triggered, this, &MainWindow::onFileNew);
    tb->addAction(action);

    if (!makeAction(action, "Open", ":/Res/pic/open.png")) {
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onFileOpen);
    tb->addAction(action);

    if (!makeAction(action, "Save", ":/Res/pic/save.png")) {
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onFileSave);
    tb->addAction(action);

    if (!makeAction(action, "Save As", ":/Res/pic/saveas.png")) {
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onFileSaveAs);
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
    action->setEnabled(false);
    connect(action, &QAction::triggered, &mainEditor, &QPlainTextEdit::undo);
    tb->addAction(action);

    if (!makeAction(action, "Redo", ":/Res/pic/redo.png")) {
        return false;
    }
    action->setEnabled(false);
    connect(action, &QAction::triggered, &mainEditor, &QPlainTextEdit::redo);
    tb->addAction(action);

    if (!makeAction(action, "Cut", ":/Res/pic/cut.png")) {
        return false;
    }
    action->setEnabled(false);
    connect(action, &QAction::triggered, &mainEditor, &QPlainTextEdit::cut);
    tb->addAction(action);

    if (!makeAction(action, "Copy", ":/Res/pic/copy.png")) {
        return false;
    }
    action->setEnabled(false);
    connect(action, &QAction::triggered, &mainEditor, &QPlainTextEdit::copy);
    tb->addAction(action);

    if (!makeAction(action, "Paste", ":/Res/pic/paste.png")) {
        return false;
    }
    connect(action, &QAction::triggered, &mainEditor, &QPlainTextEdit::paste);
    tb->addAction(action);

    if (!makeAction(action, "Find", ":/Res/pic/find.png")) {
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onEditFind);
    tb->addAction(action);

    if (!makeAction(action, "Replace", ":/Res/pic/replace.png")) {
        return false;
    }
    tb->addAction(action);

    if (!makeAction(action, "Goto", ":/Res/pic/goto.png")) {
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onEditGoto);
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
    connect(action, &QAction::triggered, this, &MainWindow::onFormatWrap);
    tb->addAction(action);

    if (!makeAction(action, "Font", ":/Res/pic/font.png")) {
        return false;
    }
    connect(action, &QAction::triggered, this, &MainWindow::onFontDialog);
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
    action->setCheckable(true);
    action->setChecked(true);
    connect(action, &QAction::triggered, this, &MainWindow::onViewToolBar);
    tb->addAction(action);

    if (!makeAction(action, "Status Bar", ":/Res/pic/status.png")) {
        return false;
    }
    action->setCheckable(true);
    action->setChecked(true);
    connect(action, &QAction::triggered, this, &MainWindow::onViewStatusBar);
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

QToolBar* MainWindow::toolBar(){
    for(QObject* obj : children()){
        if(auto tb = qobject_cast<QToolBar*>(obj)){
            return tb;
        }
    }
    return nullptr;
}

MainWindow::~MainWindow() {}
