#include "settingsform.h"
#include "ui_settingsform.h"
#include "config.h"

SettingsForm::SettingsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    Config *config = Config::getInstance();

    ui->spinBox_LenghtVideo->setValue(config->getOption("LenghtVideo", 300).toInt());
    ui->lineEdit_DateFormat->setText(config->getOption("DirNameFormat", "yyyyMMdd").toString());
    ui->lineEdit_TimeFormat->setText(config->getOption("TimeFormat", "hhmmss").toString());
    ui->lineEdit_TimePattern->setText(config->getOption("TimePattern", "\\d{6,6}").toString());
    ui->lineEdit_FileNameSuffix->setText(config->getOption("FileNameSuffix", "-INJ.flv").toString());
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::accept()
{
    Config *config = Config::getInstance();

    config->setOption("LenghtVideo", ui->spinBox_LenghtVideo->value());
    config->setOption("DirNameFormat", ui->lineEdit_DateFormat->text());
    config->setOption("TimeFormat", ui->lineEdit_TimeFormat->text());
    config->setOption("TimePattern", ui->lineEdit_TimePattern->text());
    config->setOption("FileNameSuffix", ui->lineEdit_FileNameSuffix->text());

    done(QDialog::Accepted);
}
