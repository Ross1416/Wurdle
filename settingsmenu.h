#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include<QDialog>
#include<QFileDialog>

#include"mainwindow.h"
#include"settingsfilehandler.h"

namespace Ui {
class settingsMenu;
}

class settingsMenu : public QDialog
{
    Q_OBJECT

public:
    settingsMenu(SettingsFileHandler* settingsFile, QWidget *parent = nullptr);
    ~settingsMenu();
    void ok();
    void cancel();
    void closeEvent(QCloseEvent *event);
    void Setup();
private:
    Ui::settingsMenu *ui;
    SettingsFileHandler* settingsFile;
//    std::map<std::string,std::string> settings;

public slots:
    void browseForAnswerList();
    void browseForGuessList();

signals:
    void ok_signal();
    void cancel_signal();
    void quit_signal();
};

#endif // SETTINGSMENU_H
