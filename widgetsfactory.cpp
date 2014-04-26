#include "widgetsfactory.h"

#include <QLineEdit>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QMessageBox>

#include "longintvalidator.h"
#include "currencyvalidator.h"

WidgetsFactory *WidgetsFactory::instance = NULL;

WidgetsFactory *WidgetsFactory::getInstance()
{
    if (instance == NULL)
        instance = new WidgetsFactory();

    return instance;
}

QWidget *WidgetsFactory::getWidget(const QString &type, const QString &defaultValue)
{
    QString typeUpper = type.toUpper();
    if(typeUpper == "INT")
    {
        LongIntValidator *pLongIntValidator = new LongIntValidator();

        QLineEdit *pLineEdit = new QLineEdit();
        pLineEdit->setValidator(pLongIntValidator);
        pLineEdit->setText(defaultValue);

        return pLineEdit;
    }
    else
        if(typeUpper == "CHAR")
        {
            QLineEdit *pLineEdit = new QLineEdit();
            pLineEdit->setText(defaultValue);

            return pLineEdit;
        }
        else
            if(typeUpper == "CURRENCY")
            {
                CurrencyValidator *pCurrencyValidator = new CurrencyValidator();

                QLineEdit *pLineEdit = new QLineEdit();
                pLineEdit->setValidator(pCurrencyValidator);
                pLineEdit->setText(defaultValue);

                return pLineEdit;
            }
            else
                if(typeUpper == "DATE")
                {
                    QDateEdit *pDateEdit = new QDateEdit(QDate::currentDate());
                    pDateEdit->setCalendarPopup(true);
                    pDateEdit->setDate(QDate().fromString(defaultValue, "yyyy-MM-dd"));

                    return pDateEdit;
                }
                else
                    if(typeUpper == "DATETIME")
                    {
                        QDateTimeEdit *pDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());
                        pDateTimeEdit->setCalendarPopup(true);
                        pDateTimeEdit->setDateTime(QDateTime().fromString(defaultValue, "yyyy-MM-dd hh:mm:ss"));

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
