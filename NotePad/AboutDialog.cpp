#include "AboutDialog.h"
#include <QPalette>

AboutDialog::AboutDialog(QWidget* parent) :
    QDialog(parent), m_label(this), m_closeButton(this), m_plainTextEdit(this){

    QPixmap pm(":/Res/pic/Logo.png");
    pm = pm.scaled(120, 120, Qt::KeepAspectRatio);

    m_label.setPixmap(pm);
    m_label.move(20, 20);
    m_label.resize(120, 120);

    QPalette p = m_plainTextEdit.palette();
    p.setColor(QPalette::Active, QPalette::Base, palette().color(QPalette::Active, QPalette::Window));
    p.setColor(QPalette::Inactive, QPalette::Base, palette().color(QPalette::Inactive, QPalette::Window));

    m_plainTextEdit.move(200, 30);
    m_plainTextEdit.resize(180, 130);
    m_plainTextEdit.setPalette(p);
    m_plainTextEdit.setFrameStyle(QFrame::NoFrame);
    m_plainTextEdit.setReadOnly(true);
    m_plainTextEdit.insertPlainText("NotePad Project\n\nPlatform: Qt " + QString(QT_VERSION_STR) +"\n\nVersion: 1.0.0\n\nCopyright: LGC");

    m_closeButton.setText("Close");
    m_closeButton.move(273, 175);
    m_closeButton.resize(100, 30);

    setFixedSize(390, 230);
    setWindowTitle("About NotePad");

    connect(&m_closeButton, &QPushButton::clicked, this, &QDialog::close);
}
