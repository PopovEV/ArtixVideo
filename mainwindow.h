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
#include "widgetsfactory.h"
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

private:
    SQL *pSQL;
    MediaPlayer *pMediaPlayer;
    HttpDownload *httpDownload;

    QList<QComboBox *> comboBoxQueryList;        // указатели на комбобоксы, соответствующие каждой вкладке
    QList<QTextEdit *> descriptionList;          // указатели на текстовые поля для описания запроса для каждой вкладке
    QList<QGroupBox *> groupBoxQueryList;        // указатели на бокс группировки параметров запросов
    QList<QFormLayout *> formLayoutQueryList;

    QList<Query> *queryList;

    void clean(QLayout &oL);
    void downloadFile(QDateTime &selectedTime);
    bool downloadIndexFile(QDateTime &selectedTime);
    QStringList getVideoFileNames(QString indexFileName);
    QString searchSuitableFileName(const QStringList &videoFileNames, QDateTime *selectedDateTime);
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

    void activateQuery(int index);
    void tabChanged(int tabIndex);

protected:
    virtual void resizeEvent(QResizeEvent *pe);
    virtual void closeEvent(QCloseEvent *pe);
};

#endif // MAINWINDOW_H
