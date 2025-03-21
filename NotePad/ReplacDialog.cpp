#include "ReplacDialog.h"

ReplacDialog::ReplacDialog(QWidget* parent, QPlainTextEdit* pText)
    : FindDialog(parent, pText){

    initControl();
    connectSlot();
    setWindowTitle("Replace");

}

void ReplacDialog::initControl(){
    m_replaceButton.setText("Replace");
    m_replaceAllButton.setText("Replace All");
    m_replaceAsLabel.setText("Replace with: ");

    m_gLayout.removeWidget(&m_checkBox);
    m_gLayout.removeWidget(&m_gBox);
    m_gLayout.removeWidget(&m_cancleButton);

    m_gLayout.addWidget(&m_replaceAsLabel, 1, 0);
    m_gLayout.addWidget(&m_replaceEdit, 1, 1);
    m_gLayout.addWidget(&m_replaceButton, 1, 2);
    m_gLayout.addWidget(&m_replaceAllButton, 2, 2);
    m_gLayout.addWidget(&m_checkBox, 3, 0);
    m_gLayout.addWidget(&m_gBox, 3, 1);
    m_gLayout.addWidget(&m_cancleButton, 3, 2);

    setLayout(&m_gLayout);
}

void ReplacDialog::connectSlot(){
    connect(&m_replaceButton, &QPushButton::clicked, this, &ReplacDialog::onReplaceButtonClicked);
    connect(&m_replaceAllButton, &QPushButton::clicked, this, &ReplacDialog::onReplaceAllButtonClicked);
}

void ReplacDialog::onReplaceButtonClicked(){
    QString target = m_findLineEdit.text().trimmed();
    QString  replacement = m_replaceEdit.text().trimmed();

    if(!target.isEmpty() && !replacement.isEmpty() && !m_plainTextEdit.isNull()){
        QTextCursor cursor = m_plainTextEdit->textCursor();
        if(cursor.hasSelection()){
            QString selectedText = cursor.selectedText();
            if(selectedText == target){
                cursor.insertText(replacement);
            }
        }
        onFindButtonClicked();
    }
}

void ReplacDialog::onReplaceAllButtonClicked(){

    QString target = m_findLineEdit.text().trimmed();
    QString replacement = m_replaceEdit.text().trimmed();

    if (!target.isEmpty() && !replacement.isEmpty() && !m_plainTextEdit.isNull()) {
        QTextDocument* doc = m_plainTextEdit->document();

        QString newText = doc->toPlainText()
                              .replace(target, replacement, m_checkBox.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

        doc->setPlainText(newText);
        m_plainTextEdit->viewport()->update();
    }
}
