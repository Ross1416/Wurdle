#include <QApplication>

#include "mainwindow.h"
#include "game.h"
#include "settingsmenu.h"

int main(int argc, char *argv[])
{
    Game currentGame(5, 6); // A game object is initialised with the default number
                            // of characters 5 and the default max guesses 6

    // Initialise settings file
    SettingsFileHandler settingsFile = SettingsFileHandler("settings.txt");
    settingsFile.read();

    // Initialise QT application
    QApplication a(argc, argv);

    // Initialise MainWindow
    MainWindow w(&currentGame, &settingsFile);
    w.show();
    return a.exec();
}



