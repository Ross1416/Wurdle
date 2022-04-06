#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsmenu.h"

//#include "letterwidget.h"
#include "letterscontainer.h"
#include<QGridLayout>
#include<QKeyEvent>
#include<iostream>
#include<QTranslator>

// MAINWINDOW CONSTRUCTOR
MainWindow::MainWindow(Game* currentGamePtr, QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    game = currentGamePtr;

    ui->setupUi(this);
    ui->centralwidget->setContentsMargins(0,0,0,0);
    ui->wurdleTitleLabel->setContentsMargins(0,0,0,0);

    letterContainerWidth = 5;
    letterContainerHeight = 6;

    SetupLetterContainer(letterContainerWidth,letterContainerHeight);
    letterContainer->highlightCurrentLetter();
    letterContainer->updateLetterStyles();
    SetupValidWordsScrollArea();


    // SIGNALS AND SLOTS CONNECTIONS
    connect(ui->actionSettings, &QAction::triggered,this, &MainWindow::OpenSettingsMenu);
}

// MAINWINDOW DESTRUCTOR
MainWindow::~MainWindow()
{
    delete ui;
}

// INITIAL SETUP OF VALID WORDS SCROLL AREA
void MainWindow::SetupValidWordsScrollArea()
{
    auto *innerWidget = new QWidget(ui->validWordsScrollArea);

    auto *scrollLayout = new QGridLayout(innerWidget);
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

// INITIAL SETUP OF USEFUL WORDS SCROLL AREA
void MainWindow::SetupUsefulWordsScrollArea()
{
// testing change 4
}

// INITIAL SETUP OF LETTERCONTAINER
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

void MainWindow::CheckWord()
{
    //std::cout << currentGame.getNumCharacters() << std::endl;
    if (letterContainer->getCurrentWord() != "")
    {
//        letterContainer->incrementSelectedRow();
//        letterContainer->invalidGuess();
    }
}

// KEYPRESS HANDLER
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
    // If return/enter key is pressed
    else if (event->key() == Qt::Key_Return)
    {
        this->CheckWord();
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

void MainWindow::Update()
{
    delete letterContainer;
    delete ui->containerWidget->layout();
    SetupLetterContainer(letterContainerWidth,letterContainerHeight);
    letterContainer->highlightCurrentLetter();
    letterContainer->updateLetterStyles();
//    delete ui->validWordsScrollArea->widget();
//    SetupValidWordsScrollArea();
}

// OPEN SETTINGS MENU DIALOG
void MainWindow::OpenSettingsMenu()
{
    settingsMenu *settings = new settingsMenu(this);
//    connect(settings, &QDialog::accepted, this, &MainWindow::Update);
    connect(settings, SIGNAL(ok_signal(std::string, std::string, int, std::string)), this, SLOT(GetSettings(std::string, std::string, int, std::string)));
    settings->exec(); // this function is blocking and so the mainwindow will not be accessible when this is open
}

void MainWindow::GetSettings(std::string answerListPath, std::string guessListPath,int noOfGuesses, std::string language)
{
//    std::cout<<"update "<<numberOfGuesses<<std::endl;
    game->setAnswerList(answerListPath);
    game->setGuessList(guessListPath);
    letterContainerHeight = noOfGuesses;

    QTranslator t;


    if (language == "English")
    {
        t.load("C:/Users/ringl/Desktop/Uni Classes/Y2S2/EE273/Project/Wurdle-QT/Wurdle/lang_en.qm");
    }
    else if (language == "French")
    {
        t.load("C:/Users/ringl/Desktop/Uni Classes/Y2S2/EE273/Project/Wurdle-QT/Wurdle/lang_fr.qm");
    }
    qApp->installTranslator(&t);
    ui->retranslateUi(this);
    Update();
}






