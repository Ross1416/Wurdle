#include "settingsmenu.h"
#include "ui_settingsmenu.h"
#include<QFileDialog>
#include<iostream>

settingsMenu::settingsMenu(std::map<std::string,std::string> settingsMap, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsMenu)
{

    ui->setupUi(this);

    settings = settingsMap;
//    settingsFile = SettingsFileHandler("C:/Users/ringl/Desktop/Uni Classes/Y2S2/EE273/Project/Wurdle-QT/Wurdle/settings.txt");
//    settingsFile = SettingsFileHandler("settings.txt");
//    settings = settingsFile.read();
    Setup();

    // SET DIALOG BUTTONS SO THEY'RE TRANSLATABLE
    ui->dialogBtnBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->dialogBtnBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

    // SIGNALS AND SLOTS CONNECTIONS
    connect(ui->answerListBrowseBtn, &QPushButton::clicked, this, &settingsMenu::browseForAnswerList);
    connect(ui->guessListBrowseBtn, &QPushButton::clicked, this, &settingsMenu::browseForGuessList);
    connect(ui->dialogBtnBox, &QDialogButtonBox::accepted, this, &settingsMenu::ok);
}
settingsMenu::~settingsMenu()
{
    delete ui;
}

//void settingsMenu::changeEvent(QEvent *event) {
//    if (event->type() == QEvent::LanguageChange) {
//        setWindowTitle(tr("Settings"));
//        ui->retranslateUi(this);

//    }
//    else {
//        QWidget::changeEvent(event);
//    }
//}

void settingsMenu::Setup()
{
    ui->answerListLineEdit->setText(QString::fromStdString(settings["AnswerList"]));
    ui->guessListLineEdit->setText(QString::fromStdString(settings["GuessList"]));
    ui->noGuessesSpinBox->setValue(stoi(settings["NoOfGuesses"]));

    // LANGUAGES
    ui->languageComboBox->addItem(tr("English"));
    ui->languageComboBox->addItem(tr("French"));
    ui->languageComboBox->setCurrentText(QString::fromStdString(settings["Language"]));
}

// SIGNAL THAT EMITS SETTINGS WHEN OK BTN PRESSED
void settingsMenu::ok()
{
    settings["AnswerList"] = ui->answerListLineEdit->text().toStdString();
    settings["GuessList"] = ui->guessListLineEdit->text().toStdString();
    settings["NoOfGuesses"] = std::to_string(ui->noGuessesSpinBox->value());
    settings["Language"] = ui->languageComboBox->currentText().toStdString();
    settingsFile.write(settings);

    emit ok_signal(ui->answerListLineEdit->text().toStdString(), ui->guessListLineEdit->text().toStdString(), ui->noGuessesSpinBox->value(), ui->languageComboBox->currentText().toStdString());
}

void settingsMenu::browseForAnswerList()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose answer list"), QDir().absolutePath(),"Text files (*.txt)");
    if (fileName != "")
        ui->answerListLineEdit->setText(fileName);
}

void settingsMenu::browseForGuessList()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose guess list"), QDir().absolutePath(),"Text files (*.txt)");
    if (fileName != "")
        ui->guessListLineEdit->setText(fileName);
}





