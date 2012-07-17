#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int count = ui->toolBox->count();
    for(int i = 0; i < count; ++i)
        ui->toolBox->removeItem(i);

    HeightToolBox = this->height() * 2/3 - 55;

    setPropertyToolBox();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ClickedFind()));
    connect(ui->HorisontalSplitter, SIGNAL(splitterMoved(int,int)), this, SLOT(movedHorisontalSplitter(int,int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPropertyToolBox()
{
    ui->frameToolBox->resize(this->width() / 3, this->height() * 2 / 3);

    ui->scrollArea->resize(ui->frameToolBox->width(), ui->frameToolBox->height() - 50);

    ui->toolBox->resize(ui->scrollArea->width() - 20, HeightToolBox);
    ui->toolBox->setStyleSheet(" QToolBox::tab { font: bold; color: green } ");

    ui->HorisontalSplitter->resize(this->width(), this->height() * 2 / 3);

    QList<int> sizes_widgets;
    sizes_widgets << ui->scrollArea->width() << this->width() - ui->scrollArea->width();
    ui->HorisontalSplitter->setSizes(sizes_widgets);

    ui->VerticalSplitter->resize(this->width(), this->height() - menuBar()->height());

    sizes_widgets.clear();
    sizes_widgets << this->height() * 2 / 3 << this->height() * 1 / 3;
    ui->VerticalSplitter->setSizes(sizes_widgets);
}

void MainWindow::setXMLReader(XMLReader *p)
{
    pXMLReader = p;
    connect(pXMLReader, SIGNAL(addItem(const char*)), SLOT(addItemInToolBox(const char*)));
}

void MainWindow::setSQL(SQL *p)
{
    pSQL = p;
}

void MainWindow::setHeightToolBox(qint32 count_query)
{
    HeightToolBox = count_query * 45;

    if(HeightToolBox < ui->toolBox->height())
    {
        HeightToolBox = ui->toolBox->height();
        return;
    }

    ui->toolBox->resize(ui->toolBox->width(), HeightToolBox);
}

QFormLayout *MainWindow::addItemInToolBox(const char *text)
{
    QFrame *pFrame = new QFrame(ui->toolBox);
    pFrame->setFrameShape(QFrame::Box);
    pFrame->setObjectName("FrameIntoToolBox");

    QFormLayout *pFormLayout = new QFormLayout(pFrame);
    pFormLayout->setObjectName("FormLayout");

    QWidget *newItem = ui->toolBox->widget(ui->toolBox->addItem(pFrame, tr(text)));
    newItem->setToolTip(QString(tr(text)));
    newItem->setObjectName("AddItem");

    setHeightToolBox(pXMLReader->getCountQuery());

    return pFormLayout;
}

void MainWindow::ClickedFind()
{
    int index = ui->toolBox->currentIndex();

    Query currentQuery = pXMLReader->getQuery(index);

    pSQL->SqlPrepare(currentQuery.sql);

    QFormLayout *pFormLayout = dynamic_cast<QFormLayout *> (ui->toolBox->currentWidget()->children().first());

    for(int i = 0; i < currentQuery.ParameterList.size(); ++i)
    {
        QLayoutItem *pLayoutItem = dynamic_cast<QLayoutItem *> (pFormLayout->itemAt(i, QFormLayout::FieldRole));

        QString str;

        if(QDateEdit *pDateEdit = dynamic_cast<QDateEdit *> (pLayoutItem->widget()))
        {
            str = pDateEdit->date().toString("yyyy-MM-dd");
        }
        else
            if(QDateTimeEdit *pDateTimeEdit = dynamic_cast<QDateTimeEdit *> (pLayoutItem->widget()))
            {
                str = pDateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
            }
            else
                if(QLineEdit *pLineEdit = dynamic_cast<QLineEdit *> (pLayoutItem->widget()))
                {
                    str = pLineEdit->text();
                }
        qDebug() << currentQuery.ParameterList.at(i).value;
        pSQL->setQueryValue(currentQuery.ParameterList.at(i).value, str);
    }

    ui->tableView->setModel(pSQL->QueryExec());
    ui->tableView->show();
}

void MainWindow::movedHorisontalSplitter(int pos, int index)
{

    ui->scrollArea->resize(pos, ui->scrollArea->height());
    ui->toolBox->resize(pos - 20, ui->toolBox->height());
    ui->pushButton->move(pos / 2 - ui->pushButton->width() / 2, ui->pushButton->y());

}

void MainWindow::resizeEvent(QResizeEvent *pe)
{
    ui->VerticalSplitter->resize(pe->size().width(), pe->size().height() - menuBar()->height() - statusBar()->height());
    ui->HorisontalSplitter->resize(pe->size().width(), pe->size().height() * 2/3);

    QList<int> sizes_widgets;
    sizes_widgets << this->height() * 2 / 3 << this->height() * 1 / 3;
    ui->VerticalSplitter->setSizes(sizes_widgets);

    ui->scrollArea->resize(ui->frameToolBox->width(), ui->frameToolBox->height() - 50);
    ui->toolBox->resize(ui->scrollArea->width() - 20, HeightToolBox);

    qint32 x_button = (ui->frameToolBox->width() - ui->pushButton->width()) / 2;
    qint32 y_button = ui->scrollArea->height() + (ui->frameToolBox->height() - ui->scrollArea->height()) / 2 - ui->pushButton->height() / 2;
    ui->pushButton->move(x_button, y_button);
}
