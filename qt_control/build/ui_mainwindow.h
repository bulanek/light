/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QCommandLinkButton *commandLinkButton;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_8;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_6;
    QCommandLinkButton *commandLinkButton_3;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_6;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QLabel *label_5;
    QCommandLinkButton *commandLinkButton_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(401, 579);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_7 = new QGridLayout(centralWidget);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        commandLinkButton = new QCommandLinkButton(groupBox_4);
        commandLinkButton->setObjectName(QStringLiteral("commandLinkButton"));

        gridLayout_4->addWidget(commandLinkButton, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_3->addWidget(label_3, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 1, 1, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox = new QGroupBox(groupBox_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setCheckable(true);
        pushButton_2->setAutoRepeat(false);
        pushButton_2->setAutoExclusive(false);

        gridLayout->addWidget(pushButton_2, 0, 0, 1, 1);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setCheckable(true);

        gridLayout->addWidget(pushButton_3, 1, 0, 1, 1);

        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setCheckable(true);

        gridLayout->addWidget(pushButton_4, 2, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 1, 1, 1, 1);

        pushButton = new QPushButton(groupBox_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setCheckable(true);

        gridLayout_4->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_8 = new QPushButton(groupBox_4);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setCheckable(true);

        gridLayout_4->addWidget(pushButton_8, 0, 1, 1, 1);


        gridLayout_7->addWidget(groupBox_4, 1, 0, 1, 3);

        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        gridLayout_6 = new QGridLayout(groupBox_6);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        commandLinkButton_3 = new QCommandLinkButton(groupBox_6);
        commandLinkButton_3->setObjectName(QStringLiteral("commandLinkButton_3"));

        gridLayout_6->addWidget(commandLinkButton_3, 2, 0, 1, 1);

        groupBox_5 = new QGroupBox(groupBox_6);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_5->addWidget(label_9, 1, 1, 1, 1);

        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_5->addWidget(label_8, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_5->addWidget(label_6, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_5, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(groupBox_6);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setCheckable(true);
        pushButton_5->setChecked(false);

        gridLayout_2->addWidget(pushButton_5, 0, 0, 1, 1);

        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setCheckable(true);

        gridLayout_2->addWidget(pushButton_6, 1, 0, 1, 1);

        pushButton_7 = new QPushButton(groupBox_2);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setCheckable(true);

        gridLayout_2->addWidget(pushButton_7, 2, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_2, 1, 1, 1, 1);

        pushButton_9 = new QPushButton(groupBox_6);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setCheckable(true);

        gridLayout_6->addWidget(pushButton_9, 0, 0, 1, 1);

        pushButton_10 = new QPushButton(groupBox_6);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setCheckable(true);

        gridLayout_6->addWidget(pushButton_10, 0, 1, 1, 1);


        gridLayout_7->addWidget(groupBox_6, 3, 0, 1, 3);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_7->addWidget(label_5, 4, 0, 1, 3);

        commandLinkButton_2 = new QCommandLinkButton(centralWidget);
        commandLinkButton_2->setObjectName(QStringLiteral("commandLinkButton_2"));

        gridLayout_7->addWidget(commandLinkButton_2, 6, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Luster 1", Q_NULLPTR));
        commandLinkButton->setText(QApplication::translate("MainWindow", "SetData", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Connection ", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "IP Address:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Not given addr.", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Socket:", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Socket", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Lights", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Light 1", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Light 2", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "Light 3", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "PIR On", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "Lights ON", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Luster 2", Q_NULLPTR));
        commandLinkButton_3->setText(QApplication::translate("MainWindow", "SetData", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Connection ", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Not given addr.", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Socket", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Socket:", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "IP Address:", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Lights", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "Light 1", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "Light 2", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "Light 3", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindow", "PIR On", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("MainWindow", "Lights ON", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Received data", Q_NULLPTR));
        commandLinkButton_2->setText(QApplication::translate("MainWindow", "GetData", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
