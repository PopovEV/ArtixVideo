#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QDebug>
#include <QEventLoop>
#include "videomanager.h"
#include "subtitlesmanager.h"
#include "connectionform.h"
#include "settingsform.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pDWQueries = ui->DWQuery;
    pDWVideo = ui->DWVideo;
    pDWResult = ui->DWResult;
    pDWSubtitles = ui->DWSubtitles;

    pTWQueries = ui->tabWidget;
    pPBExecQuery = ui->pushButton_Find;
    createInterface();  // создаем интерфейс главного окна

    connect(ui->action_Connection, SIGNAL(triggered()), this, SLOT(connectionCliched()));
    connect(ui->action_Settings, SIGNAL(triggered()), this, SLOT(settingsClicked()));
    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(pTWQueries, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    connect(ui->pushButton_Find, SIGNAL(clicked()), this, SLOT(clickedFind()));
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(getDateTimeFromCurrentRow(QModelIndex)));

    loadQueries();
    createQueryInterface();

    mediaPlayer = new MediaPlayer(ui->videoPlayer, ui->seekSlider, ui->volumeSlider);
    mediaPlayer->setCurrentTimeLabel(ui->label_currentTime);
    mediaPlayer->setMaxTimeLabel(ui->label_maxTime);
    connect(ui->pushButton_Play, SIGNAL(clicked()), ui->videoPlayer, SLOT(play()));
    connect(ui->pushButton_Pause, SIGNAL(clicked()), ui->videoPlayer, SLOT(pause()));
    connect(ui->pushButton_Stop, SIGNAL(clicked()), ui->videoPlayer, SLOT(stop()));
    connect(ui->pushButton_FullScreen, SIGNAL(clicked()), ui->videoPlayer->videoWidget(), SLOT(enterFullScreen()));
    connect(ui->pushButton_NextFragment, SIGNAL(clicked()), mediaPlayer, SLOT(playNextVideo()));
    connect(ui->pushButton_PreviousFragment, SIGNAL(clicked()), mediaPlayer, SLOT(playPreviousVideo()));

    SubtitlesManager::getInstance()->setListView(ui->listView_Subtitles);

    // Восстанавливаем вид главного окна
    MainWindowMemento *memento = createMemento();
    setMemento(memento);
    delete memento;
}

MainWindow::~MainWindow()
{
    delete mediaPlayer;
    delete ui;
}

void MainWindow::createInterface()
{
    ui->tabWidget->clear();
    ui->volumeSlider->setOrientation(Qt::Horizontal);
    ui->pushButton_Find->setDefault(true);
}

void MainWindow::setMemento(MainWindowMemento *memento)
{
    memento->loadState();
}

MainWindowMemento *MainWindow::createMemento()
{
    return new MainWindowMemento(this);
}

int MainWindow::addTabQueries(QString name)
{
    QFrame *pF = new QFrame();
    QVBoxLayout *pVBL = new QVBoxLayout();
    QComboBox *pCB = new QComboBox();
    pCB->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
    QTextEdit *pTE = new QTextEdit();
    pTE->setReadOnly(true);
    QGroupBox *pGB = new QGroupBox(tr("Параметры"));
    QScrollArea *pScrollArea = new QScrollArea();
    pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    pScrollArea->setWidgetResizable(true);
    pScrollArea->setFrameShape(QFrame::NoFrame);


    QVBoxLayout *pVerticalLayout = new QVBoxLayout();
    pGB->setLayout(pVerticalLayout);
    pVerticalLayout->addWidget(pScrollArea);
    pVerticalLayout->setContentsMargins(3, 3, 3, 3);

    QFormLayout *pFL = new QFormLayout();
    pFL->setRowWrapPolicy(QFormLayout::WrapLongRows);
    pFL->setContentsMargins(3, 3, 3, 3);

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setLayout(pFL);
    pScrollArea->setWidget(scrollWidget);

    connect(pCB, SIGNAL(activated(int)), this, SLOT(activateQuery(int)));

    // помещаем указатели в лист для дальнейшего использования
    comboBoxQueryList.push_back(pCB);
    descriptionList.push_back(pTE);
    groupBoxQueryList.push_back(pGB);
    widgetInScrollList.push_back(scrollWidget);
    formLayoutQueryList.push_back(pFL);

    // добавляем вкладку
    int index;
    index = pTWQueries->addTab(pF, name);

    pVBL->addWidget(new QLabel(tr("Выберите запрос:")));
    pVBL->addWidget(pCB, 1);
    pVBL->addWidget(pTE, 1);
    pVBL->addWidget(pGB, 3);
    pVBL->setContentsMargins(5, 5, 5, 5);
    pF->setLayout(pVBL);

    return index;
}

void MainWindow::getDateTimeFromCurrentRow(QModelIndex ModelIndex)
{
    int currentRow = ModelIndex.row();

    SQL *pSQL = SQL::getInstance();
    QSqlQueryModel *pSqlModel = pSQL->getSqlModel();
    qint32 columnCount = pSqlModel->columnCount();

    for(int i = 0; i < columnCount; ++i)
    {
        QString headerData =  pSqlModel->headerData(i, Qt::Horizontal).toString().toUpper();
        if(headerData == "ВРЕМЯ" || headerData == "ДАТА НАЧАЛА")
        {
            QModelIndex newModelIndex = pSqlModel->index(currentRow, i, QModelIndex());
            QDateTime selectedDateTime = pSqlModel->data(newModelIndex, Qt::DisplayRole).toDateTime();

            mediaPlayer->playVideo(selectedDateTime);
            return;
        }
    }

    QMessageBox::information(this, "Ошибка", "Не удалось найти поле \"Время\" в выбранной строке.");
}

void MainWindow::loadQueries()
{
    XMLReader *pXMLReader = new XMLReader();
    if (pXMLReader->checkFile(":/queries/Queries.xml")) {
        queryList = pXMLReader->getQueries();
    }
    delete pXMLReader;
}

void MainWindow::createQueryInterface()
{
    for (int i = 0; i < queryList->count(); ++i) {
        const Query &query = queryList->at(i);
        QString tabName = query.tabName;
        int tabIndex = isTabExist(tabName);
        if(tabIndex == -1)
            tabIndex = addTabQueries(tabName);
        addQueryName(query.name, tabIndex, query.id);
    }
}

void MainWindow::clean( QLayout &oL )
{
    QLayoutItem *poLI;
    QLayout *poL;
    QWidget *poW;

    if (oL.count() == 0)
        return;

    while( (poLI = oL.takeAt( 0 )) )
    {
        if( (poL = poLI->layout()) )
        {
            clean( *poL );
            delete poL;
        }
        else
            if( (poW = poLI->widget()) )
            {
                delete poW;
            }
        delete poLI;
        if (oL.count() == 0)
            return;
    }
}

void MainWindow::cleanFormLayout(QFormLayout *formLayout)
{
    while (formLayout->count()) {
        QLayoutItem *item = formLayout->itemAt(0);
        if (item) {
            QWidget *widget = item->widget();
            formLayout->removeItem(item);
            formLayout->removeWidget(widget);
            delete widget;
            delete item;
        }
    }
}

void MainWindow::activateQuery(int index)
{
    int currentTabIndex = pTWQueries->currentIndex();
    QComboBox *comboBox = comboBoxQueryList[currentTabIndex];
    int queryIndex = comboBox->itemData(index, Qt::UserRole).toInt();

    //Create widgets for input sql parameters
    QFormLayout *formLayout = formLayoutQueryList[currentTabIndex];
    cleanFormLayout(formLayout);
    delete formLayout;

    formLayout = new QFormLayout();
    formLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);
    formLayout->setContentsMargins(3, 3, 3, 3);
    formLayoutQueryList[currentTabIndex] = formLayout;
    widgetInScrollList[currentTabIndex]->setLayout(formLayout);

    const Query &selectedQuery = queryList->at(queryIndex);
    descriptionList.at(currentTabIndex)->setText(selectedQuery.description);

    foreach (Parameter param, selectedQuery.ParameterList) {
        formLayout->addRow(param.name,
                           WidgetsFactory::getInstance()->getWidget(param.type, param.defaultValue));
    }
}

void MainWindow::tabChanged(int tabIndex)
{
    int currentComboBoxIndex = comboBoxQueryList[tabIndex]->currentIndex();
    activateQuery(currentComboBoxIndex);
}

void MainWindow::connectionCliched()
{
    ConnectionForm *connectionForm = new ConnectionForm();
    connectionForm->exec();
    connectionForm->deleteLater();
}

void MainWindow::settingsClicked()
{
    SettingsForm *settingsForm = new SettingsForm();
    settingsForm->exec();
    settingsForm->deleteLater();
}

void MainWindow::movableDockWidgetClicked()
{

}

void MainWindow::setDefaultDockWidgetPosition()
{

}

void MainWindow::clickedFind()
{
    int currentTabIndex = pTWQueries->currentIndex();
    QComboBox *comboBox = comboBoxQueryList[currentTabIndex];
    int queryIndex = comboBox->itemData(comboBox->currentIndex(), Qt::UserRole).toInt();
    Query currentQuery = queryList->value(queryIndex);

    SQL *pSQL = SQL::getInstance();
    if (!pSQL->sqlPrepare(currentQuery.sql)) {
        QMessageBox::information(0, "Ошибка", "Не удалось подготовить запрос.\n" + currentQuery.sql);
        return;
    }

    QFormLayout *pFormLayout = formLayoutQueryList.value(currentTabIndex);
    if (pFormLayout->rowCount() != currentQuery.ParameterList.size()) {
        qDebug() << "Количество параметров на форме не соответсвует количеству параметров в sql запросе";
        qDebug() << pFormLayout->rowCount() << " " << currentQuery.ParameterList.size();
        return;
    }

    for(int i = 0; i < currentQuery.ParameterList.size(); ++i)
    {
        QLayoutItem *pLayoutItem = dynamic_cast<QLayoutItem *> (pFormLayout->itemAt(i, QFormLayout::FieldRole));
        if (!pLayoutItem) {
            qDebug() << "Error dynamic_cast<QLayoutItem *>";
        }
        QString str;
        QWidget *parameterWidget = pLayoutItem->widget();

        if(QDateEdit *pDateEdit = dynamic_cast<QDateEdit *> (parameterWidget)) {
            str = pDateEdit->date().toString("yyyy-MM-dd");
        } else {
            if(QDateTimeEdit *pDateTimeEdit = dynamic_cast<QDateTimeEdit *> (parameterWidget)) {
                str = pDateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
            } else {
                if(QLineEdit *pLineEdit = dynamic_cast<QLineEdit *> (parameterWidget)) {
                    str = pLineEdit->text();
                }
            }
        }
        pSQL->setQueryValue(currentQuery.ParameterList.at(i).value, str);
    }

    ui->tableView->setModel(pSQL->queryExec());
    ui->tableView->resizeColumnsToContents();
}

int MainWindow::isTabExist(QString tabName)
{
    for(int i = 0; i < pTWQueries->count(); i++)
        if(pTWQueries->tabText(i) == tabName)
            return i;

    return -1;
}

void MainWindow::addQueryName(QString name, int indexTab, int numQueryInList)
{
    // Добавили в комбобокс название запроса и номер этого запроса в QueryList
    comboBoxQueryList[indexTab]->addItem(name, numQueryInList);
}

void MainWindow::closeEvent(QCloseEvent *pe)
{
    MainWindowMemento *memento = createMemento();
    memento->saveState();
    delete memento;

    // Clear download folder
    QDir dir(QDir::currentPath());
    dir.cd("download");
    //removeDir(dir.path());
}
