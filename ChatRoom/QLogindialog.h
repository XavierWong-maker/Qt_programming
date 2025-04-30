#ifndef _QLOGINDIALOG_H_
#define _QLOGINDIALOG_H_

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QVector>
#include <QPoint>

class QLoginDialog : public QDialog
{
    Q_OBJECT

    QLabel UserLabel, PwdLabel, CaptLabel, CaptDisplay;
    QLineEdit UserEdit, PwdEdit, CaptEdit;
    QPushButton LoginBtn, CancelBtn;
    QTimer m_timer;

    QString m_user, m_pwd, m_captcha;
    Qt::GlobalColor* m_colors;
    QVector<QPoint> m_noisePoints;
    static constexpr int NOISE_COUNT = 150;

    QString getCaptcha();
    Qt::GlobalColor* getColors();
    void generateNoisePoints(const QRect& rect);
    void paintEvent(QPaintEvent*) override;
    void showEvent(QShowEvent*) override;

private slots:
    void LoginBtn_Clicked();
    void CancelBtn_Clicked();
    void Timer_Timeout();

public:
    QLoginDialog(QWidget* parent = nullptr);
    QString getUser() const { return m_user; }
    QString getPwd() const { return m_pwd; }
    ~QLoginDialog();
};

#endif // QLOGINDIALOG_H
