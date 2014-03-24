#ifndef WIDGETSFACTORY_H
#define WIDGETSFACTORY_H

#include <QWidget>

class WidgetsFactory
{
public:
    static WidgetsFactory *getInstance();
    QWidget *getWidget(const QString &type);

private:
    WidgetsFactory();
    static WidgetsFactory *instance;
};

WidgetsFactory *WidgetsFactory::instance = NULL;

#endif // WIDGETSFACTORY_H
