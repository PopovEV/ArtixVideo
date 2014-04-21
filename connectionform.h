#ifndef CONNECTIONFORM_H
#define CONNECTIONFORM_H

#include <QDialog>
#include <QModelIndex>

class QSqlQueryModel;

namespace Ui {
class ConnectionForm;
}

class ConnectionForm : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionForm(QWidget *parent = 0);
    ~ConnectionForm();

public slots:
    virtual void accept();
    void clickedRow(QModelIndex index);
    void addConnection();
    void deleteConnection();

private:
    Ui::ConnectionForm *ui;
    QSqlQueryModel *sqlModel;

    void loadConnectionsFromDB();
    bool checkFields();

};

#endif // CONNECTIONFORM_H
