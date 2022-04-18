/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

// ui_mainwindow.h
// Author: Ross Inglis
// Last modifier: 18/04/22

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSettings;
    QAction *actionReset;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QScrollArea *validAnswersScrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QLabel *wurdleTitleLabel;
    QSpacerItem *verticalSpacer;
    QWidget *containerWidget;
    QScrollArea *usefulGuessesScrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 700);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1000, 700));
        MainWindow->setBaseSize(QSize(1000, 700));
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../icon/ee273-project-icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        MainWindow->setIconSize(QSize(256, 256));
        MainWindow->setAnimated(false);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionSettings->setCheckable(false);
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(5, 5, 5, 5);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(16777215, 20));
        QFont font;
        font.setPointSize(12);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_2, 1, 3, 1, 1, Qt::AlignHCenter|Qt::AlignBottom);

        validAnswersScrollArea = new QScrollArea(centralwidget);
        validAnswersScrollArea->setObjectName(QString::fromUtf8("validAnswersScrollArea"));
        validAnswersScrollArea->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(validAnswersScrollArea->sizePolicy().hasHeightForWidth());
        validAnswersScrollArea->setSizePolicy(sizePolicy1);
        validAnswersScrollArea->setMinimumSize(QSize(250, 500));
        validAnswersScrollArea->setMaximumSize(QSize(250, 500));
        validAnswersScrollArea->setBaseSize(QSize(0, 0));
        validAnswersScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        validAnswersScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        validAnswersScrollArea->setWidgetResizable(true);
        validAnswersScrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 248, 498));
        validAnswersScrollArea->setWidget(scrollAreaWidgetContents_2);

        gridLayout_2->addWidget(validAnswersScrollArea, 2, 3, 1, 1);

        wurdleTitleLabel = new QLabel(centralwidget);
        wurdleTitleLabel->setObjectName(QString::fromUtf8("wurdleTitleLabel"));
        wurdleTitleLabel->setMinimumSize(QSize(0, 60));
        wurdleTitleLabel->setMaximumSize(QSize(16777215, 60));
        QFont font1;
        font1.setPointSize(25);
        wurdleTitleLabel->setFont(font1);
        wurdleTitleLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        gridLayout_2->addWidget(wurdleTitleLabel, 0, 2, 1, 1, Qt::AlignHCenter|Qt::AlignTop);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 2, 1, 1);

        containerWidget = new QWidget(centralwidget);
        containerWidget->setObjectName(QString::fromUtf8("containerWidget"));
        sizePolicy1.setHeightForWidth(containerWidget->sizePolicy().hasHeightForWidth());
        containerWidget->setSizePolicy(sizePolicy1);
        containerWidget->setMinimumSize(QSize(400, 500));

        gridLayout_2->addWidget(containerWidget, 2, 2, 1, 1);

        usefulGuessesScrollArea = new QScrollArea(centralwidget);
        usefulGuessesScrollArea->setObjectName(QString::fromUtf8("usefulGuessesScrollArea"));
        sizePolicy1.setHeightForWidth(usefulGuessesScrollArea->sizePolicy().hasHeightForWidth());
        usefulGuessesScrollArea->setSizePolicy(sizePolicy1);
        usefulGuessesScrollArea->setMinimumSize(QSize(250, 500));
        usefulGuessesScrollArea->setMaximumSize(QSize(250, 500));
        usefulGuessesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        usefulGuessesScrollArea->setWidgetResizable(true);
        usefulGuessesScrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 248, 498));
        usefulGuessesScrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(usefulGuessesScrollArea, 2, 1, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 20));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 17));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuOptions->menuAction());
        menuOptions->addAction(actionReset);
        menuOptions->addAction(actionSettings);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Wurdle", nullptr));
        actionSettings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        actionReset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Valid Answers", nullptr));
        wurdleTitleLabel->setText(QCoreApplication::translate("MainWindow", "WURDLE", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Useful Guesses", nullptr));
        menuOptions->setTitle(QCoreApplication::translate("MainWindow", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
