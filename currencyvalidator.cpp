#include "currencyvalidator.h"

CurrencyValidator::CurrencyValidator(QObject *parent) :
    QValidator(parent)
{
}

QValidator::State CurrencyValidator::validate(QString &str, int &pos) const
{
    QRegExp rxp = QRegExp();

    rxp.setPattern("\\d*|\\d+\\.?\\d{,2}");

    if(rxp.exactMatch(str))
    {
        return Acceptable;
    }

    return Invalid;
}
