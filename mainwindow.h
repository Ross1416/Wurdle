#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGridLayout>
#include<QKeyEvent>
#include<iostream>
#include<QTranslator>
#include<QMessagebox>
#include <QProgressDialog>
#include<QTimer>

#include"letterwidget.h"
#include "letterscontainer.h"

#include "guessWord.h"
#include "game.h"
#include "settingsfilehandler.h"

#include <QtConcurrent>
#include <QFuture>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Game* currentGame, SettingsFileHandler*, QWidget *parent = nullptr);
    ~MainWindow();


    void FillValidAnswersScrollArea();
    void FillUsefulWordsScrollArea();
    void SetupLetterContainer(int, int);

    void CheckWord();

    void keyPressEvent(QKeyEvent *event);
    void Update();


    void GameWon();
    void Retry();
    void GameLost();
//    void GenerateUsefulWords();

    void Precompute();
    void CalcEntropies();

private:
    Ui::MainWindow *ui;
    Game *game;
    LettersContainer *letterContainer;
    int letterContainerWidth;
    int letterContainerHeight;
    unsigned int maxUsefulWords = 100;
    QTranslator translator;

    QProgressDialog* progressDialog;
    QTimer* progressTimer;
    QFutureWatcher<void> watcher;
//    bool initial;

    SettingsFileHandler* settingsFile;
//    std::map<std::string,std::string> settings;


public slots:

    void OpenSettingsMenu();
    void GetSettings();
    void updateGenerateUsefulWordsColoursProgress(int colourPercent);
    void updateGenerateUsefulWordsEntropyProgress(int colourPercent);
    void CancelGenerateUsefulWords();
    void finishedUsefulWordsGeneration();


};

#endif // MAINWINDOW_H
