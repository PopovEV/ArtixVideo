#include <QtSql>
#include <QMessageBox>
#include <QTableView>

#include "sql.h"
#include "mainwindow.h"



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

    sqlmodel = new QSqlQueryModel();

    return true;
}

bool SQL::QueryExec(QTableView *pTableView, const QString &query)
{
    sqlmodel->setQuery(query, db);

    if(sqlmodel->lastError().isValid())
    {
        qDebug()<< sqlmodel->lastError();
        return false;
    }

    pTableView->setModel(sqlmodel);

    return true;
}
