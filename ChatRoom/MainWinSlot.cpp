#include "MainWin.h"
#include <QMessageBox>

namespace {
    constexpr char SERVER_IP[] = "127.0.0.1";
    constexpr quint16 SERVER_PORT = 8890;
}

void MainWin::initMember(){
    m_client.setHandler(this);

    m_handlerMap = {
        {"CONN", &MainWin::CONN_Handler},
        {"DSCN", &MainWin::DSCN_Handler},
        {"LIOK", &MainWin::LIOK_Handler},
        {"LIER", &MainWin::LIER_Handler},
        {"MSGA", &MainWin::MSGA_Handler}
    };
}

void MainWin::sendBtnClicked(){
    const QString formattedText = QStringLiteral("%1:\n   %2\n").arg(inputGrpBx.title(), inputEdit.text());
    TextMessage message("MSGA", formattedText.toUtf8());

    if(m_client.send(message)){
        inputEdit.clear();
    }
}

void MainWin::logInOutBtnClicked(){
    if(!m_client.isValid()){
        if(loginDlg.exec() == QDialog::Accepted){
            const QString user = loginDlg.getUser().trimmed();
            const QString pwd = loginDlg.getPwd();

            if(m_client.connectTo(SERVER_IP, SERVER_PORT)){
                TextMessage loginMessage("LGIN", QStringLiteral("%1\r%2").arg(user, pwd).toUtf8());
                m_client.send(loginMessage);
            }else{
                QMessageBox::critical(this, "Failure", "Unable to connect to the remote server");
            }
        }
    }else{
        m_client.close();
    }
}

void MainWin::handle(QTcpSocket& socket, TextMessage& message){
    auto it = m_handlerMap.find(message.type());
    if(it != m_handlerMap.end()){
        MsgHandler handler = it.value();
        (this->*handler)(socket, message);
    }
}

void MainWin::CONN_Handler(QTcpSocket&, TextMessage&){
}

void MainWin::DSCN_Handler(QTcpSocket&, TextMessage&){
    setCtrlEnabled(false);
    inputGrpBx.setTitle(QStringLiteral("user name"));
}

void MainWin::LIOK_Handler(QTcpSocket&, TextMessage& message){
    setCtrlEnabled(true);
    inputGrpBx.setTitle(message.data());
}

void MainWin::LIER_Handler(QTcpSocket&, TextMessage&){
    QMessageBox::critical(this, QStringLiteral("error"), QStringLiteral("Identity verification failed!"));
    m_client.close();
}

void MainWin::MSGA_Handler(QTcpSocket&, TextMessage& message){
    msgEditor.appendPlainText(message.data());
}

MainWin::~MainWin() {
    m_client.close();
}

