#include "xmlreader.h"

#include <QMessageBox>

XMLReader::XMLReader(QObject *parent) :
    QObject(parent)
{
    countQuery = 0;
}

bool XMLReader::checkFile(const QString &fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QString errorStr;
        int errorLine;
        int errorColumn;

        if (!domDoc.setContent(&file, true, &errorStr, &errorLine, &errorColumn))
        {
            QMessageBox::information(0,
                                     QObject::tr("Чтение запросов"),
                                     QObject::tr("Синтаксическая ошибка в строке %1, столбец %2:\n%3")
                                     .arg(errorLine)
                                     .arg(errorColumn)
                                     .arg(errorStr));
            return false;
        }
        file.close();
        return true;
    }
    else
    {
        QMessageBox::information(new QWidget(),QObject::tr("Открытие файла"),
                                 QObject::tr("Не удалось открыть файл!"));
    }
    return false;
}

QList<Query> *XMLReader::getQueries()
{
    QList<Query> *queryList = new QList<Query>();
    if(!domDoc.isNull()) {
        QDomElement domElement = domDoc.documentElement();
        traverseNode(domElement, queryList);
    }
    return queryList;
}

void XMLReader::traverseNode(const QDomNode &node, QList<Query> *queryList)
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
                    Query newQuery;
                    newQuery.id = countQuery++;
                    newQuery.num = domElement.attribute("num", "").toInt();
                    newQuery.name = domElement.attribute("name", "");
                    newQuery.child = domElement.attribute("child", "").toInt();
                    if(domElement.attribute("ischild", "").toUpper() == "TRUE")
                        newQuery.ischild = true;
                    else
                        newQuery.ischild = false;
                    newQuery.tabName = domElement.attribute("TabName", "");

                    queryList->push_back(newQuery);
                }
                else
                    if(domElement.tagName() == "description")
                    {
                        queryList->back().description = domElement.text().simplified();
                    }
                    else
                        if(domElement.tagName() == "SQL")
                        {
                            queryList->back().sql = domElement.text().simplified();
                        }
                        else
                            if(domElement.tagName() == "parameter")
                            {
                                Parameter newParameter;
                                newParameter.value = ":" + domElement.attribute("value", "") ;
                                newParameter.name = domElement.attribute("name", "");
                                newParameter.type = domElement.attribute("type", "");

                                queryList->back().ParameterList.push_back(newParameter);
                            }
            }
        }
        traverseNode(domNode, queryList);
        domNode = domNode.nextSibling();
    }
}

void XMLReader::printQueryList(QList<Query> *queryList)
{
    for(int i = 0; i < queryList->count(); ++i)
    {
        qDebug() << queryList->at(i).num ;
        qDebug() << queryList->at(i).child ;
        qDebug() << queryList->at(i).ischild ;
        qDebug() << queryList->at(i).sql ;
        for(int j = 0; j < queryList->at(i).ParameterList.count(); ++j)
        {
            qDebug() << queryList->at(i).ParameterList.at(j).value ;
            qDebug() << queryList->at(i).ParameterList.at(j).type;
        }
    }
}
