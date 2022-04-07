#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGridLayout>
#include<QKeyEvent>
#include<iostream>
#include<QTranslator>
#include<QMessagebox>

#include"letterwidget.h"
#include "letterscontainer.h"

#include "guessWord.h"
#include "game.h"
#include "settingsfilehandler.h"

//#include <QtConcurrent>
//#include <QFuture>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Game* currentGame, QWidget *parent = nullptr);
    ~MainWindow();


    void FillValidWordsScrollArea();
    void FillUsefulWordsScrollArea();
    void SetupLetterContainer(int, int);

    void CheckWord();

    void keyPressEvent(QKeyEvent *event);
    void Update();


    void GameWon();
    void Retry();
private:
    Ui::MainWindow *ui;
    Game *game;
    LettersContainer *letterContainer;
    int letterContainerWidth;
    int letterContainerHeight;
    QTranslator translator;

    SettingsFileHandler settingsFile;
    std::map<std::string,std::string> settings;


public slots:

    void OpenSettingsMenu();
    void GetSettings(std::string, std::string, int, std::string);


};

#endif // MAINWINDOW_H
