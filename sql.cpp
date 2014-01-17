#include <QtSql>
#include <QMessageBox>
#include <QTableView>

#include "sql.h"

SQL::SQL(QObject *parent) :
    QObject(parent)
{

}

bool SQL::createConnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL", "mydb");
    db.setDatabaseName("artixvideo");

    db.setUserName("root");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setPassword("12345");

    if(!db.open())
    {
        QMessageBox::critical(0, tr("Не удается открыть базу данных"),
                            db.lastError().text(), QMessageBox::Cancel);
        return false;
    }

    return true;
}

QSqlQueryModel * SQL::QueryExec()
{
    sqlmodel = new QSqlQueryModel();

    sqlquery.exec();
    sqlmodel->setQuery(sqlquery);

    if(sqlmodel->lastError().isValid())
    {
        qDebug() << sqlmodel->lastError();
        return 0;
    }

    return sqlmodel;
}

void SQL::SqlPrepare(const QString &query)
{
    sqlquery = QSqlQuery(db);
    qDebug() << sqlquery.prepare(query);
}

void SQL::setQueryValue(const QString &param_name, const QString &value)
{
    sqlquery.bindValue(param_name, value);
}

QSqlQueryModel *SQL::getSqlModel()
{
    return sqlmodel;
}
