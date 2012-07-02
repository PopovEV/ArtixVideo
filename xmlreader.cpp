#include <QMessageBox>
#include <stdio.h>

#include "xmlreader.h"


XMLReader::XMLReader()
{
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
                    qDebug() << "Query: " << domElement.attribute("name", "");
                }
                else
                    if(domElement.tagName() == "value")
                    {
                        qDebug() << "value: " << domElement.attribute("select", "");
                        //qDebug() << "select: " << domElement.text();
                    }
                    else
                        if(domElement.tagName() == "parameter")
                        {
                            qDebug() << "parameter: ";
                            qDebug() << "value " << domElement.attribute("value", "");
                            qDebug() << "name: " << domElement.attribute("name", "");
                            qDebug() << "type: " << domElement.attribute("type", "");
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
