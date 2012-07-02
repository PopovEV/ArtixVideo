#include <QApplication>
#include <QtGui>

#include "mainwindow.h"
#include "xmlreader.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    XMLReader *xml_reader = new XMLReader();
    xml_reader->ReadFile("d:/POVT/NIRS/Projects/ArtixVideo/Queries.xml");

    return a.exec();
}
