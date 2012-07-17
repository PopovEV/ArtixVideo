#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>
#include <QtXml>
#include <QFormLayout>

struct Parameter{
    QString value;
    QString type;
};

struct Query{
    int num;
    int child;
    bool ischild;
    QString sql;
    QList<Parameter> ParameterList;
};

class XMLReader : public QObject
{
    Q_OBJECT
public:
    explicit XMLReader(QObject *parent = 0);

    void ReadFile(const QString& FileName);
    void traverseNode(const QDomNode& node);
    QWidget * createInputBox(const QString *type);
    qint32 getCountQuery();

    Query getQuery(qint32 index);

private:
    QDomDocument domDoc;
    qint32 countQuery;
    QFormLayout *pNewItemFrame;

    QList<Query> QueryList;

    void PrintQueryList();

signals:
    QFormLayout* addItem(const char *);

public slots:
    
};

#endif // XMLREADER_H
