#include "MainWindow.h"
#include <QByteArray>
#include <QBuffer>
#include <QTextStream>
#include <QIODevice>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    m_edit.setParent(this);
    m_edit.resize(800, 600);
    m_edit.move(10, 10);

    m_fileModel.setRootPath(QDir::currentPath());
    connect(&m_fileModel, &QFileSystemModel::directoryLoaded, this, &MainWindow::onDirectoryLoaded);
}

void MainWindow::onDirectoryLoaded(const QString& path){

    QModelIndex root = m_fileModel.index(path);
    QByteArray array;
    QBuffer buffer(&array);

    if(buffer.open(QIODevice::WriteOnly)){
        QTextStream out(&buffer);
        out << m_fileModel.isDir(root) << Qt::endl;
        out << m_fileModel.data(root).toString() << Qt::endl;
        out << root.data().toString() << Qt::endl;
        out << &m_fileModel << Qt::endl;
        out << root.model() << Qt::endl;
        out << m_fileModel.filePath(root) << Qt::endl;
        out << m_fileModel.fileName(root) << Qt::endl;
        out << Qt::endl;

        for(int i{0}; i < m_fileModel.rowCount(root); ++i){
            QModelIndex mi = m_fileModel.index(i, 0,root);
            out << mi.data().toString() << Qt::endl;
        }

        out.flush();
        buffer.close();

        if(buffer.open(QIODevice::ReadOnly)){
            QTextStream in(&buffer);
            m_edit.insertPlainText(in.readAll());
            buffer.close();
        }
    }
}

MainWindow::~MainWindow() {}
