#include "MainWindow.h"
#include <QFileDialog>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QMap>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QList>
#include <QUrl>

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

void MainWindow::onTextChanged(){
    if(!m_isTextChanged){
        setWindowTitle("*" + windowTitle());
    }
    m_isTextChanged = true;
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

