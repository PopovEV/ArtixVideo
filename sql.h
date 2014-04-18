#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QtSql>
#include <QTableView>

class SQL : public QObject
{
    Q_OBJECT
public:

    static SQL *getInstance();
    QSqlDatabase getConnection();

    QSqlQueryModel *queryExec();
    bool sqlPrepare(const QString &query);
    void setQueryValue(const QString &param_name, const QString &value);
    QSqlQueryModel *getSqlModel();
    
private:
    explicit SQL(QObject *parent = 0);
    bool openConnection();

    static SQL *instance;
    QSqlDatabase db;
    QSqlQueryModel *sqlmodel;
    QSqlQuery sqlquery;

signals:
    
public slots:
    
};

#endif // SQL_H
