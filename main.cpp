#include <QApplication>
#include <QtGui>

#include "mainwindow.h"
#include "sql.h"
#include "mediaplayer.h"
#include "httpdownload.h"
#include "httpdialog.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    a.setApplicationName("ArtixVideo");

    SQL *sqlDB = new SQL();
    MainWindow* w = new MainWindow();
    //    w->setAttribute(Qt::WA_AlwaysShowToolTips, true);
    w->setSQL(sqlDB);

    sqlDB->createConnection();
    w->showMaximized();

    return a.exec();
}
