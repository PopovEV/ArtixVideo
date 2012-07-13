#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QDateTimeEdit>

#include <stdio.h>

#include "xmlreader.h"
#include "longintvalidator.h"
#include "currencyvalidator.h"

XMLReader::XMLReader(QObject *parent) :
    QObject(parent)
{
        countQuery = 0;
}

void XMLReader::ReadFile(const QString &FileName)
{
    QFile file(FileName);

    if(file.open(QIODevice::ReadOnly))
    {
        QString errorStr;
        int errorLine;
        int errorColumn;

        if (!domDoc.setContent(&file, true, &errorStr, &errorLine, &errorColumn))
        {
            QMessageBox::information(new QWidget(),QObject::tr("Чтение запросов"),
                                                            QObject::tr("Синтаксическая ошибка в строке %1, столбец %2:\n%3")
                                                            .arg(errorLine)
                                                            .arg(errorColumn)
                                                            .arg(errorStr));
            return ;
        }
        else
        {
            QDomElement domElement = domDoc.documentElement();
            traverseNode(domElement);
        }
        file.close();
    }
    else
    {
        QMessageBox::information(new QWidget(),QObject::tr("Открытие файла"), QObject::tr("Не удается открыть файл!"));
    }
}

void XMLReader::traverseNode(const QDomNode &node)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull())
            {
                if(domElement.tagName() == "Query")
                {
                    countQuery++;

                    pNewItemFrame = emit addItem(domElement.attribute("name", "").toUtf8().data());

                    qDebug() << "Query:"
                    << "\nname: " << domElement.attribute("name", "")
                    << "\nchild: " << domElement.attribute("child", "")
                    << "\nischild: " << domElement.attribute("ischild", "");
                }
                else
                    if(domElement.tagName() == "SQL")
                    {
                        qDebug() << "select: " << domElement.text();
                    }
                    else
                        if(domElement.tagName() == "parameter")
                        {

                            pNewItemFrame->addRow(domElement.attribute("name", ""), createInputBox(&domElement.attribute("type", "")));

                            qDebug() << "parameter: "
                            << "\nvalue " << domElement.attribute("value", "")
                            << "\nname: " << domElement.attribute("name", "")
                            << "\ntype: " << domElement.attribute("type", "");
                        }
                        else
                        {
                            qDebug() << "TagName: " << domElement.tagName() << "\tText: " << domElement.text();
                        }
            }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }
}

QWidget *XMLReader::createInputBox(const QString *type)
{
    if(type->toUpper() == "INT")
    {
        LongIntValidator *pLongIntValidator = new LongIntValidator();

        QLineEdit *pLineEdit = new QLineEdit();
        pLineEdit->setValidator(pLongIntValidator);

        return pLineEdit;
    }
    else
        if(type->toUpper() == "CHAR")
        {
            QLineEdit *pLineEdit = new QLineEdit();

            return pLineEdit;
        }
        else
            if(type->toUpper() == "CURRENCY")
            {
//                QDoubleValidator *pDoubleValidator = new QDoubleValidator();
//                pDoubleValidator->setDecimals(2);
//                pDoubleValidator->setNotation(QDoubleValidator::StandardNotation);
                CurrencyValidator *pCurrencyValidator = new CurrencyValidator();

                QLineEdit *pLineEdit = new QLineEdit();
                pLineEdit->setValidator(pCurrencyValidator);

                return pLineEdit;
            }
            else
                if(type->toUpper() == "DATE")
                {
                    QDateEdit *pDateEdit = new QDateEdit(QDate::currentDate());

                    return pDateEdit;
                }
                else
                    if(type->toUpper() == "DATETIME")
                    {
                        QDateTimeEdit *pDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());

                        return pDateTimeEdit;
                    }
                    else
                        return 0;

}


qint32 XMLReader::getCountQuery()
{
    return countQuery;
}
