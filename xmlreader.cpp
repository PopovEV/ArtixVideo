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
            PrintQueryList();
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

                    Query newQuery;
                    newQuery.num = domElement.attribute("num", "").toInt();
                    newQuery.child = domElement.attribute("child", "").toInt();
                    if(domElement.attribute("ischild", "").toUpper() == "TRUE")
                        newQuery.ischild = true;
                    else
                        newQuery.ischild = false;


                    QueryList.push_back(newQuery);

//                    qDebug() << "Query:"
//                    << "\nname: " << domElement.attribute("name", "")
//                    << "\nchild: " << domElement.attribute("child", "")
//                    << "\nischild: " << domElement.attribute("ischild", "");
                }
                else
                    if(domElement.tagName() == "SQL")
                    {
                        QueryList.back().sql = domElement.text();
//                        qDebug() << "select: " << domElement.text();
                    }
                    else
                        if(domElement.tagName() == "parameter")
                        {

                            pNewItemFrame->addRow(domElement.attribute("name", ""), createInputBox(&domElement.attribute("type", "")));

                            Parameter newParameter;
                            newParameter.value = ":" + domElement.attribute("value", "") ;
                            newParameter.type = domElement.attribute("type", "");

                            QueryList.back().ParameterList.push_back(newParameter);

//                            qDebug() << "parameter: "
//                            << "\nvalue " << domElement.attribute("value", "")
//                            << "\nname: " << domElement.attribute("name", "")
//                            << "\ntype: " << domElement.attribute("type", "");
                        }
                        else
                        {
                            //qDebug() << "TagName: " << domElement.tagName() << "\tText: " << domElement.text();
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
                CurrencyValidator *pCurrencyValidator = new CurrencyValidator();

                QLineEdit *pLineEdit = new QLineEdit();
                pLineEdit->setValidator(pCurrencyValidator);

                return pLineEdit;
            }
            else
                if(type->toUpper() == "DATE")
                {
                    QDateEdit *pDateEdit = new QDateEdit(QDate::currentDate());
                    pDateEdit->setCalendarPopup(true);

                    return pDateEdit;
                }
                else
                    if(type->toUpper() == "DATETIME")
                    {
                        QDateTimeEdit *pDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());
                        pDateTimeEdit->setCalendarPopup(true);

                        return pDateTimeEdit;
                    }
                    else
                        return 0;

}


qint32 XMLReader::getCountQuery()
{
    return countQuery;
}

Query XMLReader::getQuery(qint32 index)
{
    return QueryList.value(index);
}

void XMLReader::PrintQueryList()
{
    for(int i = 0; i < QueryList.count(); ++i)
    {
        qDebug() << QueryList.at(i).num ;
        qDebug() << QueryList.at(i).child ;
        qDebug() << QueryList.at(i).ischild ;
        qDebug() << QueryList.at(i).sql ;
        for(int j = 0; j < QueryList.at(i).ParameterList.count(); ++j)
        {
            qDebug() << QueryList.at(i).ParameterList.at(j).value ;
            qDebug() << QueryList.at(i).ParameterList.at(j).type;
        }
    }
}
