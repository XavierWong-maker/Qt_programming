#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include <QFont>
#include <QSize>
#include <QPoint>

class AppConfig : public QObject
{
    Q_OBJECT
    QFont m_editFont;
    bool m_isToolBarVisible;
    bool m_isStatusVisible;
    bool m_isAutoWrap;
    QSize m_mainWindowSize;
    QPoint m_mainWindowPoint;
    bool m_isValid;

    bool restore();

public:
    explicit AppConfig(QObject *parent = nullptr);
    explicit AppConfig(QFont editFont, bool isToolBarVisible, bool isStatusVisible,
                       bool isAutoWrap, QSize size, QPoint point, QObject *parent = nullptr);

    QFont editFont();
    bool isToolBarVisible();
    bool isStatusBarVisible();
    bool isAutoWrap();
    QSize mainWindowSize();
    QPoint mainWindowPoint();
    bool isValid();
    bool store();
};

#endif // APPCONFIG_H
