#include "Dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent), ModalBtn(this), NormalBtn(this), MixedBtn(this)
{
    ModalBtn.setText("Modal Dialog");
    ModalBtn.move(20, 20);
    ModalBtn.resize(100, 30);

    NormalBtn.setText("Normal Dialog");
    NormalBtn.move(20, 70);
    NormalBtn.resize(100, 30);

    MixedBtn.setText("Mixed Dialog");
    MixedBtn.move(20, 120);
    MixedBtn.resize(100, 30);

    connect(&ModalBtn, &QPushButton::clicked, this, &Dialog::ModalBtn_Clicked);
    connect(&MixedBtn, &QPushButton::clicked, this, &Dialog::MixedBtn_Clicked);
    connect(&NormalBtn, &QPushButton::clicked, this, &Dialog::NormalBtn_Clicked);

    resize(140, 170);
}

void Dialog::ModalBtn_Clicked(){
    qDebug() << "ModalBtn_Clicked() Begin";

    QDialog dialog(this);
    dialog.exec();
    done(Accepted);
    qDebug() << "ModalBtn_Clicked() End";
}

void Dialog::NormalBtn_Clicked(){
    qDebug() << "NormalBtn_Clicked() Begin";

    QDialog* dialog = new QDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
    done(Rejected);
    qDebug() << "NormalBtn_Clicked() End";
}

void Dialog::MixedBtn_Clicked(){
    qDebug() << "MixedBtn_Clicked() Begin";

    QDialog* dialog = new QDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setModal(true);
    dialog->show();
    done(100);
    qDebug() << "MixedBtn_Clicked() End";
}

Dialog::~Dialog() {
    qDebug() << "~Dialog()";
}
