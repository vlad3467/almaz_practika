/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *StartPushButton;
    QTableView *PacketsTableView;
    QPushButton *PausePushButton;
    QPushButton *StopPushButton;
    QComboBox *ifaceComboBox;
    QLineEdit *IPLineEdit;
    QPushButton *IPPushButton;
    QMenuBar *menubar;
    QMenu *menuPortSniffer;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(859, 585);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 370, 91, 20));
        StartPushButton = new QPushButton(centralwidget);
        StartPushButton->setObjectName("StartPushButton");
        StartPushButton->setGeometry(QRect(20, 80, 90, 29));
        PacketsTableView = new QTableView(centralwidget);
        PacketsTableView->setObjectName("PacketsTableView");
        PacketsTableView->setGeometry(QRect(20, 120, 641, 241));
        PausePushButton = new QPushButton(centralwidget);
        PausePushButton->setObjectName("PausePushButton");
        PausePushButton->setGeometry(QRect(130, 80, 90, 29));
        StopPushButton = new QPushButton(centralwidget);
        StopPushButton->setObjectName("StopPushButton");
        StopPushButton->setGeometry(QRect(240, 80, 90, 29));
        ifaceComboBox = new QComboBox(centralwidget);
        ifaceComboBox->setObjectName("ifaceComboBox");
        ifaceComboBox->setGeometry(QRect(20, 40, 461, 28));
        IPLineEdit = new QLineEdit(centralwidget);
        IPLineEdit->setObjectName("IPLineEdit");
        IPLineEdit->setGeometry(QRect(20, 400, 241, 28));
        IPPushButton = new QPushButton(centralwidget);
        IPPushButton->setObjectName("IPPushButton");
        IPPushButton->setGeometry(QRect(270, 400, 41, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 859, 25));
        menuPortSniffer = new QMenu(menubar);
        menuPortSniffer->setObjectName("menuPortSniffer");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuPortSniffer->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Search by IP:", nullptr));
        StartPushButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        PausePushButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        StopPushButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        IPPushButton->setText(QCoreApplication::translate("MainWindow", "Ok", nullptr));
        menuPortSniffer->setTitle(QCoreApplication::translate("MainWindow", "PortSniffer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
