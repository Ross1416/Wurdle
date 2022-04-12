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

    // Lettercontainer variables
    LettersContainer *letterContainer;
    int letterContainerWidth;
    int letterContainerHeight;
    // Max useful words to display
    unsigned int maxUsefulWords = 100;

    // QT Translator
    QTranslator translator;

    // Progress/threading variables
    QProgressDialog* progressDialog;
    QTimer* progressTimer;
    QFutureWatcher<void> watcher;

    // Settings
    SettingsFileHandler* settingsFile;

public:

    // CONSTRUCTOR/DESTRUCTOR
    MainWindow(Game* currentGame, SettingsFileHandler*, QWidget *parent = nullptr);
    ~MainWindow();

    // FILL SCROLL AREAS
    void FillValidAnswersScrollArea();
    void FillUsefulWordsScrollArea();

    // SETUP LETTER CONTAINER
    void SetupLetterContainer(int, int);

    // ENTERED WORD
    void CheckWord();

    // OVERRIDE QT KEY PRESS EVENT FUNCTION
    void keyPressEvent(QKeyEvent *event);

    // UPDATE
    void Update();

    // GAME
    void GameWon();
    void GameLost();
    void Retry();

    // COMPUTATION FUNCTIONS
    void Precompute();
    void CalcEntropies();

    // TRANSLATE UI
    void Translate();

// slots can recieve QT signals
public slots:
    // SETTINGS
    void OpenSettingsMenu();
    void GetSettings();

    // UPDATE PROGRESS BAR
    void updateGenerateUsefulWordsColoursProgress(int colourPercent);
    void updateGenerateUsefulWordsEntropyProgress(int colourPercent);

    // COMPUTATION FUNCTIONS ENDED
    void CancelGenerateUsefulWords();
    void finishedPrecompute();
    void finishedCalcEntropy();
};

#endif // MAINWINDOW_H
