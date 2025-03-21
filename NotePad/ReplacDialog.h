#ifndef REPLACDIALOG_H
#define REPLACDIALOG_H

#include "FindDialog.h"

class ReplacDialog : public FindDialog
{
    Q_OBJECT

    QPushButton m_replaceButton;
    QPushButton m_replaceAllButton;
    QLabel m_replaceAsLabel;
    QLineEdit m_replaceEdit;

    void initControl();
    void connectSlot();

protected slots:
    void onReplaceButtonClicked();
    void onReplaceAllButtonClicked();

public:
    explicit ReplacDialog(QWidget* parent = nullptr, QPlainTextEdit* pText = nullptr);
};

#endif // REPLACDIALOG_H
