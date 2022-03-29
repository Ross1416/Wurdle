#include "settingsmenu.h"
#include "ui_settingsmenu.h"
#include<QFileDialog>
#include<iostream>

settingsMenu::settingsMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsMenu)
{
    ui->setupUi(this);

    connect(ui->answerListBrowseBtn, &QPushButton::clicked, this, &settingsMenu::browseForAnswerList);
    connect(ui->guessListBrowseBtn, &QPushButton::clicked, this, &settingsMenu::browseForGuessList);
}

settingsMenu::~settingsMenu()
{
    delete ui;
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


