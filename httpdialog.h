#ifndef HTTPDIALOG_H
#define HTTPDIALOG_H

#include <QDialog>

class QLineEdit;

class HttpDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit *pHostName;
    QLineEdit *pPortName;

public:
    explicit HttpDialog(QWidget *parent = 0);

    void setHostName(const QString& host);
    void setPortName(const QString& port);

    QString getHostName() const;
    QString getPortName() const;
    
signals:
    
public slots:
    
};

#endif // HTTPDIALOG_H
