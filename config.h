#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

class Config
{
public:
    static Config *getInstance();

    QVariant getOption(QString key, QVariant defaultValue = QVariant(), QString section = "main");
    void setOption(QString key, QVariant value, QString section = "main");

private:
    Config();

    static Config *instance;
    QSettings *settings;

};

#endif // CONFIG_H
