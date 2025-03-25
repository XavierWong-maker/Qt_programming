#include "AppConfig.h"
#include <QFile>
#include <QApplication>

AppConfig::AppConfig(QObject *parent)
    : QObject{parent}{

    m_isValid = restore();
}

AppConfig::AppConfig(QFont editFont, bool isToolBarVisible, bool isStatusVisible,
                     bool isAutoWrap, QSize size, QPoint point, QObject*){

    m_editFont = editFont;
    m_isToolBarVisible = isToolBarVisible;
    m_isStatusVisible = isStatusVisible;
    m_isAutoWrap = isAutoWrap;
    m_mainWindowSize = size;
    m_mainWindowPoint = point;
    m_isValid = true;
}

QFont AppConfig::editFont(){
    return m_editFont;
}

bool AppConfig::isToolBarVisible(){
    return m_isToolBarVisible;
}

bool AppConfig::isStatusBarVisible(){
    return m_isStatusVisible;
}

bool AppConfig::isAutoWrap(){
    return m_isAutoWrap;
}

QSize AppConfig::mainWindowSize(){
    return m_mainWindowSize;
}

QPoint AppConfig::mainWindowPoint(){
    return m_mainWindowPoint;
}

bool AppConfig::isValid(){
    return m_isValid;
}

bool AppConfig::restore(){
    bool ret = true;
    QFile file(QApplication::applicationDirPath() + "/app.config");

    if(file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_6_8);

        in >> m_editFont >> m_isToolBarVisible >> m_isStatusVisible >> m_isAutoWrap >> m_mainWindowSize >> m_mainWindowPoint;
        file.close();
    }else{
        ret = false;
    }
    return ret;
}

bool AppConfig::store(){
    bool ret = true;
    QFile file(QApplication::applicationDirPath() + "/app.config");

    if(file.open(QIODevice::WriteOnly)){
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_6_8);

        out << m_editFont << m_isToolBarVisible << m_isStatusVisible << m_isAutoWrap << m_mainWindowSize << m_mainWindowPoint;

        file.close();
    }else{
        ret = false;
    }

    return ret;
}
