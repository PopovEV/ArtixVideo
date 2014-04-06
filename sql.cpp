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
    db.setPassword("root");

    if(!db.open())
    {
        QMessageBox::critical(0, tr("Не удается открыть базу данных"),
                            db.lastError().text(), QMessageBox::Cancel);
        return false;
    }

    return true;
}

QSqlQueryModel *SQL::queryExec()
{
    sqlmodel = new QSqlQueryModel();

    if (!sqlquery.exec()) {
        QMessageBox::information(0, "Error in sql", sqlquery.lastError().text());
        return sqlmodel;
    }

    sqlmodel->setQuery(sqlquery);
    if(sqlmodel->lastError().isValid())
    {
        qDebug() << sqlmodel->lastError();
        return sqlmodel;
    }

    return sqlmodel;
}

bool SQL::sqlPrepare(const QString &query)
{
    sqlquery = QSqlQuery(db);
    return sqlquery.prepare(query);
}

void SQL::setQueryValue(const QString &param_name, const QString &value)
{
    sqlquery.bindValue(param_name, value);
}

QSqlQueryModel *SQL::getSqlModel()
{
    return sqlmodel;
}
