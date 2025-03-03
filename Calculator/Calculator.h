#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "QCalculatorUI.h"
#include "QCalculatorDec.h"

class Calculator
{
protected:
    QCalculatorUI* m_ui;
    QCalculatorDec m_cal;

    Calculator();
    bool construct();

public:
    static Calculator* newInstance();
    void show();
    ~Calculator();
};

#endif // CALCULATOR_H
