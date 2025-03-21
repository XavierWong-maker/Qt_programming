#include "MainWindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QMap>
#include <QDropEvent>
#include <QMimeData>
#include <QInputDialog>
#include <QTextBlock>
#include <QStatusBar>


QString MainWindow::showFileDialog(QFileDialog::AcceptMode mode, QString title){
    QString ret = "";
    QFileDialog fd;
    QStringList filters;
    QMap<QString, QString> map;
    const char* fileArray[][2] =
    {
        {"Text(*.txt)",    ".txt"},
        {"All Files(*.*)",   "*" },
        {NULL,               NULL}
    };

    for(int i {0}; fileArray[i][0] != NULL; ++i){
        filters.append(fileArray[i][0]);
        map.insert(fileArray[i][0], fileArray[i][1]);
    }

    fd.setWindowTitle(title);
    fd.setAcceptMode(mode);
    fd.setNameFilters(filters);

    if(mode == QFileDialog::AcceptOpen){
        fd.setFileMode(QFileDialog::ExistingFile);
    }

    if(fd.exec() == QFileDialog::Accepted){
        ret = fd.selectedFiles()[0];
        QString posix = map[fd.selectedNameFilter()];

        if("*" != posix && !ret.endsWith(posix)){
            ret += posix;
        }
    }

    return ret;
}

void MainWindow::showErrorMessage(QString message){
    QMessageBox mb(this);
    mb.setWindowTitle("Error");
    mb.setText(message);
    mb.setIcon(QMessageBox::Critical);
    mb.setStandardButtons(QMessageBox::Ok);
    mb.exec();
}

int MainWindow::showQuesstionMessage(QString message){
    QMessageBox mb(this);
    mb.setWindowTitle("Error");
    mb.setText(message);
    mb.setIcon(QMessageBox::Question);
    mb.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    return mb.exec();
}

QString MainWindow::saveCurrentData(QString path){
    QString ret = path;
    if("" == ret){
        ret = showFileDialog(QFileDialog::AcceptSave, "save as");
    }

    if("" != ret){
        QFile file(ret);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);
            out << QString(mainEditor.toPlainText());
            file.close();
            setWindowTitle("NotePad - [" + ret + "]");
            m_isTextChanged = false;
        }else{
            showErrorMessage(QString("Open file Error!\n\n") + "\"" + ret + "\"");
            ret = "";
        }
    }
    return ret;
}

void MainWindow::preEditorChanged(){
    if(m_isTextChanged){
        int s = showQuesstionMessage("Do you want to Save?");
        switch (s) {
        case QMessageBox::Yes:
            saveCurrentData(m_filePath);
            break;
        case QMessageBox::No:
            m_isTextChanged = false;
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
}

QAction* MainWindow::findMenuBarAction(QString text){
    for(const QObject* obj : menuBar()->children()){
        if(const auto menu = qobject_cast<const QMenu*>(obj)){

            const QList<QAction*> actions = menu->actions();
            for(const QAction* action : actions){
                if(action->text().startsWith(text, Qt::CaseInsensitive)){
                    return const_cast<QAction*>(action);
                }
            }
        }
    }
    return nullptr;
}

QAction* MainWindow::findToolBarAction(QString text){
    for(const QObject* obj : children()){
        if(const auto tb = qobject_cast<const QToolBar*>(obj)){

            const QList<QAction*> actions = tb->actions();
            for(const QAction* action : actions){
                if(action->toolTip().startsWith(text, Qt::CaseInsensitive)){
                    return const_cast<QAction*>(action);
                }
            }
        }
    }
    return nullptr;
}

void MainWindow::updateActionState(const QString& actionText, bool checked){
    QAction* menuAction = findMenuBarAction(actionText);
    if(menuAction){
        menuAction->setChecked(checked);
    }

    QAction* toolAction = findToolBarAction(actionText);
    if(toolAction){
        toolAction->setChecked(checked);
    }
}

void MainWindow::openFileToEdit(QString path){
    if (!path.isEmpty()) {
        QFile file(path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            mainEditor.setPlainText(QString(file.readAll()));
            file.close();
            m_filePath = path;
            m_isTextChanged = false;
            setWindowTitle("NotePad - [" + m_filePath + "]");
        } else {
            showErrorMessage(QString("Open file Error!\n\n") + "\"" + path + "\"");
        }
    }
}

void MainWindow::onFileOpen(){
    preEditorChanged();
    if(!m_isTextChanged){
        QString path = showFileDialog(QFileDialog::AcceptOpen, "open");
        openFileToEdit(path);
    }
}

void MainWindow::onFileSave(){
    QString path = saveCurrentData(m_filePath);
    if("" != path){
        m_filePath = path;
    }
}

void MainWindow::onFileSaveAs(){
    QString path = saveCurrentData();
    if("" != path){
        m_filePath = path;
    }
}

void MainWindow::onFileNew(){
    preEditorChanged();
    if(!m_isTextChanged){
        mainEditor.clear();
        m_filePath = "";
        m_isTextChanged = false;
        setWindowTitle("NotePad-[New]");
    }
}

void MainWindow::onEditFind(){
    m_FindDlg->show();
}

void MainWindow::onEditDelete(){
    QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
    QKeyEvent keyRelease(QEvent::KeyRelease, Qt::Key_Delete, Qt::NoModifier);

    QApplication::sendEvent(&mainEditor, &keyPress);
    QApplication::sendEvent(&mainEditor, &keyRelease);
}

void MainWindow::onEditReplce(){
    m_ReplaceDlg->show();
}

void MainWindow::onEditGoto(){
    int maxLines = mainEditor.document()->lineCount();
    bool ok = false;
    int lineNumber =  QInputDialog::getInt(this, tr("Go to Line"),
                                          tr("Line number (1 - %1):").arg(maxLines),
                                          1, 1, maxLines, 1, &ok);

    if(ok){
        QString text = mainEditor.toPlainText();
        QTextCursor cursor = mainEditor.textCursor();

        int pos = 0;
        int next = -1;
        for(int i = 0; i < lineNumber; ++i){
            pos = next + 1;
            next = text.indexOf('\n', pos);
        }
        cursor.setPosition(pos);
        mainEditor.setTextCursor(cursor);
    }
}

void MainWindow::onEditExit(){
    close();
}

void MainWindow::onViewStatusBar(){
    QStatusBar* status = statusBar();
    if(!status){
        return;
    }
    bool newVisible = !status->isVisible();
    status->setVisible(newVisible);
    updateActionState("Status Bar",newVisible);
}
void MainWindow::onViewToolBar(){
    auto toolbars = findChildren<QToolBar*>();
    if(toolbars.isEmpty()){
        return;
    }
    QToolBar* toolbar = toolbars.first();
    bool newVisible = !toolbar->isVisible();
    toolbar->setVisible(newVisible);
    updateActionState("Tool Bar", newVisible);
}

void MainWindow::onTextChanged(){
    if(!m_isTextChanged){
        setWindowTitle("*" + windowTitle());
    }
    m_isTextChanged = true;
}

void MainWindow::onCopyAvailable(bool available){
    QAction* action = findMenuBarAction("&Copy...");
    if(action){
        action->setEnabled(available);
    }
    action = findToolBarAction("Copy");
    if(action){
        action->setEnabled(available);
    }
    action = findMenuBarAction("Cu&t");
    if(action){
        action->setEnabled(available);
    }
    action = findToolBarAction("Cut");
    if(action){
        action->setEnabled(available);
    }
}

void MainWindow::onUndoAvailable(bool available){
    QAction* action = findMenuBarAction("&Undo");
    if(action){
        action->setEnabled(available);
    }
    action = findToolBarAction("Undo");
    if(action){
        action->setEnabled(available);
    }
}

void MainWindow::onRedoAvailable(bool available){
    QAction* action = findMenuBarAction("&Redo...");
    if(action){
        action->setEnabled(available);
    }
    action = findToolBarAction("Redo");
    if(action){
        action->setEnabled(available);
    }
}

void MainWindow::onCursorPositionChanged(){
    QTextCursor cursor = mainEditor.textCursor();
    int line = cursor.blockNumber();
    int colum = cursor.columnNumber();
    statusLbl.setText(QString("Ln: %1        Col: %2")
                          .arg(line+1)
                          .arg(colum+1));
}

void MainWindow::closeEvent(QCloseEvent *e){
    preEditorChanged();
    if(!m_isTextChanged){
        QMainWindow::closeEvent(e);
    }else{
        e->ignore();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent* e){
    if(e->mimeData()->hasUrls()){
        e->acceptProposedAction();
    }else{
        e->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent* e){
    if(e->mimeData()->hasUrls()){
        QList<QUrl> list = e->mimeData()->urls();
        QString path = list[0].toLocalFile();
        QFileInfo fi(path);

        if(fi.isFile()){
            preEditorChanged();

            if(!m_isTextChanged){
                openFileToEdit(path);
            }
            e->accept();
        }else{
            showErrorMessage("Canot open a folder");
            e->accept();
        }
    }else{
        e->ignore();
    }
}

