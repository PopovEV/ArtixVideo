#include "widgetsfactory.h"

#include <QLineEdit>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QMessageBox>

#include "longintvalidator.h"
#include "currencyvalidator.h"


WidgetsFactory *WidgetsFactory::getInstance()
{
    if (instance == NULL)
        instance = new WidgetsFactory();

    return instance;
}

QWidget *WidgetsFactory::getWidget(const QString &type)
{
    QString typeUpper = type.toUpper();
    if(typeUpper == "INT")
    {
        LongIntValidator *pLongIntValidator = new LongIntValidator();

        QLineEdit *pLineEdit = new QLineEdit();
        pLineEdit->setValidator(pLongIntValidator);

        return pLineEdit;
    }
    else
        if(typeUpper == "CHAR")
        {
            QLineEdit *pLineEdit = new QLineEdit();

            return pLineEdit;
        }
        else
            if(typeUpper == "CURRENCY")
            {
                CurrencyValidator *pCurrencyValidator = new CurrencyValidator();

                QLineEdit *pLineEdit = new QLineEdit();
                pLineEdit->setValidator(pCurrencyValidator);

                return pLineEdit;
            }
            else
                if(typeUpper == "DATE")
                {
                    QDateEdit *pDateEdit = new QDateEdit(QDate::currentDate());
                    pDateEdit->setCalendarPopup(true);

                    return pDateEdit;
                }
                else
                    if(typeUpper == "DATETIME")
                    {
                        QDateTimeEdit *pDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());
                        pDateTimeEdit->setCalendarPopup(true);

                        return pDateTimeEdit;
                    }
                    else
                    {
                        QMessageBox::information(0, QObject::tr("Ошибка!"),
                                                 QObject::tr("Тип параметра задан неверно!"));
                        return NULL;
                    }
}

WidgetsFactory::WidgetsFactory()
{
}
