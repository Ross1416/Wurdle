#include "settingsmenu.h"
#include "ui_settingsmenu.h"

#include<iostream>

// CONSTRUCTOR
settingsMenu::settingsMenu(SettingsFileHandler* settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsMenu)
{
    // Setup ui
    ui->setupUi(this);

    // Assign settings file handler to member variable
    this->settingsFile = settings;

    // Set settings menu ui elements to the values in the settings file
    Setup();

    // Set dialog buttons so they are translatable
    ui->dialogBtnBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->dialogBtnBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

    // SIGNALS AND SLOTS CONNECTIONS
    connect(ui->answerListBrowseBtn, &QPushButton::clicked, this, &settingsMenu::browseForAnswerList);
    connect(ui->guessListBrowseBtn, &QPushButton::clicked, this, &settingsMenu::browseForGuessList);
    connect(ui->dialogBtnBox, &QDialogButtonBox::accepted, this, &settingsMenu::ok);
    connect(ui->dialogBtnBox, &QDialogButtonBox::rejected, this, &settingsMenu::cancel);
}

// DESTRUCTOR
settingsMenu::~settingsMenu()
{
    delete ui;
}

// INITIAL SETUP
void settingsMenu::Setup()
{
    // WORD LISTS AND GAME SETTINGS
    ui->answerListLineEdit->setText(QString::fromStdString(settingsFile->get("AnswerList")));
    ui->guessListLineEdit->setText(QString::fromStdString(settingsFile->get("GuessList")));
    ui->noGuessesSpinBox->setValue(stoi(settingsFile->get("NoOfGuesses")));
    ui->noCharactersSpinBox->setValue(stoi(settingsFile->get("NoOfCharacters")));

    // LANGUAGES
    ui->languageComboBox->addItem("English");
    ui->languageComboBox->addItem("French");
    ui->languageComboBox->setCurrentText(QString::fromStdString(settingsFile->get("Language")));
}

// WRITE NEW SETTINGS TO FILE AND EMIT SIGNAL (to mainwindow)
void settingsMenu::ok()
{
    settingsFile->set("AnswerList", ui->answerListLineEdit->text().toStdString());
    settingsFile->set("GuessList", ui->guessListLineEdit->text().toStdString());
    settingsFile->set("NoOfGuesses", std::to_string(ui->noGuessesSpinBox->value()));
    settingsFile->set("Language", ui->languageComboBox->currentText().toStdString());
    settingsFile->set("NoOfCharacters", std::to_string(ui->noCharactersSpinBox->value()));

    settingsFile->write();

    emit ok_signal();
}

void settingsMenu::cancel()
{
    emit cancel_signal();
}

void settingsMenu::closeEvent(QCloseEvent *event)
{
    event->accept();
    this->close();
    emit quit_signal();

}

// POP UP FILE BROWSER FOR ANSWER LIST
void settingsMenu::browseForAnswerList()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose answer list"), QDir().absolutePath(),"Text files (*.txt)");
    if (fileName != "")
        ui->answerListLineEdit->setText(fileName);
}

// POP UP FILE BROWSER FOR GUESS LIST
void settingsMenu::browseForGuessList()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose guess list"), QDir().absolutePath(),"Text files (*.txt)");
    if (fileName != "")
        ui->guessListLineEdit->setText(fileName);
}





