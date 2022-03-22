#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // I'm messing with your files, I'm a file goblin.
    //nice
    return a.exec();

}
