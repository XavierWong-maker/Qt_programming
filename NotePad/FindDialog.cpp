#include "FindDialog.h"
#include <QEvent>
#include <QMessageBox>

FindDialog::FindDialog(QWidget* parent, QPlainTextEdit* pText)
    : QDialog(parent, Qt::WindowCloseButtonHint | Qt::Drawer){

    initControl();
    connectSlot();

    setPlainTextEdit(pText);
}

void FindDialog::initControl(){
    m_findLabel.setText("Find content: ");
    m_findButton.setText("Find next");
    m_checkBox.setText("Case sensitive");
    m_forwardButton.setText("up");
    m_backwardButton.setChecked(true);
    m_backwardButton.setText("down");
    m_cancleButton.setText("Cancel");
    m_gBox.setTitle("direction");

    m_hLayout.addWidget(&m_forwardButton);
    m_hLayout.addWidget(&m_backwardButton);
    m_gBox.setLayout(&m_hLayout);

    m_gLayout.setSpacing(10);
    m_gLayout.addWidget(&m_findLabel, 0, 0);
    m_gLayout.addWidget(&m_findLineEdit, 0, 1);
    m_gLayout.addWidget(&m_findButton, 0, 2);
    m_gLayout.addWidget(&m_checkBox, 1, 0);
    m_gLayout.addWidget(&m_gBox, 1, 1);
    m_gLayout.addWidget(&m_cancleButton, 1, 2);

    setLayout(&m_gLayout);
    setWindowTitle("find");
}

void FindDialog::connectSlot(){
    connect(&m_findButton, &QPushButton::clicked, this, &FindDialog::onFindButtonClicked);
    connect(&m_cancleButton, &QPushButton::clicked, this, &FindDialog::onCancleButtonClicked);
}

bool FindDialog::event(QEvent* e){
    if(e->type() == QEvent::Close){
        hide();
        return true;
    }
    return QDialog::event(e);
}

void FindDialog::setPlainTextEdit(QPlainTextEdit* pText){
    m_plainTextEdit = pText;
}

QPlainTextEdit* FindDialog::getPlainTextEdit(){
    return m_plainTextEdit;
}

void FindDialog::onFindButtonClicked(){
    if(!m_plainTextEdit) {
        return;
    }

    const QString target = m_findLineEdit.text().trimmed();
    if(target.isEmpty()){
        return;
    }

    const QString text = m_plainTextEdit->toPlainText();
    QTextCursor cursor = m_plainTextEdit->textCursor();
    const Qt::CaseSensitivity caseSensitivity = m_checkBox.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    int index = -1;

    if(m_backwardButton.isChecked()){
        index = text.indexOf(target, cursor.position(), caseSensitivity);
        if(index >= 0){
            cursor.setPosition(index);
            cursor.setPosition(index + target.length(), QTextCursor::KeepAnchor);
            m_plainTextEdit->setTextCursor(cursor);
        }
    }else if(m_forwardButton.isChecked()){
        index = text.lastIndexOf(target, cursor.position() - text.length() -1, caseSensitivity);
        if(index >= 0){
            cursor.setPosition(index + target.length());
            cursor.setPosition(index, QTextCursor::KeepAnchor);
            m_plainTextEdit->setTextCursor(cursor);
        }
    }

    if(index < 0){
        QMessageBox::information(this, tr("Find"), tr("Cannot find \"%1\"").arg(target),
                                 QMessageBox::Ok);
    }
}

void FindDialog::onCancleButtonClicked(){
    close();
}
