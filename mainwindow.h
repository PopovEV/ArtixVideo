#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "xmlreader.h"
#include "sql.h"
#include "mediaplayer.h"
#include "httpdownload.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setPropertyToolBox();
    void setXMLReader(XMLReader *p);
    void setSQL(SQL *p);
    void setMediaPlayer(MediaPlayer *p);
    void setHeightToolBox(qint32 count_query);
    void setHttpDownload(HttpDownload *p);

    Ui::MainWindow *ui;

private:
    qint32 HeightToolBox;

    XMLReader *pXMLReader;
    SQL *pSQL;
    MediaPlayer *pMediaPlayer;
    HttpDownload *pHttpDownload;

signals:


public slots:
    void ClickedFind();
    void movedHorisontalSplitter(int pos, int index);
    QFormLayout *addItemInToolBox(const char* text);
    void getDateTimeFromCurrentRow(QModelIndex ModelIndex);

protected:
    virtual void resizeEvent(QResizeEvent *pe);
};

#endif // MAINWINDOW_H
