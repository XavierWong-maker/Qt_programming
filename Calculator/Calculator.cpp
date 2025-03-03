#include "Calculator.h"

Calculator::Calculator() {}

bool Calculator::construct(){
    m_ui = QCalculatorUI::NewInstance();
    if(m_ui){
        m_ui->setCalculator(&m_cal);
    }
    return (m_ui);
}

Calculator* Calculator::newInstance(){
    Calculator* ret = new Calculator();
    if((nullptr == ret) || (!ret->construct())){
        delete ret;
        ret =  nullptr;
    }
    return ret;
}

void Calculator::show(){
    m_ui->show();
}

Calculator::~Calculator(){
    delete m_ui;
}

