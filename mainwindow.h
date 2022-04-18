// mainwindow.h
// Author: Ross Inglis
// Last modified: 18/04/22


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// QT INCLUDES
#include<QMainWindow>
#include<QGridLayout>
#include<QKeyEvent>
#include<QTranslator>
#include<QMessageBox>
#include<QProgressDialog>
#include<QTimer>

// QT THREADING INCLUDES
#include <QtConcurrent>
#include <QFuture>

#include"letterwidget.h"
#include "letterscontainer.h"
#include "guessWord.h"
#include "game.h"
#include "settingsfilehandler.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    Game *game;

    // lettersContainer variables
    LettersContainer *lettersContainer;
    int lettersContainerWidth;
    int lettersContainerHeight;
    // Max useful words to display
    unsigned int maxUsefulGuesses = 100;

    // QT Translator
    QTranslator translator;

    // Progress/threading variables
    QProgressDialog* progressDialog;
    QFutureWatcher<void> watcher;

    bool letterContainerLoaded;

    // Settings
    SettingsFileHandler* settingsFile;

public:

    // CONSTRUCTOR/DESTRUCTOR
    MainWindow(Game* currentGame, SettingsFileHandler*, QWidget *parent = nullptr);
    ~MainWindow();

    // FILL SCROLL AREAS
    void FillValidAnswersScrollArea();
    void FillUsefulGuessesScrollArea();

    // SETUP LETTER CONTAINER
    void SetupLettersContainer();

    // ENTERED WORD
    void CheckWord();

    // OVERRIDE QT KEY PRESS EVENT FUNCTION
    void keyPressEvent(QKeyEvent *event);

    // GAME
    void GameWon();
    void GameLost();
    void Retry();

    // COMPUTATION FUNCTIONS
    void Precompute();
    void CalcEntropies();

    // TRANSLATE UI
    void Translate();

    // Load Word lists while checking for errors
    void LoadWordLists();
    // slots can recieve QT signals

public slots:
    // SETTINGS
    void OpenSettingsMenu();
    void GetSettings();
    void CancelSettings();
    void QuitSettings();


    // UPDATE PROGRESS BAR
    void updateGenerateUsefulGuessesColoursProgress(int colourPercent);
    void updateGenerateUsefulGuessesEntropyProgress(int colourPercent);

    // COMPUTATION FUNCTIONS ENDED
    void CancelGenerateUsefulGuesses();
    void finishedPrecompute();
    void finishedCalcEntropy();
};

#endif // MAINWINDOW_H
