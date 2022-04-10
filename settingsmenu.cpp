#include "settingsmenu.h"
#include "ui_settingsmenu.h"
#include<QFileDialog>
#include<iostream>

settingsMenu::settingsMenu(SettingsFileHandler* settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsMenu)
{

    ui->setupUi(this);

    this->settingsFile = settings;
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
    ui->answerListLineEdit->setText(QString::fromStdString(settingsFile->get("AnswerList")));
    ui->guessListLineEdit->setText(QString::fromStdString(settingsFile->get("GuessList")));
    ui->noGuessesSpinBox->setValue(stoi(settingsFile->get("NoOfGuesses")));

    // LANGUAGES
    ui->languageComboBox->addItem(tr("English"));
    ui->languageComboBox->addItem(tr("French"));
    ui->languageComboBox->setCurrentText(QString::fromStdString(settingsFile->get("Language")));
}

// SIGNAL THAT EMITS SETTINGS WHEN OK BTN PRESSED
void settingsMenu::ok()
{
    settingsFile->set("AnswerList", ui->answerListLineEdit->text().toStdString());
    settingsFile->set("GuessList", ui->guessListLineEdit->text().toStdString());
    settingsFile->set("NoOfGuesses", std::to_string(ui->noGuessesSpinBox->value()));
    settingsFile->set("Language", ui->languageComboBox->currentText().toStdString());

    settingsFile->write();

//    emit ok_signal(ui->answerListLineEdit->text().toStdString(), ui->guessListLineEdit->text().toStdString(), ui->noGuessesSpinBox->value(), ui->languageComboBox->currentText().toStdString());
    emit ok_signal();
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





