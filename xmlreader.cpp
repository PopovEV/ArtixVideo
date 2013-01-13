#include <QMessageBox>

#include <stdio.h>

#include "xmlreader.h"

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
//            PrintQueryList();
        }
        file.close();
    }
    else
    {
        QMessageBox::information(new QWidget(),QObject::tr("Открытие файла"), QObject::tr("Не удалось открыть файл!"));
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
                    // проверяем, существует ли вкладка с таким именем
                    int index = emit isTabExist(tr(domElement.attribute("TabName", "").toUtf8().data()));
//                    qDebug() << domElement.attribute("TabName", "").toUtf8().data();
                    // если вкладки еще нет, создаем ее
                    if(index == -1)
                        index = emit addTab(tr(domElement.attribute("TabName", "").toUtf8().data()));

                    // добавляем название запроса в комбобокс в нужную нам категорию(index)
                    emit addQueryName(tr(domElement.attribute("name", "").toUtf8().data()), index, countQuery);

                    Query newQuery;
                    newQuery.num = domElement.attribute("num", "").toInt();
                    newQuery.child = domElement.attribute("child", "").toInt();
                    if(domElement.attribute("ischild", "").toUpper() == "TRUE")
                        newQuery.ischild = true;
                    else
                        newQuery.ischild = false;

                    QueryList.push_back(newQuery);

                    countQuery++;

                    //                    qDebug() << "Query:"
                    //                    << "\nname: " << domElement.attribute("name", "")
                    //                    << "\nchild: " << domElement.attribute("child", "")
                    //                    << "\nischild: " << domElement.attribute("ischild", "");
                }
                else
                    if(domElement.tagName() == "description")
                    {
                        QueryList.back().description = domElement.text();
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

//                                pNewItemFrame->addRow(domElement.attribute("name", ""), createInputBox(&domElement.attribute("type", "")));

                                Parameter newParameter;
                                newParameter.value = ":" + domElement.attribute("value", "") ;
                                newParameter.name = domElement.attribute("name", "");
                                newParameter.type = domElement.attribute("type", "");

                                QueryList.back().ParameterList.push_back(newParameter);

                                //                            qDebug() << "parameter: "
                                //                            << "\nvalue " << domElement.attribute("value", "")
                                //                            << "\nname: " << domElement.attribute("name", "")
                                //                            << "\ntype: " << domElement.attribute("type", "");
                            }
                            else
                            {
//                                QMessageBox::information(0, tr("Ошибка!"), tr("Во время чтения файла запросов встречен неизвестный тег: %1  ").arg(domElement.tagName()));
                            }
            }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }
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
