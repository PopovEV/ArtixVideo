#include <QApplication>
#include <QtGui>
#include <QtNetwork>

#include "mainwindow.h"
#include "xmlreader.h"
#include "sql.h"
#include "mediaplayer.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    XMLReader *xml_reader = new XMLReader();

    SQL * sql_db = new SQL();

    MediaPlayer *pMediaPlayer = new MediaPlayer();

    MainWindow* w = new MainWindow();
    w->setAttribute(Qt::WA_AlwaysShowToolTips, true);
    w->setXMLReader(xml_reader);
    w->setSQL(sql_db);
    w->setMediaPlayer(pMediaPlayer);


    xml_reader->ReadFile("d:/POVT/NIRS/Projects/ArtixVideo/Queries.xml");
    sql_db->createConnection();

    w->show();

    QFile file("data.flv");
    if(file.open(QIODevice::WriteOnly)){
        QHttp *pHttp = new QHttp("localhost", 80);
        pHttp->get("/110342-INJ.flv", &file);

        file.close();
    }


    return a.exec();
}
