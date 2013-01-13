#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>
#include <QtXml>
#include <QFormLayout>
#include <QFrame>

struct Parameter{
    QString value;
    QString name;
    QString type;
};

struct Query{
    int num;
    int child;
    bool ischild;
    QString description;
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
    void addQueryName(QString name, int indexTab, int numQueryInList);
    int addTab(QString nameTab);
    int isTabExist(QString nameTab); // если вкладка уже создана, возвращает номер вкладки, иначе -1

public slots:
    
};

#endif // XMLREADER_H
