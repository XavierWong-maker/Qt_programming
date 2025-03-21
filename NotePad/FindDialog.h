#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QPointer>

class FindDialog : public QDialog
{
    Q_OBJECT

protected:
    QGridLayout m_gLayout;
    QGroupBox m_gBox;
    QHBoxLayout m_hLayout;
    QLabel m_findLabel;
    QLineEdit m_findLineEdit;
    QPushButton m_findButton;
    QCheckBox m_checkBox;
    QRadioButton m_forwardButton;
    QRadioButton m_backwardButton;
    QPushButton m_cancleButton;

    QPointer<QPlainTextEdit> m_plainTextEdit;
    void initControl();
    void connectSlot();

protected slots:
    void onFindButtonClicked();
    void onCancleButtonClicked();

public:
    explicit FindDialog(QWidget *parent = nullptr, QPlainTextEdit* pText = nullptr);
    void setPlainTextEdit(QPlainTextEdit* pText);
    QPlainTextEdit* getPlainTextEdit();
    bool event(QEvent* e);
};

#endif // FINDDIALOG_H
