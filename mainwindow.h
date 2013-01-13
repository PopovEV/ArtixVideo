#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QDockWidget>
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
#include "longintvalidator.h"
#include "currencyvalidator.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void CreateInterface(); // создаем интерфейс главного окна
    QWidget *createInputBox(const QString *type);   // создание бокса для ввода значений параметра в соответствии с типом
    void loadLayout();  // восстановление сохраненных настроек приложения
    void saveLayout();  // сохранение настроек приложения

    void setXMLReader(XMLReader *p);
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
    QPushButton *pPBExecQuery;   // кнопка выполнения выбранного запроса


private:
    XMLReader *pXMLReader;
    SQL *pSQL;
    MediaPlayer *pMediaPlayer;
    HttpDownload *pHttpDownload;

    QList <QComboBox *> ListPointsComboBoxQuery;        // указатели на комбобоксы, соответствующие каждой вкладке
    QList <QTextEdit *> ListPointsDescription;          // указатели на текстовые поля для описания запроса для каждой вкладке
    QList <QGroupBox *> ListPointsGroupBoxQuery;        // указатели на бокс группировки параметров запросов


signals:


public slots:
    void ClickedFind();
    int isTabExist(QString TabName);    // существует ли уже такая вкладка?   -1 - не существует
    int addTabQueries(QString TabName);        // добавление вкладки в TabWidget с названием категории запроса
    void addQueryName(QString name, int indexTab, int numQueryInList);  // добавление названия запроса в ComboBox нужной вкладки
    void movedHorisontalSplitter(int pos, int index);
    void getDateTimeFromCurrentRow(QModelIndex ModelIndex);

protected:
    virtual void resizeEvent(QResizeEvent *pe);
    virtual void closeEvent(QCloseEvent *pe);
};

#endif // MAINWINDOW_H
