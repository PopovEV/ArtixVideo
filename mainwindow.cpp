#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    HeightToolBox = this->height() * 2/3 - 20;
    addToolBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToolBox()
{
    pScrollArea = new QScrollArea(this);
    pFrameVideo = new QFrame(this);
    pToolBox = new QToolBox(pScrollArea);
    pHorisontalSplitter = new QSplitter(Qt::Horizontal, this);
    pVerticalSplitter = new QSplitter(Qt::Vertical, this);

    pScrollArea->setWidget(pToolBox);
    pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    pScrollArea->resize(this->width() / 3, this->height() * 2 / 3);

    pToolBox->resize(pScrollArea->width() - 20, HeightToolBox);
    pToolBox->setStyleSheet(" QToolBox::tab { font: bold; color: green} ");
    setHeightToolBox(1);

    pFrameVideo->setFrameShape(QFrame::Box);

    pHorisontalSplitter->addWidget(pScrollArea);
    pHorisontalSplitter->addWidget(pFrameVideo);
    pHorisontalSplitter->resize(this->width(), this->height() * 2 / 3);

    QList<int> sizes_widgets;
    sizes_widgets << pScrollArea->width() << this->width() - pScrollArea->width();
    pHorisontalSplitter->setSizes(sizes_widgets);

    pVerticalSplitter->addWidget(pHorisontalSplitter);
    pVerticalSplitter->addWidget(new QFrame());
    pVerticalSplitter->resize(this->width(), this->height() - menuBar()->height());
    pVerticalSplitter->move(0, menuBar()->height());

    sizes_widgets.clear();
    sizes_widgets << this->height() * 2 / 3 << this->height() * 1 / 3;
    pVerticalSplitter->setSizes(sizes_widgets);


    for(int i = 0; i<1; ++i)
    {
        pToolBox->addItem(new QLabel("aaa\nqqqqqq\nqqqqqqq\nqqqqqqq", pToolBox), tr("Вкл\nадка %1").arg(i));
    }

}

void MainWindow::setHeightToolBox(qint32 count_query)
{
    HeightToolBox = count_query * 45;
    if(HeightToolBox < pToolBox->height())
        HeightToolBox = pToolBox->height();

    pToolBox->resize(pToolBox->width(), HeightToolBox);
}

void MainWindow::resizeEvent(QResizeEvent *pe)
{
    pVerticalSplitter->resize(pe->size().width(), pe->size().height() - menuBar()->height());
    pHorisontalSplitter->resize(pe->size().width(), pe->size().height() *2/3);

    QList<int> sizes_widgets;
    sizes_widgets << this->height() * 2 / 3 << this->height() * 1 / 3;
    pVerticalSplitter->setSizes(sizes_widgets);

    pToolBox->resize(pScrollArea->width() - 20, HeightToolBox);
}

