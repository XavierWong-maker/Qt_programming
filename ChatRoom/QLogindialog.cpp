#include "QLogindialog.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QRandomGenerator>
#include <QPainter>
#include <QTime>

QLoginDialog::QLoginDialog(QWidget *parent) : QDialog(parent, Qt::WindowCloseButtonHint),
    UserLabel(this), PwdLabel(this), CaptLabel(this), CaptDisplay(this),
    UserEdit(this), PwdEdit(this), CaptEdit(this),
    LoginBtn(this), CancelBtn(this), m_timer(this) {

    QGridLayout* layout = new QGridLayout(this);

    UserLabel.setText("User Name:");
    UserEdit.setMinimumWidth(180);
    layout->addWidget(&UserLabel, 0, 0);
    layout->addWidget(&UserEdit, 0, 1);

    PwdLabel.setText("Password:");
    PwdEdit.setMinimumWidth(180);
    PwdEdit.setEchoMode(QLineEdit::Password);
    layout->addWidget(&PwdLabel, 1, 0);
    layout->addWidget(&PwdEdit, 1, 1);

    CaptLabel.setText("Captcha:");
    CaptEdit.setMinimumWidth(70);
    CaptDisplay.setMinimumSize(69, 24);
    layout->addWidget(&CaptLabel, 2, 0);
    layout->addWidget(&CaptEdit, 2, 1);
    layout->addWidget(&CaptDisplay, 2, 2);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    CancelBtn.setText("Cancel");
    LoginBtn.setText("Login");
    btnLayout->addWidget(&CancelBtn);
    btnLayout->addWidget(&LoginBtn);
    btnLayout->setSpacing(10);
    layout->addLayout(btnLayout, 3, 0, 1, 3);

    setWindowTitle("Login");
    setFixedSize(270, 205);

    connect(&m_timer, &QTimer::timeout, this, &QLoginDialog::Timer_Timeout);
    connect(&LoginBtn, &QPushButton::clicked, this, &QLoginDialog::LoginBtn_Clicked);
    connect(&CancelBtn, &QPushButton::clicked, this, &QLoginDialog::CancelBtn_Clicked);

    m_captcha = getCaptcha();
    m_colors = getColors();

    m_timer.start(500);
}

void QLoginDialog::LoginBtn_Clicked(){

    QString captcha = CaptEdit.text().replace(" ", "");

    if(m_captcha.toLower() == captcha.toLower()){
        m_user = UserEdit.text().trimmed();
        m_pwd = PwdEdit.text();
        if(!(m_user.isEmpty() || m_pwd.isEmpty())){
            done(Accepted);
        }else {
            QMessageBox::information(this, "Info", "User or PassWord can't empty!");
        }

    }else{
        QMessageBox::critical(this, "Error", "The captcha is NOT matched!");
        m_captcha = getCaptcha();
        generateNoisePoints(CaptDisplay.geometry());
        CaptEdit.selectAll();
        update();
    }
}

void QLoginDialog::CancelBtn_Clicked(){
    m_user = UserEdit.text().trimmed();
    done(Rejected);
}

void QLoginDialog::Timer_Timeout(){
    m_colors = getColors();
    update();
}

void QLoginDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QRect captchaRect = CaptDisplay.geometry();
    painter.fillRect(captchaRect, Qt::white);
    painter.setFont(QFont("Comic Sans MS", 12));

    for(int c = 0; c < 4; ++c){
        painter.setPen(m_colors[c]);
        for(int v = c; v < NOISE_COUNT; v += 4){
            painter.drawPoint(m_noisePoints[v]);
        }
    }

    int charWidth = captchaRect.width() / 4;
    for (int i = 0; i < 4; ++i) {
        painter.setPen(m_colors[i]);
        painter.drawText(captchaRect.x() + charWidth * i, captchaRect.y(), charWidth, captchaRect.height(),
                         Qt::AlignCenter, QString(m_captcha[i]));
    }
}

void QLoginDialog::showEvent(QShowEvent*) {
    m_captcha = getCaptcha();
    generateNoisePoints(CaptDisplay.geometry());
    PwdEdit.clear();
    CaptEdit.clear();
    update();
}

QString QLoginDialog::getCaptcha(){
    QString captcha;
    for(int i {0}; i < 4; ++i){
        int c = (QRandomGenerator::global()->bounded(2)) ? 'a' : 'A';
        captcha += QChar(c + QRandomGenerator::global()->bounded(26));
    }
    return captcha;
}

Qt::GlobalColor* QLoginDialog::getColors(){
    static Qt::GlobalColor colors[4];
    for (int i = 0; i < 4; ++i) {
        colors[i] = static_cast<Qt::GlobalColor>(2 + QRandomGenerator::global()->bounded(16));
    }
    return colors;
}

void QLoginDialog::generateNoisePoints(const QRect& rect){
    m_noisePoints.resize(NOISE_COUNT);
    for (int i = 0; i < NOISE_COUNT; ++i) {
        int x = rect.x() + QRandomGenerator::global()->bounded(rect.width());
        int y = rect.y() + QRandomGenerator::global()->bounded(rect.height());
        m_noisePoints[i] = QPoint(x, y);
    }
}

QLoginDialog::~QLoginDialog(){}

