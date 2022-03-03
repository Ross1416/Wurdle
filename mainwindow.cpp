#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "letterwidget.h"
#include "letterscontainer.h"


#include<QGridLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    auto *letter = new LetterWidget();
    QWidget *w = new QWidget();
    w->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    auto letterContainer = new LettersContainer(w);

//    QGridLayout *layout = new QGridLayout;
//    layout->setAlignment(Qt::AlignCenter);
//    layout->SetMinAndMaxSize(0);
//    layout->addWidget(letter);
//    layout->setHorizontalSpacing(0);
//    layout->setVerticalSpacing(0);
//    layout->addWidget(letterContainer);

    ui->widgetContainerLayout->setAlignment(Qt::AlignCenter);
    ui->widgetContainerLayout->addWidget(letterContainer);
              //      letterContainerPositionWidget
//    ui->centralwidget->setLayout(layout);
//    letter->setLetter('B');


}

MainWindow::~MainWindow()
{
    delete ui;
}


