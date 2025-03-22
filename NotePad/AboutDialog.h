#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>

class AboutDialog : public QDialog
{
    Q_OBJECT
protected:
    QLabel m_label;
    QPushButton m_closeButton;
    QPlainTextEdit m_plainTextEdit;

public:
    explicit AboutDialog(QWidget* parent = nullptr);
};

#endif // ABOUTDIALOG_H
