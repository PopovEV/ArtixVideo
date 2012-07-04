#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addToolBox();
    void setHeightToolBox(qint32 count_query);

private:
    Ui::MainWindow *ui;

    QScrollArea *pScrollArea;
    QFrame      *pFrameVideo;
    QFrame      *pFrameTable;
    QToolBox    *pToolBox;
    QSplitter   *pHorisontalSplitter;
    QSplitter   *pVerticalSplitter;

    qint32 HeightToolBox;

public slots:

protected:
    virtual void resizeEvent(QResizeEvent *pe);
};

#endif // MAINWINDOW_H
