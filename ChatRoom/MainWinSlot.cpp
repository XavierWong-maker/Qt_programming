#include "MainWin.h"

void MainWin::sendBtnClicked(){

}

void MainWin::logInOutBtnClicked(){

    if(loginDlg.exec() == QDialog::Accepted){
        inputEdit.setEnabled(true);
        sendBtn.setEnabled(true);
        logInOutBtn.setText("Logout");

    }else{
        if(!loginDlg.getUser().isEmpty()){
        }
    }
}

