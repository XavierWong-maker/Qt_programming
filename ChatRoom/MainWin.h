#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QMap>
#include <QMenu>
#include "QLogindialog.h"
#include "ClientDemo.h"
#include "TxtMsgHandler.h"


class MainWin : public QMainWindow, public TxtMsgHandler
{
    Q_OBJECT

    using MsgHandler = void (MainWin::*)(QTcpSocket&, TextMessage&);

    QVBoxLayout vMainLayout;
    QGroupBox msgGrpBx;
    QGroupBox inputGrpBx;
    QListWidget listWidget;
    QMenu listWidgetMenu;
    QPlainTextEdit msgEditor;
    QLineEdit inputEdit;
    QPushButton logInOutBtn;
    QPushButton sendBtn;
    QLabel statusLab;
    QLoginDialog loginDlg;

    ClientDemo m_client;
    QString m_level;
    QMap<QString, MsgHandler>m_handlerMap;

    void initMember();
    void initMsgGrpBx();
    void initInputGrpBx();
    void initListWidgetMenu();
    void connectSlot();
    void setCtrlEnabled(bool enabled);
    QString getCheckedUserId() const;
    bool eventFilter(QObject* obj, QEvent* evt) override;

    void CONN_Handler(QTcpSocket&, TextMessage&);
    void DSCN_Handler(QTcpSocket&, TextMessage&);
    void LIOK_Handler(QTcpSocket&, TextMessage&);
    void LIER_Handler(QTcpSocket&, TextMessage&);
    void MSGA_Handler(QTcpSocket&, TextMessage&);
    void USER_Handler(QTcpSocket&, TextMessage&);
    void CTRL_Handler(QTcpSocket&, TextMessage&);

private slots:
    void sendBtnClicked();
    void logInOutBtnClicked();
    void listWidgetMenuClicked();
    void listWidgetContextMenu(const QPoint&);

public:
    MainWin(QWidget *parent = nullptr);
    void handle(QTcpSocket& obj, TextMessage& message) override;
    ~MainWin();
};
#endif // MAINWIN_H
