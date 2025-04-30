#include "MainWin.h"

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent), loginDlg(this)
{
    QWidget* centralWidget = new QWidget(this);

    initMsgGrpBx();
    initInputGrpBx();
    connectSlot();

    vMainLayout.setSpacing(10);
    vMainLayout.addWidget(&msgGrpBx);
    vMainLayout.addWidget(&inputGrpBx);

    centralWidget->setLayout(&vMainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Chat");
    setMinimumSize(860, 640);
    resize(860, 640);

}

void MainWin::connectSlot(){
    connect(&logInOutBtn, &QPushButton::clicked, this, &MainWin::logInOutBtnClicked);
    connect(&sendBtn, &QPushButton::clicked, this, &MainWin::sendBtnClicked);
}

void MainWin::initMsgGrpBx(){
    QHBoxLayout* hbl = new QHBoxLayout();
    hbl->setContentsMargins(2,5,2,2);
    hbl->addWidget(&msgEditor);

    msgEditor.setReadOnly(true);
    msgGrpBx.setLayout(hbl);
    msgGrpBx.setTitle("message");
}

void MainWin::initInputGrpBx(){
    QGridLayout* gl = new QGridLayout();
    gl->setSpacing(10);
    gl->addWidget(&inputEdit,0,0,1,5);
    gl->addWidget(&statusLab,1,0,1,3);
    gl->addWidget(&logInOutBtn,1,3);
    gl->addWidget(&sendBtn,1,4);

    inputEdit.setFixedHeight(23);
    inputEdit.setEnabled(false);
    statusLab.setText("Status: Not logged in");
    logInOutBtn.setFixedHeight(30);
    logInOutBtn.setText("login");
    sendBtn.setFixedHeight(30);
    sendBtn.setText("Send");
    sendBtn.setEnabled(false);

    inputGrpBx.setFixedHeight(100);
    inputGrpBx.setLayout(gl);
    inputGrpBx.setTitle("user name");
}

MainWin::~MainWin() {}
