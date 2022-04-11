#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsmenu.h"

//#include "letterwidget.h"
#include "letterscontainer.h"
#include <thread>


#include "guessWord.h"



// MAINWINDOW CONSTRUCTOR
MainWindow::MainWindow(Game* currentGamePtr, SettingsFileHandler* settings_file, QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    game = currentGamePtr;
    this->settingsFile = settings_file;

    ui->setupUi(this);
    ui->centralwidget->setContentsMargins(0,0,0,0);
    ui->wurdleTitleLabel->setContentsMargins(0,0,0,0);

    letterContainerWidth = 5;
    letterContainerHeight = 6;

//    settingsFile = SettingsFileHandler("settings.txt");
//    settings = settingsFile.read();
//    std::cout<<settings["AnswerList"]<<std::endl;
//    std::cout<<settings["GuessList"]<<std::endl;
//    std::cout<<settingsFile->get("AnswerList")<<std::endl;
    game->setAnswerList(settingsFile->get("AnswerList"));
    game->setGuessList(settingsFile->get("GuessList"));
    game->readUnprocAnswers();
    game->readUnprocGuesses();
//    game->precomputeColours(); //These are slow, be careful when testing, use release mode
//    game->calcEntropies();


//    game->setInitialEntropies(); //Initial "first turn" entropies are recorded and set
    game->reset();
    game->randomAnswer();


    SetupLetterContainer(letterContainerWidth,letterContainerHeight);
    letterContainer->highlightCurrentLetter();
    letterContainer->updateLetterStyles();

    Precompute();


    // SIGNALS AND SLOTS CONNECTIONS
    connect(ui->actionSettings, &QAction::triggered,this, &MainWindow::OpenSettingsMenu);
    connect(ui->actionReset, &QAction::triggered,this, &MainWindow::Retry);

    connect(game, SIGNAL(precomputeColorsSignal(int)), this, SLOT(updateGenerateUsefulWordsColoursProgress(int)));
    connect(game, SIGNAL(calcEntropySignal(int)), this, SLOT(updateGenerateUsefulWordsEntropyProgress(int)));


}

void MainWindow::Retry()
{
    game->reset();
    game->randomAnswer();
    delete ui->containerWidget->layout();
    delete ui->validAnswersScrollArea->widget();
    delete ui->usefulWordsScrollArea->widget();
    SetupLetterContainer(letterContainerWidth,letterContainerHeight);
    letterContainer->highlightCurrentLetter();
    letterContainer->updateLetterStyles();

    if (game->getHasPrecomputerColours())
    {
        if (game->getHasInitialEntropy())
        {
            game->resetToInitialEntropies(); //Entropies are reset, but not recalculated
            FillUsefulWordsScrollArea();
        }
        else{
            CalcEntropies();
        }
    }
    else{
        Precompute();
    }

}

// MAINWINDOW DESTRUCTOR
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Precompute()
{
    std::cout<<"Precompute"<<std::endl;
//    initial = true;
    delete ui->usefulWordsScrollArea->widget();
    this->setEnabled(false);
    progressDialog = new QProgressDialog("Precomputing colours...", "Abort", 0, 100,this);
    progressDialog->setFixedSize(QSize(200,100));

    progressDialog->show();

    connect(progressDialog, SIGNAL(canceled()), this, SLOT(CancelGenerateUsefulWords()));

    disconnect(&watcher, SIGNAL(finished()), this, SLOT(finishedCalcEntropy()));
    connect(&watcher, SIGNAL(finished()), this, SLOT(finishedPrecompute()));

    QFuture<void> future = QtConcurrent::run(&Game::precomputeColours, game);
    watcher.setFuture(future);
}

void MainWindow::CalcEntropies()
{
    if (game->getHasPrecomputerColours())
    {
        std::cout<<"Calc Entropies"<<std::endl;
        delete ui->usefulWordsScrollArea->widget();
        this->setEnabled(false);
        progressDialog = new QProgressDialog("Calculating entropies...", "Abort", 0, 100, this);
        progressDialog->setFixedSize(QSize(200,100));
        progressDialog->show();


        connect(progressDialog, SIGNAL(canceled()), this, SLOT(CancelGenerateUsefulWords()));

        disconnect(&watcher, SIGNAL(finished()), this, SLOT(finishedPrecompute()));
        connect(&watcher, SIGNAL(finished()), this, SLOT(finishedCalcEntropy()));

        QFuture<void> future = QtConcurrent::run(&Game::calcEntropies, game);
        watcher.setFuture(future);
    }

}

void MainWindow::updateGenerateUsefulWordsColoursProgress(int percent)
{
//    std::cout<<percent<<std::endl;
    progressDialog->setLabelText("Precomputing colours...");
    progressDialog->setValue(percent);
}

void MainWindow::updateGenerateUsefulWordsEntropyProgress(int percent)
{
//    std::cout<<percent<<std::endl;
    progressDialog->setLabelText("Calculating entropy...");
    progressDialog->setValue(percent);
}

void MainWindow::CancelGenerateUsefulWords()
{
    std::cout<<"cancel"<<std::endl;
    if (!game->getHasPrecomputerColours())
    {
        QMessageBox msgBox;
        msgBox.setText("Must precompute colours.");
        msgBox.exec();
//        std::cout<<"Before: " << game->getCancel()<<std::endl;
//        game->uncancelCalculations();
//        std::cout<<"After: " << game->getCancel()<<std::endl;
    }
    else
        game->cancelCalculations();
}

void MainWindow::finishedPrecompute()
{
    this->setEnabled(true);
    std::cout<<"FINISHED PRECOMPUTE"<<std::endl;
    if (!game->getCancel())
    {
        game->setInitialEntropies();
        FillUsefulWordsScrollArea();
    }
    progressDialog->close();
    game->uncancelCalculations();
}

void MainWindow::finishedCalcEntropy()
{
    this->setEnabled(true);
    std::cout<<"FINISHED ENTROPY"<<std::endl;
    if (!game->getCancel())
    {
        FillUsefulWordsScrollArea();
    }
    progressDialog->close();
    game->uncancelCalculations();
}


void MainWindow::GameWon()
{
    QMessageBox msgBox;
    msgBox.setText(tr("You guessed correctly!"));
    msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    int btn = msgBox.exec();

    switch(btn){
    case QMessageBox::Retry:
        Retry();
        break;
    case QMessageBox::Close:
        msgBox.close();
//        qApp->quit();
        break;
    default:
        break;
    }

}

void MainWindow::GameLost()
{
    QMessageBox msgBox;
    msgBox.setText(tr("You lost!"));
    std::string text = "The correct word was " + game->getCurrentAnswer().getContent();
    msgBox.setInformativeText(QString::fromStdString(text));
    msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    int btn = msgBox.exec();

    switch(btn){
    case QMessageBox::Retry:
        Retry();
        break;
    case QMessageBox::Close:
        msgBox.close();
//        qApp->quit();
        break;
    default:
        break;
    }
}

// FILL SCROLL AREA WITH VALID WORDS
void MainWindow::FillValidAnswersScrollArea()
{
    delete ui->validAnswersScrollArea->widget();

    auto *innerWidget = new QWidget(ui->validAnswersScrollArea);
    auto *scrollLayout = new QGridLayout(innerWidget);

    scrollLayout->setAlignment(Qt::AlignCenter);
//    scrollLayout->setContentsMargins(10,10,10,10);
    scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    innerWidget->setLayout(scrollLayout);
    ui->validAnswersScrollArea->setWidget(innerWidget);

    int row = 0;
    int col = 0;
//    std::cout << game->getPossGuessVector().size() << std::endl;
    for (unsigned int i=0; i < game->getPossAnswerVector().size() ; i++)
    {
        if (game->getPossAnswerVector()[i].getValid())
        {
    //      std::cout<<game->getPossAnswerVector()[index].getContent()<<std::endl;
            auto *text = new QLabel();
            text->setText(QString::fromStdString(game->getPossAnswerVector()[i].getContent()));
            //text->setText("Wurdle");
            text->setContentsMargins(5,5,5,5);
            scrollLayout->addWidget(text,row,col);
            col++;
            if (col > 3)
            {
                col = 0;
                row++;
            }
        }

    }
//    std::cout<<"end"<<std::endl;
}


// INITIAL SETUP OF USEFUL WORDS SCROLL AREA
void MainWindow::FillUsefulWordsScrollArea()
{
    delete ui->usefulWordsScrollArea->widget();

    auto *innerWidget = new QWidget(ui->usefulWordsScrollArea);
    auto *scrollLayout = new QGridLayout(innerWidget);

    scrollLayout->setAlignment(Qt::AlignCenter);
//    scrollLayout->setContentsMargins(10,10,10,10);
    scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    innerWidget->setLayout(scrollLayout);
    ui->usefulWordsScrollArea->setWidget(innerWidget);

    int row = 0;
    int col = 0;
//    std::cout << game->getPossGuessVector().size() << std::endl;
    for (unsigned int i=0; i <game->getPossGuessVectorSorted().size() ; i++)
    {
        if (!game->getPossGuessVectorSorted()[i].getGuessed())
        {
    //      std::cout<<game->getPossAnswerVector()[index].getContent()<<std::endl;
            auto *text = new QLabel();
            text->setText(QString::fromStdString(game->getPossGuessVectorSorted()[i].getContent()));
            //text->setText("Wurdle");
            text->setContentsMargins(5,5,5,5);
            scrollLayout->addWidget(text,row,col);
            col++;
            if (col > 3)
            {
                col = 0;
                row++;
            }
        }
        if (i > maxUsefulWords)
            break;
    }
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
//    guessWord test;
//    test.setContent(std::to_string(letterContainer->getCurrentLetterText()));
//    test.determineColourVector(game->getCurrentAnswer());
////    std::cout<<test.displayColourVector(0)<<std::endl;
//    std::vector<uint8_t> colourVector = test.getColourVector();

//    std::cout<<letterContainer->getCurrentWord()<<std::endl;
    if (game->isValidGuess(letterContainer->getCurrentWord())) {
        std::cout << "Valid!" << std::endl;

        std::vector<uint8_t> colourVector = game->getGuessedVector()[game->getTotalGuesses()-1].getColourVector();


        letterContainer->UpdateCurrentColours(colourVector);

        if (game->isCorrectGuess(letterContainer->getCurrentWord()))
        {
            GameWon();
        }
        else{
            if (letterContainer->getSelectedRow() >= letterContainerHeight-1)
            {
                GameLost();
            }
            else{
                game->setValidAnswers();
                FillValidAnswersScrollArea();

                CalcEntropies();
//                game->calcEntropies();

//                FillUsefulWordsScrollArea();
                letterContainer->incrementSelectedRow();
            }

        }
    }
    else {
        std::cout << "Invalid!" << std::endl;
        letterContainer->invalidGuess();
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
            char key = toupper(keyStr.c_str()[0]); //  (Changed to lowercase, as that is the format that the words are stored in the txt files) - did this in get current word instead since looks better with capitals

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
    delete ui->validAnswersScrollArea->widget();
    SetupLetterContainer(letterContainerWidth,letterContainerHeight);
    letterContainer->highlightCurrentLetter();
    letterContainer->updateLetterStyles();

//    SetupvalidAnswersScrollArea();
}


// OPEN SETTINGS MENU DIALOG
void MainWindow::OpenSettingsMenu()
{
    settingsMenu *settings = new settingsMenu(settingsFile, this);
//    connect(settings, &QDialog::accepted, this, &MainWindow::Update);
    connect(settings, SIGNAL(ok_signal()), this, SLOT(GetSettings()));
    settings->exec(); // this function is blocking and so the mainwindow will not be accessible when this is open
}

void MainWindow::GetSettings()
{
//    std::cout<<"update "<<numberOfGuesses<<std::endl;
//    game->setAnswerList(answerListPath);
//    game->setGuessList(guessListPath);
    game->setAnswerList(settingsFile->get("AnswerList"));
    game->setGuessList(settingsFile->get("GuessList"));
    game->readUnprocAnswers();
    game->readUnprocGuesses();
//    game->precomputeColours(); //These are slow, be careful when testing, use release mode
    //Reset the game
    game->reset();
    game->randomAnswer();

//    GenerateUsefulWords();
    Precompute();
//    game->calcEntropies();
//    game->setInitialEntropies(); //Sets the initial entropies, so they only have to be calculated once

    letterContainerHeight = std::stoi(settingsFile->get("NoOfGuesses"));
    std::string language = settingsFile->get("Language");

    if (language == "English")
    {
//        t.load("C:/Users/ringl/Desktop/Uni Classes/Y2S2/EE273/Project/Wurdle-QT/Wurdle/lang_en.qm");
        translator.load(":/lang_en.qm");
    }
    else if (language == "French")
    {
//        t.load("C:/Users/ringl/Desktop/Uni Classes/Y2S2/EE273/Project/Wurdle-QT/Wurdle/lang_fr.qm");
        translator.load(":/lang_fr.qm");
    }
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    Update();
}
