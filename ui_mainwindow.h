/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <phonon/seekslider.h>
#include <phonon/videoplayer.h>
#include <phonon/volumeslider.h>
#include "dockwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionHttp;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    DockWidget *DWVideo;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    Phonon::VideoPlayer *videoPlayer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Play;
    QPushButton *pushButton_Pause;
    Phonon::SeekSlider *seekSlider;
    Phonon::VolumeSlider *volumeSlider;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuSettings;
    DockWidget *DWQuery;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Find;
    QSpacerItem *horizontalSpacer_2;
    DockWidget *DWResult;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout_4;
    QTableView *tableView;
    DockWidget *DWEvent;
    QWidget *dockWidgetContents_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(752, 583);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setBaseSize(QSize(0, 0));
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow::separator::vertical {\n"
"     background :qlineargradient(spread:pad, x1:0.993909, y1:0.455, x2:0, y2:0.511, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(255, 255, 255, 255));\n"
"     width: 5px; /* when vertical */\n"
"     height: 5px; /* when horizontal */\n"
" \n"
"     border-radius: 2px;\n"
" \n"
" }\n"
" \n"
" QMainWindow::separator:hover::vertical {\n"
"     background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(102, 102, 102, 255), stop:1 rgba(255, 255, 255, 255));\n"
" }\n"
" \n"
"QMainWindow::separator::horizontal {\n"
"     background :qlineargradient(spread:pad, x1:0.494, y1:1, x2:0.483, y2:0.0166818, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(255, 255, 255, 255));\n"
"     width: 5px; /* when vertical */\n"
"     height: 5px; /* when horizontal */\n"
" \n"
"     border-radius: 2px;\n"
" \n"
" }\n"
" \n"
" QMainWindow::separator:hover::horizontal{\n"
"     background:qlineargradient(spread:pad, x1:0.5, y1:0.017, x2:0.5, y2:1, stop:0 rgba(102, 102, 102, 255), st"
                        "op:1 rgba(255, 255, 255, 255));\n"
" }"));
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockOptions(QMainWindow::AnimatedDocks);
        actionHttp = new QAction(MainWindow);
        actionHttp->setObjectName(QString::fromUtf8("actionHttp"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        DWVideo = new DockWidget(centralWidget);
        DWVideo->setObjectName(QString::fromUtf8("DWVideo"));
        DWVideo->setFloating(false);
        DWVideo->setFeatures(QDockWidget::NoDockWidgetFeatures);
        DWVideo->setAllowedAreas(Qt::TopDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(3, 3, 3, 3);
        videoPlayer = new Phonon::VideoPlayer(dockWidgetContents);
        videoPlayer->setObjectName(QString::fromUtf8("videoPlayer"));

        verticalLayout_2->addWidget(videoPlayer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_Play = new QPushButton(dockWidgetContents);
        pushButton_Play->setObjectName(QString::fromUtf8("pushButton_Play"));
        pushButton_Play->setMinimumSize(QSize(35, 35));
        pushButton_Play->setMaximumSize(QSize(35, 35));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Play->setIcon(icon);

        horizontalLayout->addWidget(pushButton_Play);

        pushButton_Pause = new QPushButton(dockWidgetContents);
        pushButton_Pause->setObjectName(QString::fromUtf8("pushButton_Pause"));
        pushButton_Pause->setMinimumSize(QSize(30, 30));
        pushButton_Pause->setMaximumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icon/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Pause->setIcon(icon1);

        horizontalLayout->addWidget(pushButton_Pause);

        seekSlider = new Phonon::SeekSlider(dockWidgetContents);
        seekSlider->setObjectName(QString::fromUtf8("seekSlider"));

        horizontalLayout->addWidget(seekSlider);

        volumeSlider = new Phonon::VolumeSlider(dockWidgetContents);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setMaximumSize(QSize(150, 16777215));
        volumeSlider->setProperty("muteVisible", QVariant(true));

        horizontalLayout->addWidget(volumeSlider);


        verticalLayout_2->addLayout(horizontalLayout);

        DWVideo->setWidget(dockWidgetContents);

        verticalLayout->addWidget(DWVideo);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 752, 20));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        MainWindow->setMenuBar(menuBar);
        DWQuery = new DockWidget(MainWindow);
        DWQuery->setObjectName(QString::fromUtf8("DWQuery"));
        DWQuery->setFeatures(QDockWidget::NoDockWidgetFeatures);
        DWQuery->setAllowedAreas(Qt::LeftDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget = new QTabWidget(dockWidgetContents_2);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::West);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout_3->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_Find = new QPushButton(dockWidgetContents_2);
        pushButton_Find->setObjectName(QString::fromUtf8("pushButton_Find"));

        horizontalLayout_2->addWidget(pushButton_Find);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        DWQuery->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), DWQuery);
        DWResult = new DockWidget(MainWindow);
        DWResult->setObjectName(QString::fromUtf8("DWResult"));
        DWResult->setFeatures(QDockWidget::NoDockWidgetFeatures);
        DWResult->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(3, 3, 3, 3);
        tableView = new QTableView(dockWidgetContents_3);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout_4->addWidget(tableView);

        DWResult->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), DWResult);
        DWEvent = new DockWidget(MainWindow);
        DWEvent->setObjectName(QString::fromUtf8("DWEvent"));
        DWEvent->setFeatures(QDockWidget::NoDockWidgetFeatures);
        DWEvent->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        DWEvent->setWidget(dockWidgetContents_5);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), DWEvent);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuSettings->addAction(actionHttp);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ArtixVideo", 0, QApplication::UnicodeUTF8));
        actionHttp->setText(QApplication::translate("MainWindow", "Http", 0, QApplication::UnicodeUTF8));
        pushButton_Play->setText(QString());
        pushButton_Pause->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        DWQuery->setWindowTitle(QApplication::translate("MainWindow", "Query", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0, QApplication::UnicodeUTF8));
        pushButton_Find->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", 0, QApplication::UnicodeUTF8));
        DWResult->setWindowTitle(QApplication::translate("MainWindow", "Result", 0, QApplication::UnicodeUTF8));
        DWEvent->setWindowTitle(QApplication::translate("MainWindow", "Events", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
