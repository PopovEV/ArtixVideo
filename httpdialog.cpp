#include "httpdialog.h"
#include <QtGui>

HttpDialog::HttpDialog(QWidget *parent) :
    QDialog(parent)
{
    pHostName = new QLineEdit();
    pPortName = new QLineEdit();

    QIntValidator *pPortValidator = new QIntValidator();
    pPortName->setValidator(pPortValidator);

    QLabel *pLblHostName = new QLabel(tr("&Хост"));
    QLabel *pLblPortName = new QLabel(tr("&Порт"));

    pLblHostName->setBuddy(pHostName);
    pLblPortName->setBuddy(pPortName);

    QPushButton *pOk = new QPushButton("&Ok");
    QPushButton *pCancel = new QPushButton("&Cancel");
    connect(pOk, SIGNAL(clicked()), SLOT(accept()));
    connect(pCancel, SIGNAL(clicked()), SLOT(reject()));

    QGridLayout *ptopLayout = new QGridLayout();
    ptopLayout->addWidget(pLblHostName, 0, 0);
    ptopLayout->addWidget(pHostName, 0, 1);
    ptopLayout->addWidget(pLblPortName, 1, 0);
    ptopLayout->addWidget(pPortName, 1, 1);
    ptopLayout->addWidget(pOk, 2, 0);
    ptopLayout->addWidget(pCancel, 2, 1);

    setLayout(ptopLayout);
}

void HttpDialog::setHostName(const QString &host)
{
    pHostName->setText(host);
}

void HttpDialog::setPortName(const QString &port)
{
    pPortName->setText(port);
}

QString HttpDialog::getHostName() const
{
    return pHostName->text();
}

QString HttpDialog::getPortName() const
{
    return pPortName->text();
}
