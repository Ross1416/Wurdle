#include "settingsmenu.h"
#include "ui_settingsmenu.h"
#include<QFileDialog>
#include<iostream>

settingsMenu::settingsMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsMenu)
{
    ui->setupUi(this);

    // SIGNALS AND SLOTS CONNECTIONS
    connect(ui->answerListBrowseBtn, &QPushButton::clicked, this, &settingsMenu::browseForAnswerList);
    connect(ui->guessListBrowseBtn, &QPushButton::clicked, this, &settingsMenu::browseForGuessList);
    connect(ui->dialogBtnBox, &QDialogButtonBox::accepted, this, &settingsMenu::ok);
}

settingsMenu::~settingsMenu()
{
    delete ui;
}

// SIGNAL THAT EMITS SETTINGS WHEN OK BTN PRESSED
void settingsMenu::ok()
{
    emit ok_signal(ui->answerListLineEdit->text().toStdString(), ui->guessListLineEdit->text().toStdString(), ui->noGuessesSpinBox->value());
}

void settingsMenu::browseForAnswerList()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose answer list", "/","Text files (*.txt)");
    ui->answerListLineEdit->setText(fileName);
}

void settingsMenu::browseForGuessList()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose answer list", "/","Text files (*.txt)");
    ui->guessListLineEdit->setText(fileName);
}





