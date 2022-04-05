#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H
#include"mainwindow.h"
#include <QDialog>

namespace Ui {
class settingsMenu;
}

class settingsMenu : public QDialog
{
    Q_OBJECT

public:
    explicit settingsMenu(QWidget *parent = nullptr);
    ~settingsMenu();
    void ok();

private:
    Ui::settingsMenu *ui;

public slots:
    void browseForAnswerList();
    void browseForGuessList();

signals:
    void ok_signal(int);
};

#endif // SETTINGSMENU_H
