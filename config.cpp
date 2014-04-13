#include "config.h"

#include <QCoreApplication>
#include <QDebug>

Config *Config::instance = NULL;

Config::Config()
{
    qDebug() << QCoreApplication::applicationDirPath();
    settings = new QSettings(QCoreApplication::applicationDirPath() + "/" + "options.conf", QSettings::IniFormat);
}

Config *Config::getInstance()
{
    if(!instance) {
        instance = new Config();
    }

    return instance;
}

QVariant Config::getOption(QString key, QVariant defaultValue, QString section)
{
    QVariant value = settings->value(section + "/" + key, defaultValue);
    return value;
}

void Config::setOption(QString key, QVariant value, QString section)
{
    settings->setValue(section + "/" + key, value);
    // Принудительно сохраним данные на диск
    settings->sync();
}
