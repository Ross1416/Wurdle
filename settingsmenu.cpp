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
    connect(ui->dialogBtnBox, &QDialogButtonBox::accepted, this, &settingsMenu::ok);
//    connect(ui->dialogBtnBox, &QDialogButtonBox::accepted, this, ok_);
}

settingsMenu::~settingsMenu()
{
    delete ui;
}

void settingsMenu::ok()
{
    emit ok_signal(ui->noGuessesSpinBox->value());
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





