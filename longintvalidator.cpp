#include "longintvalidator.h"

LongIntValidator::LongIntValidator(QObject *parent) :
    QValidator(parent)
{
}

QValidator::State LongIntValidator::validate(QString &str, int &pos) const
{
    QRegExp rxp = QRegExp("\\D");

    if(str.contains(rxp))
    {
        return Invalid;
    }

    return Acceptable;

}
