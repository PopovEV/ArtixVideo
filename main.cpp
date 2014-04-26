#include <QApplication>
#include <QtGui>

#include "mainwindow.h"
#include "sql.h"
#include "mediaplayer.h"
#include "httpdownload.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    a.setApplicationName("ArtixVideo");

    MainWindow* w = new MainWindow();
    //    w->setAttribute(Qt::WA_AlwaysShowToolTips, true);
    w->showMaximized();

    return a.exec();
}
