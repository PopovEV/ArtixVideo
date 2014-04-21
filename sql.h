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
    QSqlDatabase getArtixVideo();
    QSqlDatabase getLocalDB();

    QSqlQueryModel *queryExec();
    bool sqlPrepare(const QString &query);
    void setQueryValue(const QString &param_name, const QString &value);
    QSqlQueryModel *getSqlModel();
    
private:
    explicit SQL(QObject *parent = 0);
    bool openConnection(QSqlDatabase &db, QString type, QString connectionName, QString dbName,
                        QString userName = QString(), QString hostName = QString(), int port = 0,
                        QString password = QString());
    void createTables();
    static SQL *instance;
    QSqlDatabase dbArtixVideo;
    QSqlDatabase dbLocal;
    QSqlQueryModel *sqlmodel;
    QSqlQuery sqlquery;

signals:
    
public slots:
    
};

#endif // SQL_H
