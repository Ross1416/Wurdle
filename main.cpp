// mainwindow.cpp
// Author: Angus Mulligan & Ross Inglis
// Last modified: 17/04/22


#include <QApplication>

#include "mainwindow.h"
#include "game.h"
#include "settingsmenu.h"

int main(int argc, char *argv[])
{
    Game currentGame(5, 6); // A game object is initialised with the default number
                            // of characters 5 and the default max guesses 6

    // Initialise settings file
    SettingsFileHandler settingsFile("settings.txt");
    settingsFile.read();

    // Initialise QT application
    QApplication app(argc, argv);

    // Initialise MainWindow
    MainWindow window(&currentGame, &settingsFile);

    window.show();
    return app.exec();
}



