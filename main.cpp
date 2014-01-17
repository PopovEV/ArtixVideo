#include <QApplication>
#include <QtGui>

#include "mainwindow.h"
#include "xmlreader.h"
#include "sql.h"
#include "mediaplayer.h"
#include "httpdownload.h"
#include "httpdialog.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    XMLReader *xml_reader = new XMLReader();

//    SQL * sql_db = new SQL();

//    MediaPlayer *pMediaPlayer = new MediaPlayer();

//    HttpDownload *pHttpDownload = new HttpDownload();

    MainWindow* w = new MainWindow();
//    w->setAttribute(Qt::WA_AlwaysShowToolTips, true);
    w->setXMLReader(xml_reader);
//    w->setSQL(sql_db);
//    w->setMediaPlayer(pMediaPlayer);
//    w->setHttpDownload(pHttpDownload);


    xml_reader->ReadFile("/home/evgeniy/workspace/kursovaya/ArtixVideo/Queries.xml");
//    sql_db->createConnection();
    w->showMaximized();

    return a.exec();
}
