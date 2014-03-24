#include "mainwindowmemento.h"

#include <QFile>
#include <QMessageBox>

#include "mainwindow.h"

MainWindowMemento::MainWindowMemento(MainWindow *main)
{
    this->mainWindow = main;
    fileName = "DockProperties.set";
}

void MainWindowMemento::saveState()
{
    if(!mainWindow)
         return;

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QString msg = QObject::tr("Не удается открыть файл настроек %1\n%2")
                .arg(fileName)
                .arg(file.errorString());
        QMessageBox::warning(0, QObject::tr("Ошибка восстановления параметров окна"), msg);
        return;
    }

    QByteArray geo_data = mainWindow->saveGeometry();
    QByteArray layout_data = mainWindow->saveState();

    bool ok = file.putChar((uchar)geo_data.size());
    if (ok)
        ok = file.write(geo_data) == geo_data.size();
    if (ok)
        ok = file.write(layout_data) == layout_data.size();

    if (!ok) {
        QString msg = QObject::tr("Ошибка записи настроек в %1\n%2")
                .arg(fileName)
                .arg(file.errorString());
        QMessageBox::warning(0, QObject::tr("Ошибка восстановления параметров окна"), msg);
        return;
    }
}

void MainWindowMemento::loadState()
{
    if(!mainWindow)
         return;

    QFile file(fileName);
    if (!file.exists()) {
        qDebug() << "Нет файла для восстановления настроек";
        return;
    }

    if (!file.open(QFile::ReadOnly)) {
        QString msg = QObject::tr("Не удается открыть файл настроек %1\n%2")
                .arg(fileName)
                .arg(file.errorString());
        QMessageBox::warning(0, QObject::tr("Ошибка восстановления параметров окна"), msg);
        return;
    }

    uchar geo_size;
    QByteArray geo_data;
    QByteArray layout_data;

    bool ok = file.getChar((char*)&geo_size);
    if (ok) {
        geo_data = file.read(geo_size);
        ok = geo_data.size() == geo_size;
    }
    if (ok) {
        layout_data = file.readAll();
        ok = layout_data.size() > 0;
    }

    if (ok)
        ok = mainWindow->restoreGeometry(geo_data);
    if (ok)
        ok = mainWindow->restoreState(layout_data);

    if (!ok) {
        QString msg = QObject::tr("Ошибка чтения файла настроек %1")
                .arg(fileName);
        QMessageBox::warning(0, QObject::tr("Ошибка восстановления параметров окна"), msg);
        return;
    }
}
