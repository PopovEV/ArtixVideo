#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QDateTimeEdit>

#include <stdio.h>

#include "xmlreader.h"
#include "sql.h"
#include "mediaplayer.h"
#include "httpdownload.h"
#include "dockwidget.h"
#include "mainwindowmemento.h"
#include "global.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createInterface(); // создаем интерфейс главного окна
    void setMemento(MainWindowMemento *memento);
    MainWindowMemento *createMemento();

    void setSQL(SQL *p);
    void setMediaPlayer(MediaPlayer *p);
    void setHttpDownload(HttpDownload *p);

    Ui::MainWindow *ui;

    /* Элементы интерфейса формы */
    DockWidget *pDWQueries;
    DockWidget *pDWVideo;
    DockWidget *pDWResult;
    DockWidget *pDWEvent;

    QTabWidget *pTWQueries;
    QPushButton *pPBExecQuery;      // кнопка выполнения выбранного запроса
    QFormLayout *pFLCurrentInputWidgets;     // dlya razmesheniya widgetov neobhodimih dlya zaprosa


private:
    SQL *pSQL;
    MediaPlayer *pMediaPlayer;
    HttpDownload *pHttpDownload;

    QList <QComboBox *> listPointsComboBoxQuery;        // указатели на комбобоксы, соответствующие каждой вкладке
    QList <QTextEdit *> listPointsDescription;          // указатели на текстовые поля для описания запроса для каждой вкладке
    QList <QGroupBox *> listPointsGroupBoxQuery;        // указатели на бокс группировки параметров запросов

    QList<Query> *queryList;

signals:


public slots:
    void clickedFind();
    int isTabExist(QString tabName);    // существует ли уже такая вкладка?   -1 - не существует
    int addTabQueries(QString TabName);        // добавление вкладки в TabWidget с названием категории запроса
    void addQueryName(QString name, int indexTab, int numQueryInList);  // добавление названия запроса в ComboBox нужной вкладки
    void movedHorisontalSplitter(int pos, int index);
    void getDateTimeFromCurrentRow(QModelIndex ModelIndex);

    void loadQueries();
    void createQueryInterface();

protected:
    virtual void resizeEvent(QResizeEvent *pe);
    virtual void closeEvent(QCloseEvent *pe);
};

#endif // MAINWINDOW_H
