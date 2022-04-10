#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H
#include"mainwindow.h"
#include <QDialog>
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

    void Setup();
//    void changeEvent(QEvent *event);
private:
    Ui::settingsMenu *ui;
    SettingsFileHandler* settingsFile;
//    std::map<std::string,std::string> settings;

public slots:
    void browseForAnswerList();
    void browseForGuessList();

signals:
    void ok_signal();
};

#endif // SETTINGSMENU_H
