#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "letterwidget.h"
#include "letterscontainer.h"


#include<QGridLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setContentsMargins(0,0,0,0);
    ui->wurdleTitleLabel->setContentsMargins(0,0,0,0);

//    auto *letter = new LetterWidget();
    QWidget *w = new QWidget();
    w->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    int width = 5;
    int height = 6;
    auto letterContainer = new LettersContainer(width, height, w);

//    QGridLayout *layout = new QGridLayout;
//    layout->setAlignment(Qt::AlignCenter);
//    layout->SetMinAndMaxSize(0);
//    layout->addWidget(letter);
//    layout->setHorizontalSpacing(0);
//    layout->setVerticalSpacing(0);
//    layout->addWidget(letterContainer);

    QHBoxLayout *boxlayout = new QHBoxLayout();

    ui->containerWidget->setLayout(boxlayout);

    boxlayout->setAlignment(Qt::AlignCenter);
    boxlayout->addWidget(letterContainer);
              //      letterContainerPositionWidget
//    ui->centralwidget->setLayout(layout);
//    letter->setLetter('B');

    letterContainer->setLetterColour("green", 4,5);
    letterContainer->setLetterText('H',3,2);

    letterContainer->setLetterColour("red", 2,1);
    letterContainer->setLetterText('L',2,1);

    letterContainer->setLetterColour("grey",0,0);
    letterContainer->setLetterText('A',0,0);

    letterContainer->setLetterHighlight(0,0);

    letterContainer->updateLetterStyles();

    auto *inner = new QWidget(ui->validWordsScrollArea);

    auto *scrollLayout = new QGridLayout();
    scrollLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
//    scrollLayout->setContentsMargins(10,10,10,10);
    scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    inner->setLayout(scrollLayout);


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


//    auto *text2 = new QLabel();
//    text2->setText("Wurdle");

//    auto *text3 = new QLabel();
//    text3->setText("Wurdle");

//    text->setContentsMargins(5,0,5,0);
//    text2->setContentsMargins(5,0,5,0);
//    text3->setContentsMargins(5,0,5,0);

//    scrollLayout->addWidget(text,0,0);
//    scrollLayout->addWidget(text2,1,0);
//    scrollLayout->addWidget(text3,0,1);
//    ui->validWordsScrollArea->setLayout(scrollLayout);
    ui->validWordsScrollArea->setWidget(inner);

}

MainWindow::~MainWindow()
{
    delete ui;
}


