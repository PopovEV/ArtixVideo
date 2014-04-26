#ifndef WIDGETSFACTORY_H
#define WIDGETSFACTORY_H

#include <QWidget>

class WidgetsFactory
{
public:
    static WidgetsFactory *getInstance();
    QWidget *getWidget(const QString &type, const QString &defaultValue);

private:
    WidgetsFactory();
    static WidgetsFactory *instance;
};

#endif // WIDGETSFACTORY_H
