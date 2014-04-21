#include <QtSql>
#include <QMessageBox>
#include <QTableView>

#include "sql.h"
#include <config.h>

SQL *SQL::instance = NULL;

SQL::SQL(QObject *parent) :
    QObject(parent)
{

}

SQL *SQL::getInstance()
{
    if(!instance)
        instance = new SQL();
    return instance;
}

QSqlDatabase SQL::getArtixVideo()
{
    if(!dbArtixVideo.isOpen() || !dbArtixVideo.isValid()) {
        Config *config = Config::getInstance();
        QString hostName = config->getOption("HostName", "localhost", "Database").toString();
        int port = config->getOption("Port", 3306, "Database").toInt();
        QString user = config->getOption("User", "root", "Database").toString();
        QString password = config->getOption("Password", "root", "Database").toString();

        instance->openConnection(dbArtixVideo, "QMYSQL", "dbArtixVideo", "artixvideo",
                                 user, hostName, port, password);
    }
    return dbArtixVideo;
}

QSqlDatabase SQL::getLocalDB()
{
    if(!dbLocal.isOpen() || !dbLocal.isValid()){
        instance->openConnection(dbLocal, "QSQLITE", "dbLocal", "local.db");
        createTables();
    }
    return dbLocal;
}

bool SQL::openConnection(QSqlDatabase &db, QString type, QString connectionName, QString dbName, QString userName,
                         QString hostName, int port, QString password)
{
    db = QSqlDatabase::addDatabase(type, connectionName);
    db.setDatabaseName(dbName);

    if(type == "QMYSQL") {
        db.setUserName(userName);
        db.setHostName(hostName);
        db.setPort(port);
        db.setPassword(password);
    }

    if(!db.open())
    {
        QMessageBox::critical(0, tr("Не удается открыть базу данных"),
                              db.lastError().text(), QMessageBox::Cancel);
        return false;
    }

    return true;
}

void SQL::createTables()
{
    QSqlQuery query(dbLocal);
    QString queryStr("CREATE TABLE IF NOT EXISTS Connection"
                     "("
                     "idConnection INTEGER NOT NULL CONSTRAINT Key1 PRIMARY KEY AUTOINCREMENT,"
                     "dbUserName TEXT,"
                     "dbHostName TEXT,"
                     "dbPort TEXT,"
                     "dbPassword TEXT,"
                     "WebAddress TEXT,"
                     "CONSTRAINT idConnection_constr UNIQUE (idConnection)"
                     ");");
    query.exec(queryStr);
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
    sqlquery = QSqlQuery(getArtixVideo());
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
