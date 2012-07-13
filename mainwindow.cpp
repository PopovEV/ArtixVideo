#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xmlreader.h"
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

    QFormLayout *pFormLayout = new QFormLayout(pFrame);

    QWidget *newItem = ui->toolBox->widget(ui->toolBox->addItem(pFrame, tr(text)));
    newItem->setToolTip(QString(tr(text)));

    setHeightToolBox(pXMLReader->getCountQuery());

    return pFormLayout;
}

void MainWindow::ClickedFind()
{
    int index = ui->toolBox->currentIndex();


}

void MainWindow::movedHorisontalSplitter(int pos, int index)
{

    ui->scrollArea->resize(pos, ui->scrollArea->height());
    ui->toolBox->resize(pos - 20, ui->toolBox->height());
    ui->pushButton->move(pos / 2 - ui->pushButton->width() / 2, ui->pushButton->y());

}

void MainWindow::resizeEvent(QResizeEvent *pe)
{
    ui->VerticalSplitter->resize(pe->size().width(), pe->size().height() - menuBar()->height());
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
