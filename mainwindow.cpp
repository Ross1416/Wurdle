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

    // Setup UI
    ui->setupUi(this);
    ui->centralwidget->setContentsMargins(0,0,0,0);
    ui->wurdleTitleLabel->setContentsMargins(0,0,0,0);

    // Setup game
    game->setAnswerList(settingsFile->get("AnswerList"));
    game->setGuessList(settingsFile->get("GuessList"));
    game->setNumCharacters(stoi(settingsFile->get("NoOfCharacters")));
    game->readUnprocAnswers();
    game->readUnprocGuesses();
    game->reset();
    game->randomAnswer();

    // Translate
    Translate();

    // Setup letter container
    SetupLetterContainer();

    // Compute colours and entropy in another thread
    Precompute();

    // SIGNALS AND SLOTS CONNECTIONS
    connect(ui->actionSettings, &QAction::triggered,this, &MainWindow::OpenSettingsMenu);
    connect(ui->actionReset, &QAction::triggered,this, &MainWindow::Retry);

    connect(game, SIGNAL(precomputeColorsSignal(int)), this, SLOT(updateGenerateUsefulWordsColoursProgress(int)));
    connect(game, SIGNAL(calcEntropySignal(int)), this, SLOT(updateGenerateUsefulWordsEntropyProgress(int)));
}

// MAINWINDOW DESTRUCTOR
MainWindow::~MainWindow()
{
    delete ui;
}

// RETRY FUNCTION
void MainWindow::Retry()
{
    // Reset game
    game->reset();
    game->randomAnswer();

    // Delete ui elements to allow them to be replaced
    delete ui->containerWidget->layout();
    delete ui->validAnswersScrollArea->widget();
    delete ui->usefulWordsScrollArea->widget();

    // Setup letter container
    SetupLetterContainer();


    if (game->getHasPrecomputerColours())
    {
        std::cout<<"has pre"<<std::endl;
        if (game->getHasInitialEntropy())
        {
            std::cout<<"has en"<<std::endl;
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

// PRECOMPUTE COLOURS AND ENTROPY ASYNCHRONOUSLY
void MainWindow::Precompute()
{
    // Delete useful words scroll area
    delete ui->usefulWordsScrollArea->widget();

    // Disable mainwindow so nothing can be changed while loading
    this->setEnabled(false);

    // Setup progress dialog
    progressDialog = new QProgressDialog("Precomputing colours...", "Abort", 0, 100,this);
    connect(progressDialog, SIGNAL(canceled()), this, SLOT(CancelGenerateUsefulWords()));
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
        delete ui->usefulWordsScrollArea->widget();

        // Disable mainwindow so nothing can be changed while loading
        this->setEnabled(false);

        // Setup progress dialog
        progressDialog = new QProgressDialog("Calculating entropies...", "Abort", 0, 100, this);
        connect(progressDialog, SIGNAL(canceled()), this, SLOT(CancelGenerateUsefulWords()));
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
void MainWindow::updateGenerateUsefulWordsColoursProgress(int percent)
{
    progressDialog->setLabelText("Precomputing colours...");
    progressDialog->setValue(percent);
}

// UPDATE PROGRESS BAR FOR CALCULATING ENTROPY
void MainWindow::updateGenerateUsefulWordsEntropyProgress(int percent)
{
    progressDialog->setLabelText("Calculating entropy...");
    progressDialog->setValue(percent);
}

// CANCEL ENTROPY CALCULATIONS
void MainWindow::CancelGenerateUsefulWords()
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
        FillUsefulWordsScrollArea();
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
        FillUsefulWordsScrollArea();
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
    msgBox.setText(tr("You lost!"));
    std::string text = "The correct word was " + game->getCurrentAnswer().getContent();
    msgBox.setInformativeText(QString::fromStdString(text));
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


// INITIAL SETUP OF USEFUL WORDS SCROLL AREA
void MainWindow::FillUsefulWordsScrollArea()
{
    // Remove current useful words
    delete ui->usefulWordsScrollArea->widget();

    // Create layout and widget
    auto *innerWidget = new QWidget(ui->usefulWordsScrollArea);
    auto *scrollLayout = new QGridLayout(innerWidget);

    // Align intems contained in layout in the centre (vertically & horizontally)
    scrollLayout->setAlignment(Qt::AlignCenter);
    scrollLayout->setContentsMargins(10,10,10,10);
    scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    // Set layout of inner widget
    innerWidget->setLayout(scrollLayout);
    // Fill valid words scroll area with inner widget
    ui->usefulWordsScrollArea->setWidget(innerWidget);

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
        if (i > maxUsefulWords)
            break;
    }
}

// INITIAL SETUP OF LETTERCONTAINER
void MainWindow::SetupLetterContainer()
{
    // Letter container geometry
    int width = std::stoi(settingsFile->get("NoOfCharacters"));
    int height = stoi(settingsFile->get("NoOfGuesses"));

    if (height >= 2 && height <= 10)
        letterContainerHeight = height;
    else
    {
        letterContainerHeight = 5;
        settingsFile->CreateSettingsFile();
    }

    if (width >= 2 && width <= 10)
        letterContainerWidth = width;
    else
    {
        letterContainerWidth = 5;
        settingsFile->CreateSettingsFile();
    }

    // Create new letter container


    letterContainer = new LettersContainer(letterContainerWidth, letterContainerHeight, ui->containerWidget);

    // Create box layout
    QHBoxLayout *boxlayout = new QHBoxLayout(ui->containerWidget);

    // Set containerwidget (created in designer) layout
    ui->containerWidget->setLayout(boxlayout);

    // Align contents centrally and add letter container to layout
    boxlayout->setAlignment(Qt::AlignCenter);
    boxlayout->addWidget(letterContainer);

    // Set initial style of lettercontainer
    letterContainer->highlightCurrentLetter();
    letterContainer->updateLetterStyles();
}

// CALLED WHEN WORD IS ENTERED
void MainWindow::CheckWord()
{
    // Check if the word entered is in the guess list
    if (game->isValidGuess(letterContainer->getCurrentWord())) {
        std::cout << "Valid!" << std::endl;

        // Get the colour vector of the current guess when compared to the current answer
        std::vector<uint8_t> colourVector = game->getGuessedVector()[game->getTotalGuesses()-1].getColourVector();

        // Update the current row with the colour vector
        letterContainer->UpdateCurrentColours(colourVector);

        // If the guess is the answer => game won
        if (game->isCorrectGuess(letterContainer->getCurrentWord()))
        {
            GameWon();
        }
        else{
            // If the user has not guessed the word in the no of guesses limit => game lost
            if (letterContainer->getSelectedRow() >= letterContainerHeight-1)
            {
                GameLost();
            }
            // If the guess is wrong but not run out of guesses
            // update valid answers, useful guess, fill scroll areas and increment row
            else{
                game->setValidAnswers();
                FillValidAnswersScrollArea();
                CalcEntropies();
                letterContainer->incrementSelectedRow();
            }

        }
    }
    // If guess is invalid alert user by flashing the current row red
    else {
        std::cout << "Invalid!" << std::endl;
        letterContainer->invalidGuess();
    }
}

// KEYPRESS HANDLER
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // If back space is pressed => remove letter and decrement selected letter
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
            letterContainer->setCurrentLetterText(key);
            letterContainer->unhighlightCurrentLetter();
            letterContainer->incrementSelectedColumn();
            letterContainer->highlightCurrentLetter();
        }

    }
    // Update stylesheets of all widgets in lettercontainer
    letterContainer->updateLetterStyles();
}


// OPEN SETTINGS MENU DIALOG
void MainWindow::OpenSettingsMenu()
{
    // Create settings menu and connect signal and slot
    settingsMenu *settings = new settingsMenu(settingsFile, this);
    connect(settings, SIGNAL(ok_signal()), this, SLOT(GetSettings()));
    connect(settings, SIGNAL(cancel_signal()), this, SLOT(CancelSettings()));
    connect(settings, SIGNAL(quit_signal()), this, SLOT(QuitSettings()));
    settings->exec(); // this function is blocking and so the mainwindow will not be accessible when this is open (as desired)
}

// CALLED WHEN SETTINGS OK BTN IS PRESSED
void MainWindow::GetSettings()
{
    // Update game word lists
    game->setAnswerList(settingsFile->get("AnswerList"));
    game->setGuessList(settingsFile->get("GuessList"));
    game->setNumCharacters(stoi(settingsFile->get("NoOfCharacters")));
    game->readUnprocAnswers();
    game->readUnprocGuesses();
    //Reset the game
    game->reset();
    game->randomAnswer();

    // Precompute colours and entropy
    Precompute();


    // Update lettercontainer geometry
    // Letter container geometry
//    delete letterContainer;
    delete ui->containerWidget->layout();
    delete ui->validAnswersScrollArea->widget();
    SetupLetterContainer();

    // Translate UI
    Translate();
}

void MainWindow::CancelSettings()
{
    if (!game->getHasPrecomputerColours())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("You must precompute colours."));
        msgBox.exec();
        OpenSettingsMenu();
    }
}

void MainWindow::QuitSettings()
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
            msgBox.close();
            qApp->quit();
            break;
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
//        t.load("C:/Users/ringl/Desktop/Uni Classes/Y2S2/EE273/Project/Wurdle-QT/Wurdle/lang_en.qm");
        result = translator.load(":/lang_en.qm");
    }
    else if (language == "French")
    {
//        t.load("C:/Users/ringl/Desktop/Uni Classes/Y2S2/EE273/Project/Wurdle-QT/Wurdle/lang_fr.qm");
        result = translator.load(":/lang_fr.qm");
    }

    // If translator could be loaded install selected translator and update ui
    if (result)
    {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}
