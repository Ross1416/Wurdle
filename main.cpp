#include "mainwindow.h"
#include <QApplication>

#include "game.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Game currentGame(5, 6); //A game object is initialised with the default number of characters 5 and the default max guesses 6
    QApplication a(argc, argv);
    MainWindow w(&currentGame);
    w.show();
    //std::cout << currentGame.getNumCharacters() << std::endl;

    // I'm messing with your files, I'm a file goblin.
    //nice

    return a.exec();

}
