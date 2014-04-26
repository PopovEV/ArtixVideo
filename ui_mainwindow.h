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
#include <QtGui/QLabel>
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
#include "listview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Settings;
    QAction *action_Connection;
    QAction *action_Exit;
    QAction *action_MovableDockWidgets;
    QAction *action_DefaultDockWidgets;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_5;
    DockWidget *DWVideo;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    Phonon::VideoPlayer *videoPlayer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_PreviousFragment;
    QPushButton *pushButton_Play;
    QPushButton *pushButton_Pause;
    QPushButton *pushButton_Stop;
    QPushButton *pushButton_NextFragment;
    Phonon::SeekSlider *seekSlider;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_currentTime;
    QLabel *label;
    QLabel *label_maxTime;
    Phonon::VolumeSlider *volumeSlider;
    QPushButton *pushButton_FullScreen;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuSettings;
    QMenu *menu_2;
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
    DockWidget *DWSubtitles;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_6;
    ListView *listView_Subtitles;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1110, 800);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow::separator::vertical {\n"
"     background :qlineargradient(spread:pad, x1:0.993909, y1:0.455, x2:0, y2:0.511, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(255, 255, 255, 255));\n"
"     width: 5px; /* when vertical */\n"
"     height: 5px; /* when horizontal */\n"
"     border-radius: 2px;\n"
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
"     border-radius: 2px;\n"
" \n"
" }\n"
" \n"
" QMainWindow::separator:hover::horizontal{\n"
"     background:qlineargradient(spread:pad, x1:0.5, y1:0.017, x2:0.5, y2:1, stop:0 rgba(102, 102, 102, 255), stop:1 rgba(255, 255"
                        ", 255, 255));\n"
" }"));
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockOptions(QMainWindow::AnimatedDocks);
        action_Settings = new QAction(MainWindow);
        action_Settings->setObjectName(QString::fromUtf8("action_Settings"));
        action_Connection = new QAction(MainWindow);
        action_Connection->setObjectName(QString::fromUtf8("action_Connection"));
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        action_MovableDockWidgets = new QAction(MainWindow);
        action_MovableDockWidgets->setObjectName(QString::fromUtf8("action_MovableDockWidgets"));
        action_DefaultDockWidgets = new QAction(MainWindow);
        action_DefaultDockWidgets->setObjectName(QString::fromUtf8("action_DefaultDockWidgets"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setBaseSize(QSize(400, 300));
        verticalLayout_5 = new QVBoxLayout(centralWidget);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_5->setContentsMargins(2, 2, 2, 2);
        DWVideo = new DockWidget(centralWidget);
        DWVideo->setObjectName(QString::fromUtf8("DWVideo"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(DWVideo->sizePolicy().hasHeightForWidth());
        DWVideo->setSizePolicy(sizePolicy1);
        DWVideo->setFloating(false);
        DWVideo->setFeatures(QDockWidget::NoDockWidgetFeatures);
        DWVideo->setAllowedAreas(Qt::TopDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        videoPlayer = new Phonon::VideoPlayer(dockWidgetContents);
        videoPlayer->setObjectName(QString::fromUtf8("videoPlayer"));

        verticalLayout->addWidget(videoPlayer);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_PreviousFragment = new QPushButton(dockWidgetContents);
        pushButton_PreviousFragment->setObjectName(QString::fromUtf8("pushButton_PreviousFragment"));
        pushButton_PreviousFragment->setMinimumSize(QSize(30, 30));
        pushButton_PreviousFragment->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_PreviousFragment->setIcon(icon);

        horizontalLayout->addWidget(pushButton_PreviousFragment);

        pushButton_Play = new QPushButton(dockWidgetContents);
        pushButton_Play->setObjectName(QString::fromUtf8("pushButton_Play"));
        pushButton_Play->setMinimumSize(QSize(35, 35));
        pushButton_Play->setMaximumSize(QSize(35, 35));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icon/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Play->setIcon(icon1);
        pushButton_Play->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButton_Play);

        pushButton_Pause = new QPushButton(dockWidgetContents);
        pushButton_Pause->setObjectName(QString::fromUtf8("pushButton_Pause"));
        pushButton_Pause->setMinimumSize(QSize(30, 30));
        pushButton_Pause->setMaximumSize(QSize(30, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/icon/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Pause->setIcon(icon2);

        horizontalLayout->addWidget(pushButton_Pause);

        pushButton_Stop = new QPushButton(dockWidgetContents);
        pushButton_Stop->setObjectName(QString::fromUtf8("pushButton_Stop"));
        pushButton_Stop->setMinimumSize(QSize(30, 30));
        pushButton_Stop->setMaximumSize(QSize(30, 30));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/icon/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Stop->setIcon(icon3);

        horizontalLayout->addWidget(pushButton_Stop);

        pushButton_NextFragment = new QPushButton(dockWidgetContents);
        pushButton_NextFragment->setObjectName(QString::fromUtf8("pushButton_NextFragment"));
        pushButton_NextFragment->setMinimumSize(QSize(30, 30));
        pushButton_NextFragment->setMaximumSize(QSize(30, 30));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/icon/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_NextFragment->setIcon(icon4);

        horizontalLayout->addWidget(pushButton_NextFragment);

        seekSlider = new Phonon::SeekSlider(dockWidgetContents);
        seekSlider->setObjectName(QString::fromUtf8("seekSlider"));

        horizontalLayout->addWidget(seekSlider);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        label_currentTime = new QLabel(dockWidgetContents);
        label_currentTime->setObjectName(QString::fromUtf8("label_currentTime"));
        label_currentTime->setMinimumSize(QSize(55, 0));
        QFont font;
        font.setPointSize(9);
        font.setItalic(true);
        font.setStyleStrategy(QFont::PreferDefault);
        label_currentTime->setFont(font);
        label_currentTime->setTextFormat(Qt::RichText);

        horizontalLayout_3->addWidget(label_currentTime);

        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setTextFormat(Qt::RichText);

        horizontalLayout_3->addWidget(label);

        label_maxTime = new QLabel(dockWidgetContents);
        label_maxTime->setObjectName(QString::fromUtf8("label_maxTime"));
        label_maxTime->setMinimumSize(QSize(55, 0));
        label_maxTime->setFont(font);
        label_maxTime->setTextFormat(Qt::RichText);

        horizontalLayout_3->addWidget(label_maxTime);


        horizontalLayout->addLayout(horizontalLayout_3);

        volumeSlider = new Phonon::VolumeSlider(dockWidgetContents);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setMaximumSize(QSize(150, 16777215));
        volumeSlider->setProperty("tracking", QVariant(true));
        volumeSlider->setProperty("muteVisible", QVariant(true));

        horizontalLayout->addWidget(volumeSlider);

        pushButton_FullScreen = new QPushButton(dockWidgetContents);
        pushButton_FullScreen->setObjectName(QString::fromUtf8("pushButton_FullScreen"));
        pushButton_FullScreen->setMinimumSize(QSize(30, 30));
        pushButton_FullScreen->setMaximumSize(QSize(30, 30));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/icon/fullscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_FullScreen->setIcon(icon5);

        horizontalLayout->addWidget(pushButton_FullScreen);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 1);
        DWVideo->setWidget(dockWidgetContents);

        verticalLayout_5->addWidget(DWVideo);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1110, 20));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menuBar);
        DWQuery = new DockWidget(MainWindow);
        DWQuery->setObjectName(QString::fromUtf8("DWQuery"));
        sizePolicy1.setHeightForWidth(DWQuery->sizePolicy().hasHeightForWidth());
        DWQuery->setSizePolicy(sizePolicy1);
        DWQuery->setFloating(false);
        DWQuery->setFeatures(QDockWidget::NoDockWidgetFeatures);
        DWQuery->setAllowedAreas(Qt::LeftDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_3->setSpacing(4);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_3->setContentsMargins(4, 4, 4, 4);
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
        pushButton_Find->setMinimumSize(QSize(100, 0));
        pushButton_Find->setAutoDefault(true);
        pushButton_Find->setDefault(true);

        horizontalLayout_2->addWidget(pushButton_Find);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalLayout_3->setStretch(0, 1);
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
        verticalLayout_4->setContentsMargins(4, 4, 4, 4);
        tableView = new QTableView(dockWidgetContents_3);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

        verticalLayout_4->addWidget(tableView);

        DWResult->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), DWResult);
        DWSubtitles = new DockWidget(MainWindow);
        DWSubtitles->setObjectName(QString::fromUtf8("DWSubtitles"));
        sizePolicy1.setHeightForWidth(DWSubtitles->sizePolicy().hasHeightForWidth());
        DWSubtitles->setSizePolicy(sizePolicy1);
        DWSubtitles->setFeatures(QDockWidget::NoDockWidgetFeatures);
        DWSubtitles->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        verticalLayout_6 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_6->setSpacing(4);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_6->setContentsMargins(4, 4, 4, 4);
        listView_Subtitles = new ListView(dockWidgetContents_5);
        listView_Subtitles->setObjectName(QString::fromUtf8("listView_Subtitles"));
        listView_Subtitles->setStyleSheet(QString::fromUtf8("QListView  {\n"
"    show-decoration-selected: 1; /* make the selection span the entire width of the view */\n"
"}\n"
"\n"
"QListView::item:selected  {\n"
"    border: 1px solid #6a6ea9;\n"
"}\n"
" \n"
"QListView::item:selected:!active  {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #6a6ea9, stop: 1 #888dd9);\n"
"}\n"
" \n"
"QListView::item:selected:active  {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #6a6ea9, stop: 1 #888dd9);\n"
"}\n"
" \n"
"QListView::item:hover  {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #FAFBFE, stop: 1 #DCDEF1);\n"
"}"));
        listView_Subtitles->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView_Subtitles->setSelectionMode(QAbstractItemView::MultiSelection);
        listView_Subtitles->setSelectionBehavior(QAbstractItemView::SelectRows);
        listView_Subtitles->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        listView_Subtitles->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        listView_Subtitles->setResizeMode(QListView::Adjust);
        listView_Subtitles->setLayoutMode(QListView::Batched);
        listView_Subtitles->setSpacing(2);
        listView_Subtitles->setWordWrap(true);

        verticalLayout_6->addWidget(listView_Subtitles);

        DWSubtitles->setWidget(dockWidgetContents_5);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), DWSubtitles);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(action_Connection);
        menu->addSeparator();
        menu->addAction(action_Exit);
        menuSettings->addAction(action_Settings);
        menu_2->addAction(action_MovableDockWidgets);
        menu_2->addAction(action_DefaultDockWidgets);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ArtixVideo", 0, QApplication::UnicodeUTF8));
        action_Settings->setText(QApplication::translate("MainWindow", "\320\236\320\261\321\211\320\270\320\265", 0, QApplication::UnicodeUTF8));
        action_Connection->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        action_MovableDockWidgets->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\320\265\320\277\320\270\321\202\321\214 \320\276\320\272\320\275\320\260", 0, QApplication::UnicodeUTF8));
        action_DefaultDockWidgets->setText(QApplication::translate("MainWindow", "Default", 0, QApplication::UnicodeUTF8));
        pushButton_Play->setText(QString());
        pushButton_Pause->setText(QString());
        label_currentTime->setText(QApplication::translate("MainWindow", "00:00:00", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "|", 0, QApplication::UnicodeUTF8));
        label_maxTime->setText(QApplication::translate("MainWindow", "00:00:00", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\236\320\272\320\275\320\276", 0, QApplication::UnicodeUTF8));
        DWQuery->setWindowTitle(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\200\320\276\321\201\321\213", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0, QApplication::UnicodeUTF8));
        pushButton_Find->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", 0, QApplication::UnicodeUTF8));
        DWResult->setWindowTitle(QApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\277\320\276\320\270\321\201\320\272\320\260", 0, QApplication::UnicodeUTF8));
        DWSubtitles->setWindowTitle(QApplication::translate("MainWindow", "\320\241\321\203\320\261\321\202\320\270\321\202\321\200\321\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
