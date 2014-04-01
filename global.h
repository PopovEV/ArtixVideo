#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QList>

struct Parameter{
    QString value;
    QString name;
    QString type;
};

struct Query{
    int id;
    int num;
    int child;
    bool ischild;
    QString name;
    QString description;
    QString sql;
    QString tabName;
    QList<Parameter> ParameterList;
};

#endif // GLOBAL_H
