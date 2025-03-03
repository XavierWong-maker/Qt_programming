#ifndef _QCALCULATORDEC_H_
#define _QCALCULATORDEC_H_

#include "ICalculator.h"
#include <QString>
#include <QStack>
#include <QQueue>

class QCalculatorDec:public ICalculator
{
protected:
    QString m_exp;
    QString m_result;

    bool isDigitOrDot(QChar c);
    bool isSymbol(QChar c);
    bool isSign(QChar c);
    bool isNumber(QString s);
    bool isOperator(QString s);
    bool isLeft(QString s);
    bool isRight(QString s);
    int priority(QString s);
    QQueue<QString> split(const QString& exp);
    bool match(QQueue<QString>& exp);
    bool transform(QQueue<QString>& exp, QQueue<QString>& output);
    QString calculate(QString l, QString op, QString r);
    QString calculate(QQueue<QString>& exp);

public:
    QCalculatorDec();
    ~QCalculatorDec();
    bool expression(const QString& exp);
    QString expression();
    QString result();
};

#endif // QCALCULATORDEC_H
