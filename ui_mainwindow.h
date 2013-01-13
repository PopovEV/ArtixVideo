/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat 12. Jan 20:00:20 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ArtixVideo", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
