#include "QCalculatorUI.h"
#include <QDebug>

QCalculatorUI::QCalculatorUI(): QWidget(nullptr,Qt::WindowCloseButtonHint){
    m_cal = nullptr;
}

bool QCalculatorUI::construct(){
    bool ret = true;
    const char* btnText[20] =
    {
        "7", "8", "9", "+", "(",
        "4", "5", "6", "-", ")",
        "1", "2", "3", "*", "<-",
        "0", ".", "=", "/", "C",
    };

    m_edit = new QLineEdit(this);
    if(nullptr != m_edit){
        m_edit->move(10,10);
        m_edit->resize(240,30);
        m_edit->setReadOnly(true);
        m_edit->setAlignment(Qt::AlignRight);
    }else{
        ret = false;
    }


    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            m_buttons[i*5 + j] = new QPushButton(this);
            if(nullptr != m_buttons[i*5 + j]){
                m_buttons[i*5 + j]->resize(40,40);
                m_buttons[i*5 + j]->move(10 + (10 + 40) * j, 50 + (10 + 40) * i);
                m_buttons[i*5 + j]->setText(btnText[i*5+j]);
                QObject::connect(m_buttons[i*5 + j],&QPushButton::clicked,this,&QCalculatorUI::onButtonClicked);
            }else{
                ret = false;
            }
        }
    }
    return ret;
}


QCalculatorUI::~QCalculatorUI(){

}

QCalculatorUI* QCalculatorUI::NewInstance(){

    QCalculatorUI* ret = new QCalculatorUI();
    if((nullptr == ret) || !ret->construct()){
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void QCalculatorUI::show(){
    QWidget::show();
    setFixedSize(width(),height());
}

void QCalculatorUI::onButtonClicked(){
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(!btn){
        return;
    }

    const QString clickText = btn->text();
    QString currentText = m_edit->text();

    if("<-" == clickText){
        if(!currentText.isEmpty()){
            currentText.chop(1);
            m_edit->setText(currentText);
        }
    }else if("C" == clickText){
        m_edit->clear();
    }else if("=" == clickText){
        m_cal->expression(m_edit->text());
        m_edit->setText(m_cal->result());
    }else{
        m_edit->setText(currentText.append(clickText));
    }
}

void QCalculatorUI::setCalculator(ICalculator* cal){
    m_cal = cal;
}
ICalculator* QCalculatorUI::getCalculator(){
    return m_cal;
}

