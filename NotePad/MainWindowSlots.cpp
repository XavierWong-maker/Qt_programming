#include "MainWindow.h"
#include <QFileDialog>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

QString MainWindow::showFileDialog(QFileDialog::AcceptMode mode, QString title){
    QString ret = "";
    QFileDialog fd;

    fd.setWindowTitle(title);
    fd.setAcceptMode(mode);
    QStringList filters;
    filters.append("Text(*.txt)");
    filters.append("All Files(*.*)");
    fd.setNameFilters(filters);

    if(mode == QFileDialog::AcceptOpen){
        fd.setFileMode(QFileDialog::ExistingFile);
    }

    if(fd.exec() == QFileDialog::Accepted){
        ret = fd.selectedFiles()[0];
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

void MainWindow::onFileOpen(){
    preEditorChanged();
    if(!m_isTextChanged){
        QString path = showFileDialog(QFileDialog::AcceptOpen, "open");
        if("" != path){
            QFile file(path);
            if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
                mainEditor.setPlainText(QString(file.readAll()));
                file.close();
                m_filePath = path;
                setWindowTitle("NotePad - [" + m_filePath + "]");
            }else {
                showErrorMessage(QString("Open file Error!\n\n") + "\"" + m_filePath + "\"");
            }
        }
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
