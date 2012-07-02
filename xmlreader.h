#ifndef XMLREADER_H
#define XMLREADER_H

#include <QtXml>

class XMLReader
{
private:
    QDomDocument domDoc;

public:
    XMLReader();

    void ReadFile(const QString& FileName);
    void traverseNode(const QDomNode& node);
};

#endif // XMLREADER_H
