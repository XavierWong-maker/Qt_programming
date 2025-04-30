#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "QLogindialog.h"

class MainWin : public QMainWindow
{
    Q_OBJECT

    QVBoxLayout vMainLayout;
    QGroupBox msgGrpBx;
    QGroupBox inputGrpBx;
    QPlainTextEdit msgEditor;
    QLineEdit inputEdit;
    QPushButton logInOutBtn;
    QPushButton sendBtn;
    QLabel statusLab;
    QLoginDialog loginDlg;

    void initMsgGrpBx();
    void initInputGrpBx();
    void connectSlot();

private slots:
    void sendBtnClicked();
    void logInOutBtnClicked();

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();
};
#endif // MAINWIN_H
