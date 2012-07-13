#ifndef LONGINTVALIDATOR_H
#define LONGINTVALIDATOR_H

#include <QValidator>

class LongIntValidator : public QValidator
{
    Q_OBJECT
public:
    explicit LongIntValidator(QObject *parent = 0);

    virtual State validate(QString &str, int &pos) const;
    
signals:
    
public slots:
    
};

#endif // LONGINTVALIDATOR_H
