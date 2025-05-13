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
        {"MSGA", &MainWin::MSGA_Handler},
        {"USER", &MainWin::USER_Handler},
        {"CTRL", &MainWin::CTRL_Handler}
    };
}

QString MainWin::getCheckedUserId() const{
    QStringList checkedUsers;
    for(int i = 0; i < listWidget.count(); ++i){
        auto item = listWidget.item(i);
        if(item && item->checkState() == Qt::Checked){
            checkedUsers << item->text();
        }
    }
    return checkedUsers.join('\r');
}

void MainWin::sendBtnClicked(){
    QString input = inputEdit.text().trimmed();
    if(input.isEmpty()){
        return;
    }

    QString self = inputGrpBx.title();
    QString text = QStringLiteral("%1:\n   %2\n").arg(self, input);
    QString uid = getCheckedUserId();
    bool success;

    if(uid.isEmpty()){  // Broadcast message to all users
        TextMessage tm("MSGA", text.toUtf8());
        success = m_client.send(tm);

    }else{ // Send private message to selected users
        QString sid = uid.contains(self) ? uid : uid + self + QStringLiteral("\r");
        TextMessage tm("MSGP", (sid + text).toUtf8());
        success = m_client.send(tm);
    }

    if(success){
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

void MainWin::listWidgetMenuClicked(){
    auto* action = qobject_cast<QAction*>(sender());
    const auto selectItems = listWidget.selectedItems();

    if(!selectItems.isEmpty()){
        QString user = selectItems.first()->text();
        QString prompt = QStringLiteral("Is it confirmed to perform the %1 operation on the chat member [%2]?")
                             .arg(action->text(), user);
        if(QMessageBox::question(this, QStringLiteral("tips"), prompt, QMessageBox::Yes | QMessageBox::No,
        QMessageBox::Yes) == QMessageBox::Yes){
            QString data = QStringLiteral("%1\r%2").arg(action->objectName(), user);
            TextMessage tm = TextMessage("ASMN", data.toUtf8());
            m_client.send(tm);
        }

    }else{
        QMessageBox::information(this, QStringLiteral("tips"), QStringLiteral("Please select the chat members : "));
    }
}

void MainWin::listWidgetContextMenu(const QPoint&){
    if("admin" != m_level){
        return;
    }
    listWidgetMenu.exec(QCursor::pos());
}

void MainWin::handle(QTcpSocket& socket, TextMessage& message){
    auto it = m_handlerMap.find(QString::fromUtf8(message.type()));
    if(it != m_handlerMap.end()){
        MsgHandler handler = it.value();
        (this->*handler)(socket, message);

    }else{
        qDebug() << "Unhandled message type:" << QString::fromUtf8(message.type());
    }
}

void MainWin::CONN_Handler(QTcpSocket&, TextMessage&){
}

void MainWin::DSCN_Handler(QTcpSocket&, TextMessage&){
    setCtrlEnabled(false);
    inputGrpBx.setTitle(QStringLiteral("user name"));
    m_level = "";
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

void MainWin::USER_Handler(QTcpSocket&, TextMessage& message){
    QStringList users = QString::fromUtf8(message.data()).split('\r', Qt::SkipEmptyParts);
    QStringList checkedUsers = getCheckedUserId().split('\r', Qt::SkipEmptyParts);
    listWidget.clear();

    for(const QString& user : users){
        auto item = new QListWidgetItem(user, &listWidget);
        item->setCheckState(checkedUsers.contains(user) ? Qt::Checked : Qt::Unchecked);
    }
}

void MainWin::CTRL_Handler(QTcpSocket &, TextMessage &message){
    const QByteArray data = message.data();

    if("silent" == data){
        QMessageBox::information(this, "Tips", "You have been muted by the administrator!");
        inputEdit.clear();
        inputEdit.setEnabled(false);
        sendBtn.setEnabled(false);

    }else if("recover" == data){
        QMessageBox::information(this, "Tips", "The administrator has restored your chat permission!");
        inputEdit.setEnabled(true);
        sendBtn.setEnabled(true);

    }else if("kick" == data){
        QMessageBox::information(this, "Tips", QStringLiteral("Account [%1] is prohibited from logging in to chat!")
                                                   .arg(inputGrpBx.title()));
        m_client.close();

    }else{
        qDebug() << "Unknown CTRL message:" << data;
    }
}

MainWin::~MainWin() {
    m_client.close();
}

