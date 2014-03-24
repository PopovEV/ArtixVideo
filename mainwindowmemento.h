#ifndef MAINWINDOWMEMENTO_H
#define MAINWINDOWMEMENTO_H

#include "QString"

class MainWindow;

class MainWindowMemento
{
public:
    MainWindowMemento(MainWindow *main);

    void saveState();
    void loadState();

private:
    QString fileName;
    MainWindow *mainWindow;
};

#endif // MAINWINDOWMEMENTO_H
