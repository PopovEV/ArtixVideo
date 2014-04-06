#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QtSql>
#include <QTableView>

class SQL : public QObject
{
    Q_OBJECT
public:
    explicit SQL(QObject *parent = 0);

    bool createConnection();

    QSqlQueryModel *queryExec();
    bool sqlPrepare(const QString &query);
    void setQueryValue(const QString &param_name, const QString &value);
    QSqlQueryModel *getSqlModel();
    
private:
    QSqlDatabase db;
    QSqlQueryModel *sqlmodel;
    QSqlQuery sqlquery;

signals:
    
public slots:
    
};

#endif // SQL_H
