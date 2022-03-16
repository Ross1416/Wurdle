#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "letterwidget.h"
#include "letterscontainer.h"
#include<QGridLayout>
#include<QKeyEvent>
#include<iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setContentsMargins(0,0,0,0);
    ui->wurdleTitleLabel->setContentsMargins(0,0,0,0);

    SetupLetterContainer(5,6);
    letterContainer->highlightCurrentLetter();
    letterContainer->updateLetterStyles();
    SetupValidWordsScrollArea();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::SetupValidWordsScrollArea()
{
    auto *innerWidget = new QWidget(ui->validWordsScrollArea);

    auto *scrollLayout = new QGridLayout();
    scrollLayout->setAlignment(Qt::AlignCenter);
//    scrollLayout->setContentsMargins(10,10,10,10);
    scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    innerWidget->setLayout(scrollLayout);
    ui->validWordsScrollArea->setWidget(innerWidget);

    for (int i=0; i<30; i++)
    {
        for (int j=0; j<4; j++)
        {
            auto *text = new QLabel();
            text->setText("Wurdle");
            text->setContentsMargins(5,5,5,5);
            scrollLayout->addWidget(text,i,j);
        }

    }

}

void MainWindow::SetupUsefulWordsScrollArea()
{
// testing change 4
}

void MainWindow::SetupLetterContainer(int w, int h)
{
//    QWidget *widget = new QWidget();
//    widget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    //g
    letterContainer = new LettersContainer(w, h, ui->containerWidget);

    QHBoxLayout *boxlayout = new QHBoxLayout(ui->containerWidget);

    ui->containerWidget->setLayout(boxlayout);

    boxlayout->setAlignment(Qt::AlignCenter);
    boxlayout->addWidget(letterContainer);
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{

    // Remove letter and decrement selected letter
    if (event->key() == Qt::Key_Backspace)
    {
        if (letterContainer->getCurrentLetterText() == ' ')
        {
            letterContainer->unhighlightCurrentLetter();
            letterContainer->decrementSelectedColumn();
            letterContainer->highlightCurrentLetter();
            letterContainer->setCurrentLetterText(' ');
        }
        else
        {
            letterContainer->setCurrentLetterText(' ');
        }

    }
    else
    {
        // Check if key pressed is a letter
        if (event->key() >= 0x41 && event->key() <= 0x5a)
        {
            std::string keyStr = event->text().toStdString();
            char key = toupper(keyStr.c_str()[0]);

            letterContainer->setCurrentLetterText(key);
            letterContainer->unhighlightCurrentLetter();
            letterContainer->incrementSelectedColumn();
            letterContainer->highlightCurrentLetter();
        }
    }
    letterContainer->updateLetterStyles();

}

