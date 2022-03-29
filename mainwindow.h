#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include"letterwidget.h"
#include "letterscontainer.h"

#include "guessWord.h"
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Game& currentGame, QWidget *parent = nullptr);
    ~MainWindow();

    LettersContainer *letterContainer;

    void SetupValidWordsScrollArea();
    void SetupUsefulWordsScrollArea();
    void SetupLetterContainer(int, int);

    void CheckWord();

    void keyPressEvent(QKeyEvent *event);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
