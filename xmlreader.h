#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>
#include <QtXml>

#include "global.h"

class XMLReader : public QObject
{
    Q_OBJECT
public:
    explicit XMLReader(QObject *parent = 0);

    bool checkFile(const QString& fileName);
    QList<Query> *getQueries();
    void traverseNode(const QDomNode& node, QList<Query> *queryList);

private:
    QDomDocument domDoc;
    int countQuery;

    void printQueryList(QList<Query> *queryList);

signals:

public slots:
    
};

#endif // XMLREADER_H
