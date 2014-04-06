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

    SQL *sqlDB = new SQL();
    //    MediaPlayer *pMediaPlayer = new MediaPlayer();
    HttpDownload *httpDownload = new HttpDownload();
    MainWindow* w = new MainWindow();
    //    w->setAttribute(Qt::WA_AlwaysShowToolTips, true);
    w->setSQL(sqlDB);
    //    w->setMediaPlayer(pMediaPlayer);
    w->setHttpDownload(httpDownload);

    sqlDB->createConnection();
    w->showMaximized();

    return a.exec();
}
