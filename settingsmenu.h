#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

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

private:
    Ui::settingsMenu *ui;

public slots:
    void browseForAnswerList();
    void browseForGuessList();
};

#endif // SETTINGSMENU_H
