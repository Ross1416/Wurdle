#include "mainwindow.h"
#include <QApplication>

#include "game.h"
#include "settingsmenu.h"
#include <iostream>
//#include<QTranslator>


int main(int argc, char *argv[])
{
    Game currentGame(5, 6); //A game object is initialised with the default number of characters 5 and the default max guesses 6
    QApplication a(argc, argv);


//    QTranslator t;
//    t.load("C:/Users/ringl/Desktop/Uni Classes/Y2S2/EE273/Project/Wurdle-QT/Wurdle/lang_fr.qm");
//    a.installTranslator(&t);
    //std::cout << currentGame.getNumCharacters() << std::endl;

    // I'm messing with your files, I'm a file goblin.
    //nice


    SettingsFileHandler settingsFile = SettingsFileHandler("settings.txt");
    settingsFile.read();

    MainWindow w(&currentGame, &settingsFile);
    w.show();
    return a.exec();

}
