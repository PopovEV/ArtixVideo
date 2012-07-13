#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>
#include <QtXml>
#include <QFormLayout>

class XMLReader : public QObject
{
    Q_OBJECT
public:
    explicit XMLReader(QObject *parent = 0);

    void ReadFile(const QString& FileName);
    void traverseNode(const QDomNode& node);
    QWidget * createInputBox(const QString *type);
    qint32 getCountQuery();

private:
    QDomDocument domDoc;
    qint32 countQuery;
    QFormLayout *pNewItemFrame;

signals:
    QFormLayout* addItem(const char *);

public slots:
    
};

#endif // XMLREADER_H
