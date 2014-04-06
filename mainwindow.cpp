#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QDebug>
#include <QEventLoop>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pDWQueries = ui->DWQuery;
    pDWVideo = ui->DWVideo;
    pDWResult = ui->DWResult;
    pDWEvent = ui->DWEvent;

    pTWQueries = ui->tabWidget;
    pPBExecQuery = ui->pushButton_Find;      // кнопка выполнения выбранного запроса

    createInterface();  // создаем интерфейс главного окна

    connect(pTWQueries, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    connect(ui->pushButton_Find, SIGNAL(clicked()), this, SLOT(clickedFind()));
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(getDateTimeFromCurrentRow(QModelIndex)));

    //    connect(ui->HorisontalSplitter, SIGNAL(splitterMoved(int,int)), this, SLOT(movedHorisontalSplitter(int,int)));

    //    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    loadQueries();
    createQueryInterface();

    // Восстанавливаем вид главного окна
    MainWindowMemento *memento = createMemento();
    setMemento(memento);
    delete memento;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createInterface()
{
    ui->tabWidget->clear();
    ui->volumeSlider->setOrientation(Qt::Horizontal);
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

void MainWindow::setSQL(SQL *p)
{
    pSQL = p;
}

void MainWindow::setMediaPlayer(MediaPlayer *p)
{
    pMediaPlayer = p;
    //    connect(ui->PlayButton, SIGNAL(clicked()), pMediaPlayer->getMediaObject(), SLOT(play()));
    //    connect(ui->PauseButton, SIGNAL(clicked()), pMediaPlayer->getMediaObject(), SLOT(pause()));
    //    connect(ui->LoadButton, SIGNAL(clicked()), pMediaPlayer, SLOT(slotLoad()));
    //    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), pMediaPlayer->getMediaObject(), SLOT(stop()));
    //    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(getDateTimeFromCurrentRow(QModelIndex)));

    //    pMediaPlayer->setParentForVideoWidget(ui->VideoFrame1);
    //    pMediaPlayer->setSeekSlider(ui->NavigationHorizontalLayout);
    //    pMediaPlayer->setVolumeSlider(ui->NavigationHorizontalLayout);
}

void MainWindow::setHttpDownload(HttpDownload *p)
{
    httpDownload = p;
    //    connect(pHttpDownload, SIGNAL(fileDownloaded(QString)), pMediaPlayer, SLOT(loadVideo(QString)));
}

void MainWindow::getDateTimeFromCurrentRow(QModelIndex ModelIndex)
{
    int currentRow = ModelIndex.row();

    QSqlQueryModel *pSqlModel = pSQL->getSqlModel();
    qint32 columnCount = pSqlModel->columnCount();

    for(int i = 0; i < columnCount; ++i)
    {
        QString headerData =  pSqlModel->headerData(i, Qt::Horizontal).toString().toUpper();
        if(headerData == tr("ВРЕМЯ"))
        {
            QModelIndex newModelIndex = pSqlModel->index(currentRow, i, QModelIndex());
            QDateTime selectedTime = pSqlModel->data(newModelIndex, Qt::DisplayRole).toDateTime();
            downloadFile(selectedTime);
            return;
        }
    }

    QMessageBox::information(this, "Error", "Don't find field \"Time\" in sql  model!");
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
        if (oL.count() == 0)
            return;
    }
}

void MainWindow::downloadFile(QDateTime &selectedTime)
{
    if (!downloadIndexFile(selectedTime)) {
        return;
    }

    QString indexFileName = httpDownload->getLastFileName();
    QStringList videoFileNames = getVideoFileNames(indexFileName);
    if(videoFileNames.isEmpty()) {
        QMessageBox::information(this, "Information", "There are no videos for the selected day.");
        return;
    }

    QString fileName = searchSuitableFileName(videoFileNames, &selectedTime);
    if(fileName.isEmpty()) {
       return;
    }

    //Download suitable file
    QString date;
    date = selectedTime.date().toString("yyyyMMdd");

    QUrl videoFile("http://localhost/artixvideo/" + date + "/" + fileName);
    QEventLoop eventLoop;
    connect(httpDownload, SIGNAL(fileDownloaded()), &eventLoop, SLOT(quit()));
    httpDownload->doDownload(videoFile);
    eventLoop.exec();

    QString videoFileName = httpDownload->getLastFileName();
    if(videoFileName.isNull()) {
        return;
    }

    qDebug() << "Play video " << videoFile.toString();
}

bool MainWindow::downloadIndexFile(QDateTime &selectedTime)
{
    QString date;
    date = selectedTime.date().toString("yyyyMMdd");

    QUrl indexFileUrl("http://localhost/artixvideo/" + date + "/");
    QEventLoop eventLoop;
    connect(httpDownload, SIGNAL(fileDownloaded()), &eventLoop, SLOT(quit()));
    httpDownload->doDownload(indexFileUrl);
    eventLoop.exec();

    QString indexFileName = httpDownload->getLastFileName();
    if(indexFileName.isEmpty()) {
        qDebug() << "Error download index file: " << indexFileUrl.toString();
        return false;
    }

    return true;
}

QStringList MainWindow::getVideoFileNames(QString indexFileName)
{
    QStringList fileNamesList;
    QFile indexFile(indexFileName);
    if(!indexFile.open(QFile::ReadOnly)) {
        qDebug() << "Error opening index file!";
        return fileNamesList;
    }

    QString data(indexFile.readAll());
    QRegExp regExpr("\\d*-INJ.flv", Qt::CaseInsensitive);
    int pos = 0;
    while ((pos = regExpr.indexIn(data, pos)) != -1) {
        if(!fileNamesList.isEmpty()) {
            if(fileNamesList.last() != regExpr.cap(0)) {
                fileNamesList.push_back(regExpr.cap(0));
            }
        } else {
            fileNamesList.push_back(regExpr.cap(0));
        }
        pos += regExpr.matchedLength();
    }

    return fileNamesList;
}

QString MainWindow::searchSuitableFileName(const QStringList &videoFileNames, QDateTime *selectedDateTime)
{
    QList<QTime> timeStartVideo;
    QRegExp regExpr("\\d{6,6}");
    foreach (QString fileName, videoFileNames) {
        if (regExpr.indexIn(fileName) != -1) {
            QString timeStr = regExpr.cap(0);
            QTime time = QTime::fromString(timeStr, "hhmmss");
            if (time.isValid()) {
                timeStartVideo.push_back(time);
            } else {
                qDebug() << "Time is not valid " << timeStr;
            }
        }
    }

    QTime selectedTime = selectedDateTime->time();
    QTime suitableTime;
    foreach (QTime time, timeStartVideo) {
        //TODO: Replace 300 sec by get option "VideoLenght" from config.ini
        if(selectedTime >= time && selectedTime < time.addSecs(300)) {
            suitableTime = time;
        }
    }

    if(suitableTime.isNull()) {
        QMessageBox::information(this, "Поиск видеофайла",
                                 "Не удается найти подходящий по времени видеофрагмент.");
        return QString();
    }

    return suitableTime.toString("hhmmss") + "-INJ.flv";
}

void MainWindow::activateQuery(int index)
{
    int currentTabIndex = pTWQueries->currentIndex();
    QComboBox *comboBox = comboBoxQueryList[currentTabIndex];
    int queryIndex = comboBox->itemData(index, Qt::UserRole).toInt();

    //Create widgets for input sql parameters
    QFormLayout *formLayout = formLayoutQueryList[currentTabIndex];
    clean(*formLayout);

    const Query &selectedQuery = queryList->at(queryIndex);
    descriptionList.at(currentTabIndex)->setText(selectedQuery.description);

    foreach (Parameter param, selectedQuery.ParameterList) {
        formLayout->addRow(param.name,
                           WidgetsFactory::getInstance()->getWidget(param.type));
    }
}

void MainWindow::tabChanged(int tabIndex)
{
    int currentComboBoxIndex = comboBoxQueryList[tabIndex]->currentIndex();
    activateQuery(currentComboBoxIndex);
}

void MainWindow::clickedFind()
{
    int currentTabIndex = pTWQueries->currentIndex();
    QComboBox *comboBox = comboBoxQueryList[currentTabIndex];
    int queryIndex = comboBox->itemData(comboBox->currentIndex(), Qt::UserRole).toInt();
    Query currentQuery = queryList->value(queryIndex);

    if (!pSQL->sqlPrepare(currentQuery.sql)) {
        QMessageBox::information(0, "Error", "Error prepare query\n" + currentQuery.sql);
        return;
    }

    QFormLayout *pFormLayout = formLayoutQueryList.value(currentTabIndex);
    for(int i = 0; i < currentQuery.ParameterList.size(); ++i)
    {
        QLayoutItem *pLayoutItem = dynamic_cast<QLayoutItem *> (pFormLayout->itemAt(i, QFormLayout::FieldRole));
        QString str;
        QWidget *parameterWidget = pLayoutItem->widget();

        if(QDateEdit *pDateEdit = dynamic_cast<QDateEdit *> (parameterWidget)) {
            str = pDateEdit->date().toString("yyyy-MM-dd");
            qDebug() << "QDateEdit";
        } else {
            if(QDateTimeEdit *pDateTimeEdit = dynamic_cast<QDateTimeEdit *> (parameterWidget)) {
                str = pDateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
                qDebug() << "QDateTimeEdit";
            } else {
                if(QLineEdit *pLineEdit = dynamic_cast<QLineEdit *> (parameterWidget)) {
                    str = pLineEdit->text();
                    qDebug() << "QLineEdit";
                }
            }
        }
        pSQL->setQueryValue(currentQuery.ParameterList.at(i).value, str);
    }

    ui->tableView->setModel(pSQL->queryExec());
    //    ui->tableView->show();
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

void MainWindow::movedHorisontalSplitter(int pos, int index)
{

    //    ui->scrollArea->resize(pos, ui->scrollArea->height());
    //    ui->toolBox->resize(pos - 20, ui->toolBox->height());
    //    ui->pushButton->move(pos / 2 - ui->pushButton->width() / 2, ui->pushButton->y());

}

void MainWindow::resizeEvent(QResizeEvent *pe)
{
    //    ui->VerticalSplitter->resize(pe->size().width(), pe->size().height() - menuBar()->height() - statusBar()->height());
    //    ui->HorisontalSplitter->resize(pe->size().width(), pe->size().height() * 2/3);

    //    QList<int> sizes_widgets;
    //    sizes_widgets << this->height() * 2 / 3 << this->height() * 1 / 3;
    //    ui->VerticalSplitter->setSizes(sizes_widgets);

    //    ui->scrollArea->resize(ui->frameToolBox->width(), ui->frameToolBox->height() - 50);
    //    ui->toolBox->resize(ui->scrollArea->width() - 20, HeightToolBox);

    //    qint32 x_button = (ui->frameToolBox->width() - ui->pushButton->width()) / 2;
    //    qint32 y_button = ui->scrollArea->height() + (ui->frameToolBox->height() - ui->scrollArea->height()) / 2 - ui->pushButton->height() / 2;
    //    ui->pushButton->move(x_button, y_button);
}

void MainWindow::closeEvent(QCloseEvent *pe)
{
    MainWindowMemento *memento = createMemento();
    memento->saveState();
    delete memento;
}
