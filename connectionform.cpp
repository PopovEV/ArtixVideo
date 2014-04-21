#include "connectionform.h"
#include "ui_connectionform.h"
#include "sql.h"
#include "config.h"

#include <QMessageBox>


ConnectionForm::ConnectionForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionForm)
{
    ui->setupUi(this);
    sqlModel = new QSqlQueryModel();

    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedRow(QModelIndex)));
    connect(ui->pushButton_Add, SIGNAL(clicked()), this, SLOT(addConnection()));
    connect(ui->pushButton_Delete, SIGNAL(clicked()), this, SLOT(deleteConnection()));

    loadConnectionsFromDB();
}

ConnectionForm::~ConnectionForm()
{
    delete ui;
    if (sqlModel)
        delete sqlModel;
}

void ConnectionForm::accept()
{
    if (!checkFields())
        return;

    Config *config = Config::getInstance();
    config->setOption("HostName", ui->lineEdit_dbAddress->text(), "Database");
    config->setOption("Port", ui->spinBox_dbPort->value(), "Database");
    config->setOption("User", ui->lineEdit_dbUser->text(), "Database");
    config->setOption("Password", ui->lineEdit_dbPassword->text(), "Database");

    config->setOption("WebAddress", ui->lineEdit_webAddress->text(), "VideoArchive");

    done(QDialog::Accepted);
}

void ConnectionForm::clickedRow(QModelIndex index)
{
    int row = index.row();

    ui->lineEdit_dbUser->setText(sqlModel->data(sqlModel->index(row, 1)).toString());
    ui->lineEdit_dbAddress->setText(sqlModel->data(sqlModel->index(row, 2)).toString());
    ui->spinBox_dbPort->setValue(sqlModel->data(sqlModel->index(row, 3)).toInt());
    ui->lineEdit_dbPassword->setText(sqlModel->data(sqlModel->index(row, 4)).toString());
    ui->lineEdit_webAddress->setText(sqlModel->data(sqlModel->index(row, 5)).toString());
}

void ConnectionForm::addConnection()
{
    if (!checkFields())
        return;

    QSqlDatabase db = SQL::getInstance()->getLocalDB();

    QSqlQuery query(db);
    QString queryStr = QString("INSERT INTO Connection (dbUserName, dbHostName, dbPort, dbPassword, WebAddress) "
                               "VALUES ('%1', '%2', '%3', '%4', '%5')")
            .arg(ui->lineEdit_dbUser->text())
            .arg(ui->lineEdit_dbAddress->text())
            .arg(ui->spinBox_dbPort->value())
            .arg(ui->lineEdit_dbPassword->text())
            .arg(ui->lineEdit_webAddress->text());
    if (!query.exec(queryStr)) {
        QMessageBox::information(0, "Сохранение подключения", "Не удается сохранить настройки подключения.\n" +
                                 query.lastError().text());
        return;
    }

    loadConnectionsFromDB();
}

void ConnectionForm::deleteConnection()
{
    int row = ui->tableView->currentIndex().row();
    if(row == -1)
        return;

    int idConnection = sqlModel->data(sqlModel->index(row, 0)).toInt();

    QSqlDatabase db = SQL::getInstance()->getLocalDB();
    QSqlQuery query(db);
    QString queryStr = QString("DELETE FROM Connection WHERE idConnection = %1").arg(idConnection);
    if (!query.exec(queryStr)) {
        QMessageBox::information(0, "Удаление подключения", "Не удается удалить подключение.\n" +
                                 query.lastError().text());
        return;
    }

    loadConnectionsFromDB();
}

void ConnectionForm::loadConnectionsFromDB()
{
    QSqlDatabase db = SQL::getInstance()->getLocalDB();

    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM Connection")) {
        QMessageBox::information(0, "Загрузка соединений", "Не удается загрузить соединения.\n" +
                                 query.lastError().text());
        return;
    }

    sqlModel->clear();
    sqlModel->setQuery(query);
    sqlModel->setHeaderData(1, Qt::Horizontal, "Пользователь");
    sqlModel->setHeaderData(2, Qt::Horizontal, "Адрес");
    sqlModel->setHeaderData(3, Qt::Horizontal, "Порт");
    sqlModel->setHeaderData(5, Qt::Horizontal, "Адрес видеоархива");

    ui->tableView->setModel(sqlModel);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(4);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

bool ConnectionForm::checkFields()
{
    if (ui->lineEdit_dbAddress->text().isEmpty() || ui->lineEdit_dbPassword->text().isEmpty() ||
            ui->lineEdit_dbUser->text().isEmpty() || ui->lineEdit_webAddress->text().isEmpty()) {
        QMessageBox::information(0, "Подключение", "Все поля должны быть заполнены!");
        return false;
    }
    return true;
}


