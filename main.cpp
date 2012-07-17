#include <QApplication>
#include <QtGui>

#include "mainwindow.h"
#include "xmlreader.h"
#include "sql.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    XMLReader *xml_reader = new XMLReader();

    SQL * sql_db = new SQL();    

    MainWindow* w = new MainWindow();
    w->setAttribute(Qt::WA_AlwaysShowToolTips, true);
    w->setXMLReader(xml_reader);
    w->setSQL(sql_db);

    xml_reader->ReadFile("d:/POVT/NIRS/Projects/ArtixVideo/Queries.xml");
    sql_db->createConnection();

    w->show();

    return a.exec();
}
