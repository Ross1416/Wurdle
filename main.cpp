#include "mainwindow.h"
#include <QApplication>

#include "game.h"
#include <iostream>
//#include<QTranslator>

int main(int argc, char *argv[])
{
    Game currentGame(5, 6);
    QApplication a(argc, argv);


//    QTranslator t;
//    t.load("C:/Users/ringl/Desktop/Uni Classes/Y2S2/EE273/Project/Wurdle-QT/Wurdle/lang_fr.qm");
//    a.installTranslator(&t);
    //std::cout << currentGame.getNumCharacters() << std::endl;

    // I'm messing with your files, I'm a file goblin.
    //nice

    MainWindow w(&currentGame);
    w.show();
    return a.exec();

}
