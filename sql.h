#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QtSql>

#include "mainwindow.h"

class SQL : public QObject
{
    Q_OBJECT
public:
    explicit SQL(QObject *parent = 0);

    bool createConnection();

    bool QueryExec(QTableView *pTableView, const QString& query);
    
private:
    QSqlDatabase db;
    QSqlQueryModel *sqlmodel;

signals:
    
public slots:
    
};

#endif // SQL_H
