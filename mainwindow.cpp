#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CreateInterface();  // создаем интерфейс главного окна
//    if(QFile::exists("DockProperties.set"))
//        loadLayout();

//    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ClickedFind()));
//    connect(ui->HorisontalSplitter, SIGNAL(splitterMoved(int,int)), this, SLOT(movedHorisontalSplitter(int,int)));

//    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateInterface()
{
    // создаем интерфейс главного окна
    QMainWindow::setCorner(Qt::TopLeftCorner, Qt::TopDockWidgetArea);

    pDWVideo = new DockWidget(tr("Видео"), this);
    pDWVideo->setObjectName("DWVideo");
    pDWVideo->setAllowedAreas(Qt::TopDockWidgetArea);
    pDWVideo->setFloating(false);
    pDWVideo->setFeatures(QDockWidget::NoDockWidgetFeatures);
    setCentralWidget(pDWVideo);
//    addDockWidget(Qt::TopDockWidgetArea, );

    QMainWindow::setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);

    pDWEvent = new DockWidget(tr("События"), this);
    pDWEvent->setObjectName("DWVideo");
    pDWEvent->setAllowedAreas(Qt::RightDockWidgetArea);
    pDWEvent->setFloating(false);
    pDWEvent->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::RightDockWidgetArea, pDWEvent);

    QMainWindow::setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);

    pDWQueries = new DockWidget(tr("Запросы"), this);
    pDWQueries->setObjectName("DWVideo");
    pDWQueries->setAllowedAreas(Qt::LeftDockWidgetArea);
    pDWQueries->setFloating(false);
    pDWQueries->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::LeftDockWidgetArea, pDWQueries);

    QMainWindow::setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

    pDWResult = new DockWidget(tr("Результаты поиска"), this);
    pDWResult->setObjectName("DWVideo");
    pDWResult->setAllowedAreas(Qt::BottomDockWidgetArea);
    pDWResult->setFloating(false);
    pDWResult->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::BottomDockWidgetArea, pDWResult);

    /*
     *Создаем TabWidget для группировки запросов по тематике
    */
    pTWQueries = new QTabWidget();
    pTWQueries->setTabPosition(QTabWidget::West);

    QVBoxLayout *pVBL = new QVBoxLayout();
    pVBL->addWidget(pTWQueries);

    QFrame *pFrame = new QFrame();
    pDWQueries->setWidget(pFrame);

    pFrame->setLayout(pVBL);

    // Кнопка выполнения запроса
    pPBExecQuery = new QPushButton(tr("Выполнить запрос"));
    pPBExecQuery->setFixedWidth(150);
    pVBL->addWidget(pPBExecQuery, 1);
    pVBL->setAlignment(pPBExecQuery, Qt::AlignHCenter);
}

int MainWindow::addTabQueries(QString name)
{
    QFrame *pF = new QFrame();
    QVBoxLayout *pVBL = new QVBoxLayout();
    QComboBox *pCB = new QComboBox();
    QTextEdit *pTE = new QTextEdit();
    QGroupBox *pGB = new QGroupBox(tr("Параметры"));

    pTE->setDisabled(true);
    // не позволяем длинным строкам расширять виджет(в середине длинной строки вставляется троеточие)
    pCB->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);

    // помещаем указатели в лист для дальнейшего использования
    ListPointsComboBoxQuery.push_back(pCB);
    ListPointsDescription.push_back(pTE);
    ListPointsGroupBoxQuery.push_back(pGB);

    // добавляем вкладку
    int index;
    index = pTWQueries->addTab(pF, name);

    pVBL->addWidget(new QLabel(tr("Выберите запрос:")));
    pVBL->addWidget(pCB, 1);
    pVBL->addWidget(pTE, 1);
    pVBL->addWidget(pGB, 3);
    pF->setLayout(pVBL);

    return index;
}

QWidget *MainWindow::createInputBox(const QString *type)
{
    if(type->toUpper() == "INT")
    {
        LongIntValidator *pLongIntValidator = new LongIntValidator();

        QLineEdit *pLineEdit = new QLineEdit();
        pLineEdit->setValidator(pLongIntValidator);

        return pLineEdit;
    }
    else
        if(type->toUpper() == "CHAR")
        {
            QLineEdit *pLineEdit = new QLineEdit();

            return pLineEdit;
        }
        else
            if(type->toUpper() == "CURRENCY")
            {
                CurrencyValidator *pCurrencyValidator = new CurrencyValidator();

                QLineEdit *pLineEdit = new QLineEdit();
                pLineEdit->setValidator(pCurrencyValidator);

                return pLineEdit;
            }
            else
                if(type->toUpper() == "DATE")
                {
                    QDateEdit *pDateEdit = new QDateEdit(QDate::currentDate());
                    pDateEdit->setCalendarPopup(true);

                    return pDateEdit;
                }
                else
                    if(type->toUpper() == "DATETIME")
                    {
                        QDateTimeEdit *pDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());
                        pDateTimeEdit->setCalendarPopup(true);

                        return pDateTimeEdit;
                    }
                    else
                    {
                        QMessageBox::information(this, tr("Ошибка!"), tr("Тип параметра задан неверно!"));
                        return NULL;
                    }
}

void MainWindow::loadLayout()
{
    QString fileName = "DockProperties.set";

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QString msg = tr("Не удается открыть файл настроек %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Ошибка"), msg);
        return;
    }

    uchar geo_size;
    QByteArray geo_data;
    QByteArray layout_data;

    bool ok = file.getChar((char*)&geo_size);
    if (ok) {
        geo_data = file.read(geo_size);
        ok = geo_data.size() == geo_size;
    }
    if (ok) {
        layout_data = file.readAll();
        ok = layout_data.size() > 0;
    }

    if (ok)
        ok = restoreGeometry(geo_data);
    if (ok)
        ok = restoreState(layout_data);

    if (!ok) {
        QString msg = tr("Ошибка чтения файла настроек %1")
                        .arg(fileName);
        QMessageBox::warning(this, tr("Ошибка"), msg);
        return;
    }
}

void MainWindow::saveLayout()
{
    QString fileName = "DockProperties.set";

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QString msg = tr("Не удается открыть файл настроек %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Ошибка"), msg);
        return;
    }

    QByteArray geo_data = saveGeometry();
    QByteArray layout_data = saveState();

    bool ok = file.putChar((uchar)geo_data.size());
    if (ok)
        ok = file.write(geo_data) == geo_data.size();
    if (ok)
        ok = file.write(layout_data) == layout_data.size();

    if (!ok) {
        QString msg = tr("Ошибка записи настроек в %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Ошибка"), msg);
        return;
    }
}

void MainWindow::setXMLReader(XMLReader *p)
{
    pXMLReader = p;
    connect(pXMLReader, SIGNAL(addTab(QString)), SLOT(addTabQueries(QString)));
    connect(pXMLReader, SIGNAL(addQueryName(QString,int,int)), SLOT(addQueryName(QString,int,int)));
    connect(pXMLReader, SIGNAL(isTabExist(QString)), SLOT(isTabExist(QString)));
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
    pHttpDownload = p;
    connect(pHttpDownload, SIGNAL(fileDownloaded(QString, QDateTime)), pMediaPlayer, SLOT(LoadVideo(QString, QDateTime)));
}

void MainWindow::getDateTimeFromCurrentRow(QModelIndex ModelIndex)
{
//    int currentRow = ModelIndex.row();

//    QSqlQueryModel *pSqlModel = pSQL->getSqlModel();
//    qint32 columnCount = pSqlModel->columnCount();

//    for(int i = 0; i < columnCount; ++i)
//    {
//        QString headerData =  pSqlModel->headerData(i, Qt::Horizontal).toString().toUpper();
//        if(headerData == tr("ВРЕМЯ"))
//        {
//            QModelIndex newModelIndex = pSqlModel->index(currentRow, i, QModelIndex());

//            pHttpDownload->setUrl((pSqlModel->data(newModelIndex, Qt::DisplayRole).toDateTime()));
//            return;
//        }
//    }
}

void MainWindow::ClickedFind()
{
//    int index = ui->toolBox->currentIndex();

//    Query currentQuery = pXMLReader->getQuery(index);

//    pSQL->SqlPrepare(currentQuery.sql);

//    QFormLayout *pFormLayout = dynamic_cast<QFormLayout *> (ui->toolBox->currentWidget()->children().first());

//    for(int i = 0; i < currentQuery.ParameterList.size(); ++i)
//    {
//        QLayoutItem *pLayoutItem = dynamic_cast<QLayoutItem *> (pFormLayout->itemAt(i, QFormLayout::FieldRole));

//        QString str;

//        if(QDateEdit *pDateEdit = dynamic_cast<QDateEdit *> (pLayoutItem->widget()))
//        {
//            str = pDateEdit->date().toString("yyyy-MM-dd");
//        }
//        else
//            if(QDateTimeEdit *pDateTimeEdit = dynamic_cast<QDateTimeEdit *> (pLayoutItem->widget()))
//            {
//                str = pDateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
//            }
//            else
//                if(QLineEdit *pLineEdit = dynamic_cast<QLineEdit *> (pLayoutItem->widget()))
//                {
//                    str = pLineEdit->text();
//                }
//        qDebug() << currentQuery.ParameterList.at(i).value;
//        pSQL->setQueryValue(currentQuery.ParameterList.at(i).value, str);
//    }

//    ui->tableView->setModel(pSQL->QueryExec());
    //    ui->tableView->show();
}

int MainWindow::isTabExist(QString TabName)
{
    for(int i = 0; i < pTWQueries->count(); i++)
        if(pTWQueries->tabText(i) == TabName)
            return i;

    return -1;
}

void MainWindow::addQueryName(QString name, int indexTab, int numQueryInList)
{
    ListPointsComboBoxQuery[indexTab]->addItem(name, numQueryInList);   // Добавили в комбобокс название запроса и номер этого запроса в QueryList
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
    saveLayout();
}
