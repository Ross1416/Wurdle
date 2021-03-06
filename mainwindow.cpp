// mainwindow.cpp
// Author: Ross Inglis
// Last modified: 18/04/22

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsmenu.h"

#include "letterscontainer.h"
#include "guessWord.h"

#include<iostream>

// MAINWINDOW CONSTRUCTOR
MainWindow::MainWindow(Game* currentGamePtr, SettingsFileHandler* settings_file, QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    // Assign game and settings file to member variables
    this->game = currentGamePtr;
    this->settingsFile = settings_file;
    this->progressDialog = nullptr;
    this->letterContainerLoaded = false;
    this->lettersContainer = nullptr;

    // Setup UI
    ui->setupUi(this);
    ui->centralwidget->setContentsMargins(0,0,0,0);
    ui->wurdleTitleLabel->setContentsMargins(0,0,0,0);

    // Setup game
    game->setAnswerList(settingsFile->get("AnswerList"));
    game->setGuessList(settingsFile->get("GuessList"));
    game->setNumCharacters(stoi(settingsFile->get("NoOfCharacters")));
    game->setMaxGuesses(stoi(settingsFile->get("NoOfGuesses")));


    // Try open word list text files, if error get user to browse for them
    LoadWordLists();

    game->reset();
    game->randomAnswer();


    // SIGNALS AND SLOTS CONNECTIONS
    connect(ui->actionSettings, &QAction::triggered,this, &MainWindow::OpenSettingsMenu);
    connect(ui->actionReset, &QAction::triggered,this, &MainWindow::Retry);

    connect(game, SIGNAL(precomputeColorsSignal(int)), this, SLOT(updateGenerateUsefulGuessesColoursProgress(int)));
    connect(game, SIGNAL(calcEntropySignal(int)), this, SLOT(updateGenerateUsefulGuessesEntropyProgress(int)));
}

// MAINWINDOW DESTRUCTOR
MainWindow::~MainWindow()
{
    delete ui;
}

// LOAD WORD LISTS AND CHECK FOR ERRORS
void MainWindow::LoadWordLists()
{
    try
    {
        int error = 0;
        int ans = game->readUnprocAnswers();
        int guess = game->readUnprocGuesses();

        error = ans + guess;
        throw (error);

    }
    catch (int error)
    {
        if (error > 0)
        {
            std::cout<<"Error opening word list(s)"<<std::endl;
            QMessageBox msgBox;
            msgBox.setText(tr("Error opening word list(s).\n Please browse for them."));
            msgBox.exec();
            OpenSettingsMenu();

        }
        else
        {
            // Translate
            Translate();

            // Setup letter container
            SetupLettersContainer();

            // Compute colours and entropy in another thread
            Precompute();
        }
    }
}

// RETRY FUNCTION
void MainWindow::Retry()
{
    // Reset game
    game->reset();
    game->randomAnswer();

    // Used for testing ONLY
//    game->setAnswer(200);
//    std::cout<<"current answer is: "<<game->getCurrentAnswer().getContent()<<std::endl;


    // Delete ui elements to allow them to be replaced
//    if (lettersContainer)
//        delete lettersContainer;

    try{
        delete lettersContainer;
    }
    catch(...)
    {
        std::cout<<"Couldn't delete letterscontainer."<<std::endl;
    }

    delete ui->containerWidget->layout();
    delete ui->validAnswersScrollArea->widget();
    delete ui->usefulGuessesScrollArea->widget();

    // Setup letter container
    SetupLettersContainer();


    if (game->getHasPrecomputerColours())
    {
//        std::cout<<"has pre"<<std::endl;
        if (game->getHasInitialEntropy())
        {
//            std::cout<<"has en"<<std::endl;
            game->resetToInitialEntropies(); //Entropies are reset, but not recalculated
            FillUsefulGuessesScrollArea();
        }
        else{
            CalcEntropies();
        }
    }
    else{
        Precompute();
    }

}

// PRECOMPUTE COLOURS AND ENTROPY ASYNCHRONOUSLY
void MainWindow::Precompute()
{
    // Delete useful words scroll area
    delete ui->usefulGuessesScrollArea->widget();

    // Disable mainwindow so nothing can be changed while loading
    this->setEnabled(false);

    // Setup progress dialog
    try{
        delete progressDialog;
    }
    catch(...)
    {
        std::cout<<"Couldn't delete progressDialog."<<std::endl;
    }

    progressDialog = new QProgressDialog(tr("Precomputing colours..."), tr("Abort"), 0, 100,this);
    connect(progressDialog, SIGNAL(canceled()), this, SLOT(CancelGenerateUsefulGuesses()));
    progressDialog->setFixedSize(QSize(200,100));
    progressDialog->show();

    // Disconnect from finished calc entropy slot
    disconnect(&watcher, SIGNAL(finished()), this, SLOT(finishedCalcEntropy()));
    // Connected to finished precompute slot
    connect(&watcher, SIGNAL(finished()), this, SLOT(finishedPrecompute()));

    // Start thread and set future watcher
    QFuture<void> future = QtConcurrent::run(&Game::precomputeColours, game);
    watcher.setFuture(future);
}

// CALCULATE ENTROPY ASYNCHRONOUSLY
void MainWindow::CalcEntropies()
{
    // Only try calculate entropies if colours have already been precomputed
    if (game->getHasPrecomputerColours())
    {
        // Delete useful words scroll area
        delete ui->usefulGuessesScrollArea->widget();

        // Disable mainwindow so nothing can be changed while loading
        this->setEnabled(false);

        // Setup progress dialog

        try{
            delete progressDialog;
        }
        catch(...)
        {
            std::cout<<"Couldn't delete progressDialog."<<std::endl;
        }

        progressDialog = new QProgressDialog(tr("Calculating entropies..."), tr("Abort"), 0, 100, this);
        connect(progressDialog, SIGNAL(canceled()), this, SLOT(CancelGenerateUsefulGuesses()));
        progressDialog->setFixedSize(QSize(200,100));
        progressDialog->show();

        // Disconnect from finished calc entropy slot
        disconnect(&watcher, SIGNAL(finished()), this, SLOT(finishedPrecompute()));
        // Connected to finished precompute slot
        connect(&watcher, SIGNAL(finished()), this, SLOT(finishedCalcEntropy()));

        // Start thread and set future watcher
        QFuture<void> future = QtConcurrent::run(&Game::calcEntropies, game);
        watcher.setFuture(future);
    }
}

// UPDATE PROGRESS BAR FOR PRECOMPUTE COLOURS
void MainWindow::updateGenerateUsefulGuessesColoursProgress(int percent)
{
    progressDialog->setLabelText(tr("Precomputing colours..."));
    progressDialog->setValue(percent);
}

// UPDATE PROGRESS BAR FOR CALCULATING ENTROPY
void MainWindow::updateGenerateUsefulGuessesEntropyProgress(int percent)
{
    progressDialog->setLabelText(tr("Calculating entropies..."));
    progressDialog->setValue(percent);
}

// CANCEL ENTROPY CALCULATIONS
void MainWindow::CancelGenerateUsefulGuesses()
{
    std::cout << "### Cancelled ###" << std::endl;
    game->cancelCalculations();
    CancelSettings();
}

// CALLED WHEN FINISHED PRECOMPUTING COLOURS AND CALCULATING ENTROPY
void MainWindow::finishedPrecompute()
{
    // Disable mainwindow
    this->setEnabled(true);

    // If entropy wasn't cancelled set initial entropies and fill useful words scroll area
    if (!game->getCancel())
    {
        game->setInitialEntropies();
        FillUsefulGuessesScrollArea();
    }
    // Close progress dialog
    progressDialog->close();
    // Reset cancel in game
    game->uncancelCalculations();
}

// CALLED WHEN FINISHED CALCULATING ENTROPY ONLY
void MainWindow::finishedCalcEntropy()
{
    // Disable mainwindow
    this->setEnabled(true);

    // If entropy wasn't cancelled fill useful words scroll area
    if (!game->getCancel())
    {
        FillUsefulGuessesScrollArea();
    }
    // Close progress dialog
    progressDialog->close();
    // Reset cancel in game
    game->uncancelCalculations();
}

// CALLED WHEN GAME WON
void MainWindow::GameWon()
{
    // Create message box
    QMessageBox msgBox;
    msgBox.setText(tr("You guessed correctly!"));
    msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    int btn = msgBox.exec();

    // Reset game or close msg box depending on which button is pressed
    switch(btn){
    case QMessageBox::Retry:
        Retry();
        break;
    case QMessageBox::Close:
        msgBox.close();
        break;
    }

}

// CALLED WHEN GAME LOST
void MainWindow::GameLost()
{
    // Create message box
    QMessageBox msgBox;
    msgBox.setText(tr("You lost!\nThe correct word was: "));
    msgBox.setInformativeText(QString::fromStdString(game->getCurrentAnswer().getContent()));
    msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    int btn = msgBox.exec();

    // Reset game or close msg box depending on which button is pressed
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
    // Remove current valid words
    delete ui->validAnswersScrollArea->widget();

    // Create layout and widget
    auto *innerWidget = new QWidget(ui->validAnswersScrollArea);
    auto *scrollLayout = new QGridLayout(innerWidget);

    // Align intems contained in layout in the centre (vertically & horizontally)
    scrollLayout->setAlignment(Qt::AlignCenter);
    scrollLayout->setContentsMargins(10,10,10,10);
    scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    // Set layout of inner widget
    innerWidget->setLayout(scrollLayout);
    // Fill valid words scroll area with inner widget
    ui->validAnswersScrollArea->setWidget(innerWidget);

    int row = 0;
    int col = 0;

    // Loop through all possible answers
    for (unsigned int i=0; i < game->getPossAnswerVector().size() ; i++)
    {
        // Check if that current possible answer is valid
        if (game->getPossAnswerVector()[i].getValid())
        {
            // Create label, fill with possible answer and add to scroll area layout
            auto *text = new QLabel();
            text->setText(QString::fromStdString(game->getPossAnswerVector()[i].getContent()));
            text->setContentsMargins(5,5,5,5);
            scrollLayout->addWidget(text,row,col);
            col++;

            // Fill scroll area 4 words to a row
            if (col > 3)
            {
                col = 0;
                row++;
            }
        }

    }
}


// INITIAL SETUP OF USEFUL Guesses SCROLL AREA
void MainWindow::FillUsefulGuessesScrollArea()
{
    // Remove current useful guesses
    delete ui->usefulGuessesScrollArea->widget();

    // Create layout and widget
    auto *innerWidget = new QWidget(ui->usefulGuessesScrollArea);
    auto *scrollLayout = new QGridLayout(innerWidget);

    // Align intems contained in layout in the centre (vertically & horizontally)
    scrollLayout->setAlignment(Qt::AlignCenter);
    scrollLayout->setContentsMargins(10,10,10,10);
    scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    // Set layout of inner widget
    innerWidget->setLayout(scrollLayout);
    // Fill valid words scroll area with inner widget
    ui->usefulGuessesScrollArea->setWidget(innerWidget);

    int row = 0;
    int col = 0;
    // Loop through all possible guesses (sorted by most useful)
    for (unsigned int i=0; i <game->getPossGuessVectorSorted().size() ; i++)
    {
        // Check if the current possible guess has not already been guessed
        if (!game->getPossGuessVectorSorted()[i].getGuessed())
        {
            // Create label, fill with possible guess and add to scroll area layout
            auto *text = new QLabel();
            text->setText(QString::fromStdString(game->getPossGuessVectorSorted()[i].getContent()));
            text->setContentsMargins(5,5,5,5);
            scrollLayout->addWidget(text,row,col);
            col++;
            // Fill scroll area 4 words to a row
            if (col > 3)
            {
                col = 0;
                row++;
            }
        }
        // Break from the loop when max words is reached
        // This is because the words are sorted by most useful and the ones towards the end are not useful
        // It will also save on loading times
        if (i > maxUsefulGuesses)
            break;
    }
}

// INITIAL SETUP OF LETTERSCONTAINER
void MainWindow::SetupLettersContainer()
{
    // Letter container geometry
    int width = std::stoi(settingsFile->get("NoOfCharacters"));
    int height = stoi(settingsFile->get("NoOfGuesses"));

//    lettersContainerWidth = std::stoi(settingsFile->get("NoOfCharacters"));
//    lettersContainerHeight = stoi(settingsFile->get("NoOfGuesses"));


    // Ensure the letter contiainer widths and height from the settings file
    // isn't less than 2 or larger than 10
    // if they are, recreate the settings file with default values
    // this saves a massive letter container from being created if the settings
    // file is manually edited
    if (height >= 2 && height <= 10)
        lettersContainerHeight = height;
    else
    {
        lettersContainerHeight = 5;
        settingsFile->CreateSettingsFile();
    }

    if (width >= 2 && width <= 10)
        lettersContainerWidth = width;
    else
    {
        lettersContainerWidth = 5;
        settingsFile->CreateSettingsFile();
    }

    // Create new letter container
    lettersContainer = new LettersContainer(lettersContainerWidth, lettersContainerHeight, ui->containerWidget);

    // Create box layout
    QHBoxLayout *boxlayout = new QHBoxLayout(ui->containerWidget);

    // Set containerwidget (created in designer) layout
    ui->containerWidget->setLayout(boxlayout);

    // Align contents centrally and add letter container to layout
    boxlayout->setAlignment(Qt::AlignCenter);
    boxlayout->addWidget(lettersContainer);

    // Set initial style of lettersContainer
    lettersContainer->highlightCurrentLetter();
    lettersContainer->updateLetterStyles();

    letterContainerLoaded = true;
}

// CALLED WHEN WORD IS ENTERED
void MainWindow::CheckWord()
{
    // Check if the word entered is in the guess list
    if (game->isValidGuess(lettersContainer->getCurrentWord())) {
        std::cout << "Valid!" << std::endl;

        // Get the colour vector of the current guess when compared to the current answer
        std::vector<uint8_t> colourVector = game->getGuessedVector()[game->getTotalGuesses()-1].getColourVector();

        // Update the current row with the colour vector
        lettersContainer->UpdateCurrentColours(colourVector);

        // If the guess is the answer => game won
        if (game->isCorrectGuess(lettersContainer->getCurrentWord()))
        {
            GameWon();
        }
        else{
            // If the user has not guessed the word in the no of guesses limit => game lost
            if (lettersContainer->getSelectedRow() >= lettersContainerHeight-1)
            {
                GameLost();
            }
            // If the guess is wrong but not run out of guesses
            // update valid answers, useful guess, fill scroll areas and increment row
            else{
                game->setValidAnswers();
                FillValidAnswersScrollArea();
                CalcEntropies();
                lettersContainer->incrementSelectedRow();
            }

        }
    }
    // If guess is invalid alert user by flashing the current row red
    else {
        std::cout << "Invalid!" << std::endl;
        lettersContainer->invalidGuess();
    }
}

// KEYPRESS HANDLER
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // If back space is pressed => remove letter and decrement selected letter
    if (event->key() == Qt::Key_Backspace)
    {
        if (lettersContainer->getCurrentLetterText() == ' ')
        {
            lettersContainer->unhighlightCurrentLetter();
            lettersContainer->decrementSelectedColumn();
            lettersContainer->highlightCurrentLetter();
            lettersContainer->setCurrentLetterText(' ');
        }
        else
        {
            lettersContainer->setCurrentLetterText(' ');
        }

    }
    // If enter/return is pressed
    else if (event->key() == Qt::Key_Return)
    {
        this->CheckWord();
    }
    else
    {
        // Check if key pressed is a letter (eg not a number or symbol)
        if (event->key() >= 0x41 && event->key() <= 0x5a)
        {
            std::string keyStr = event->text().toStdString();
            char key = toupper(keyStr.c_str()[0]); // changed to uppercase

            // Set current letter widget text to pressed letter key
            // increment selected column and highlighted widget
            lettersContainer->setCurrentLetterText(key);
            lettersContainer->unhighlightCurrentLetter();
            lettersContainer->incrementSelectedColumn();
            lettersContainer->highlightCurrentLetter();
        }

    }
    // Update stylesheets of all widgets in lettersContainer
    lettersContainer->updateLetterStyles();
}


// OPEN SETTINGS MENU DIALOG
void MainWindow::OpenSettingsMenu()
{
    // Create settings menu and connect signal and slot
    settingsMenu settings(settingsFile, this);
    connect(&settings, SIGNAL(ok_signal()), this, SLOT(GetSettings()));
    connect(&settings, SIGNAL(cancel_signal()), this, SLOT(CancelSettings()));
    connect(&settings, SIGNAL(quit_signal()), this, SLOT(QuitSettings()));
    settings.exec(); // this function is blocking and so the mainwindow will not be accessible when this is open (as desired)
}

// CALLED WHEN SETTINGS OK BTN IS PRESSED
void MainWindow::GetSettings()
{
//    std::cout<<settingsFile->get("AnswerList")<<std::endl;
//    if (lettersContainer)
//        delete lettersContainer;

    try{
        delete lettersContainer;

    }
    catch(...)
    {
        std::cout<<"Couldn't delete letterscontainer."<<std::endl;
    }

    delete ui->containerWidget->layout();
    delete ui->validAnswersScrollArea->widget();

//    SetupLettersContainer();

    // Update game word lists

    game->setAnswerList(settingsFile->get("AnswerList"));
    game->setGuessList(settingsFile->get("GuessList"));
    game->setNumCharacters(stoi(settingsFile->get("NoOfCharacters")));
    game->setMaxGuesses(stoi(settingsFile->get("NoOfGuesses")));

    LoadWordLists();
//    game->readUnprocAnswers();
//    game->readUnprocGuesses();
    //Reset the game
    game->reset();
    game->randomAnswer();


}

void MainWindow::CancelSettings()
{
    if (!game->getAnswerListLoaded())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Answer List could not be loaded.\nPlease browse for one."));
        msgBox.exec();
        OpenSettingsMenu();
    }
    else{
        if (!game->getGuessListLoaded())
        {
            QMessageBox msgBox;
            msgBox.setText(tr("Guess List could not be loaded.\nPlease browse for one."));
            msgBox.exec();
            OpenSettingsMenu();
        }
        else
        {
            if (!game->getHasPrecomputerColours())
            {
                QMessageBox msgBox;
                msgBox.setText(tr("You must precompute colours."));
                msgBox.exec();
                OpenSettingsMenu();
            }
        }
    }

}

void MainWindow::QuitSettings()
{
    if (!game->getAnswerListLoaded())
    {
        // Create message box
        QMessageBox msgBox;
        msgBox.setText(tr("Answer list could not be loaded."));
        msgBox.setInformativeText(tr("Please browse for one."));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
        int btn = msgBox.exec();

        // Reset game or close msg box depending on which button is pressed
        switch(btn){
        case QMessageBox::Ok:
            OpenSettingsMenu();
            break;
        case QMessageBox::Close:
//            msgBox.close();
            qApp->exit();
            break;
        }
    }
    else{
        if (!game->getGuessListLoaded())
        {
            // Create message box
            QMessageBox msgBox;
            msgBox.setText(tr("Guess list could not be loaded."));
            msgBox.setInformativeText(tr("Please browse for one."));
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
            int btn = msgBox.exec();

            // Reset game or close msg box depending on which button is pressed
            switch(btn){
            case QMessageBox::Ok:
                OpenSettingsMenu();
                break;
            case QMessageBox::Close:
//                msgBox.close();
                qApp->exit();
                break;
            }
        }
        else
        {
            if (!game->getHasPrecomputerColours())
            {
                // Create message box
                QMessageBox msgBox;
                msgBox.setText(tr("You must precompute colours."));
                msgBox.setInformativeText(tr("Do you want to compute colours or quit?"));
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
                int btn = msgBox.exec();

                // Reset game or close msg box depending on which button is pressed
                switch(btn){
                case QMessageBox::Ok:
                    Precompute();
                    break;
                case QMessageBox::Close:
                    qApp->exit();
                    break;
                }
            }
        }
    }
}

void MainWindow::Translate()
{
    // Get selected language
    std::string language = settingsFile->get("Language");
    bool result = false;

    // Load the correct translator depending on selected language
    if (language == "English")
    {
        result = translator.load(":/lang_en.qm");
    }
    else if (language == "French")
    {
        result = translator.load(":/lang_fr.qm");
    }

    // If translator could be loaded install selected translator and update ui
    if (result)
    {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}
