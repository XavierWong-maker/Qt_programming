#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMap>
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
    QPlainTextEdit msgEditor;
    QLineEdit inputEdit;
    QPushButton logInOutBtn;
    QPushButton sendBtn;
    QLabel statusLab;
    QLoginDialog loginDlg;

    ClientDemo m_client;
    QMap<QString, MsgHandler>m_handlerMap;

    void initMember();
    void initMsgGrpBx();
    void initInputGrpBx();
    void connectSlot();
    void setCtrlEnabled(bool enabled);

    void CONN_Handler(QTcpSocket&, TextMessage&);
    void DSCN_Handler(QTcpSocket&, TextMessage&);
    void LIOK_Handler(QTcpSocket&, TextMessage&);
    void LIER_Handler(QTcpSocket&, TextMessage&);
    void MSGA_Handler(QTcpSocket&, TextMessage&);

private slots:
    void sendBtnClicked();
    void logInOutBtnClicked();

public:
    MainWin(QWidget *parent = nullptr);
    void handle(QTcpSocket& obj, TextMessage& message) override;
    ~MainWin();
};
#endif // MAINWIN_H
