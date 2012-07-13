#ifndef CYRRENCYVALIDATOR_H
#define CYRRENCYVALIDATOR_H

#include <QValidator>

class CurrencyValidator : public QValidator
{
    Q_OBJECT
public:
    explicit CurrencyValidator(QObject *parent = 0);

    virtual State validate(QString & str, int & pos) const;
    
signals:
    
public slots:
    
};

#endif // CYRRENCYVALIDATOR_H
