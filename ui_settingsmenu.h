/********************************************************************************
** Form generated from reading UI file 'settingsmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

// ui_settingsmenu.h
// Author: Ross Ingis
// Last modified: 19/04/22

#ifndef UI_SETTINGSMENU_H
#define UI_SETTINGSMENU_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_settingsMenu
{
public:
    QDialogButtonBox *dialogBtnBox;
    QPushButton *guessListBrowseBtn;
    QPushButton *answerListBrowseBtn;
    QLineEdit *guessListLineEdit;
    QLineEdit *answerListLineEdit;
    QLabel *guessListLabel;
    QLabel *answerListLabel;
    QFrame *wordListsSelectionLine;
    QLabel *wordListSelectionHeaderLabel;
    QFrame *gameSettingsLine;
    QLabel *gameSettingsHeaderLabel;
    QLabel *noGuessesLabel;
    QLabel *noCharactersLabel;
    QSpinBox *noGuessesSpinBox;
    QSpinBox *noCharactersSpinBox;
    QComboBox *languageComboBox;
    QLabel *languageLabel;

    void setupUi(QDialog *settingsMenu)
    {
        if (settingsMenu->objectName().isEmpty())
            settingsMenu->setObjectName(QString::fromUtf8("settingsMenu"));
        settingsMenu->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(settingsMenu->sizePolicy().hasHeightForWidth());
        settingsMenu->setSizePolicy(sizePolicy);
        settingsMenu->setMinimumSize(QSize(600, 400));
        settingsMenu->setMaximumSize(QSize(600, 400));
        dialogBtnBox = new QDialogButtonBox(settingsMenu);
        dialogBtnBox->setObjectName(QString::fromUtf8("dialogBtnBox"));
        dialogBtnBox->setGeometry(QRect(420, 360, 161, 32));
        dialogBtnBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        dialogBtnBox->setOrientation(Qt::Horizontal);
        dialogBtnBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        guessListBrowseBtn = new QPushButton(settingsMenu);
        guessListBrowseBtn->setObjectName(QString::fromUtf8("guessListBrowseBtn"));
        guessListBrowseBtn->setGeometry(QRect(450, 60, 100, 25));
        answerListBrowseBtn = new QPushButton(settingsMenu);
        answerListBrowseBtn->setObjectName(QString::fromUtf8("answerListBrowseBtn"));
        answerListBrowseBtn->setGeometry(QRect(450, 100, 100, 25));
        guessListLineEdit = new QLineEdit(settingsMenu);
        guessListLineEdit->setObjectName(QString::fromUtf8("guessListLineEdit"));
        guessListLineEdit->setGeometry(QRect(80, 60, 350, 25));
        sizePolicy.setHeightForWidth(guessListLineEdit->sizePolicy().hasHeightForWidth());
        guessListLineEdit->setSizePolicy(sizePolicy);
        answerListLineEdit = new QLineEdit(settingsMenu);
        answerListLineEdit->setObjectName(QString::fromUtf8("answerListLineEdit"));
        answerListLineEdit->setGeometry(QRect(80, 100, 350, 25));
        sizePolicy.setHeightForWidth(answerListLineEdit->sizePolicy().hasHeightForWidth());
        answerListLineEdit->setSizePolicy(sizePolicy);
        guessListLabel = new QLabel(settingsMenu);
        guessListLabel->setObjectName(QString::fromUtf8("guessListLabel"));
        guessListLabel->setGeometry(QRect(10, 60, 51, 20));
        answerListLabel = new QLabel(settingsMenu);
        answerListLabel->setObjectName(QString::fromUtf8("answerListLabel"));
        answerListLabel->setGeometry(QRect(10, 100, 61, 20));
        wordListsSelectionLine = new QFrame(settingsMenu);
        wordListsSelectionLine->setObjectName(QString::fromUtf8("wordListsSelectionLine"));
        wordListsSelectionLine->setGeometry(QRect(10, 40, 561, 16));
        QFont font;
        font.setPointSize(9);
        wordListsSelectionLine->setFont(font);
        wordListsSelectionLine->setLineWidth(2);
        wordListsSelectionLine->setFrameShape(QFrame::HLine);
        wordListsSelectionLine->setFrameShadow(QFrame::Sunken);
        wordListSelectionHeaderLabel = new QLabel(settingsMenu);
        wordListSelectionHeaderLabel->setObjectName(QString::fromUtf8("wordListSelectionHeaderLabel"));
        wordListSelectionHeaderLabel->setGeometry(QRect(10, 10, 141, 31));
        QFont font1;
        font1.setPointSize(11);
        wordListSelectionHeaderLabel->setFont(font1);
        gameSettingsLine = new QFrame(settingsMenu);
        gameSettingsLine->setObjectName(QString::fromUtf8("gameSettingsLine"));
        gameSettingsLine->setGeometry(QRect(10, 160, 561, 16));
        gameSettingsLine->setFrameShadow(QFrame::Sunken);
        gameSettingsLine->setLineWidth(3);
        gameSettingsLine->setMidLineWidth(0);
        gameSettingsLine->setFrameShape(QFrame::HLine);
        gameSettingsHeaderLabel = new QLabel(settingsMenu);
        gameSettingsHeaderLabel->setObjectName(QString::fromUtf8("gameSettingsHeaderLabel"));
        gameSettingsHeaderLabel->setGeometry(QRect(10, 130, 141, 31));
        gameSettingsHeaderLabel->setFont(font1);
        noGuessesLabel = new QLabel(settingsMenu);
        noGuessesLabel->setObjectName(QString::fromUtf8("noGuessesLabel"));
        noGuessesLabel->setGeometry(QRect(10, 180, 191, 16));
        noCharactersLabel = new QLabel(settingsMenu);
        noCharactersLabel->setObjectName(QString::fromUtf8("noCharactersLabel"));
        noCharactersLabel->setGeometry(QRect(10, 220, 121, 16));
        noGuessesSpinBox = new QSpinBox(settingsMenu);
        noGuessesSpinBox->setObjectName(QString::fromUtf8("noGuessesSpinBox"));
        noGuessesSpinBox->setGeometry(QRect(220, 180, 42, 22));
        noGuessesSpinBox->setMinimum(2);
        noGuessesSpinBox->setMaximum(10);
        noGuessesSpinBox->setValue(6);
        noCharactersSpinBox = new QSpinBox(settingsMenu);
        noCharactersSpinBox->setObjectName(QString::fromUtf8("noCharactersSpinBox"));
        noCharactersSpinBox->setGeometry(QRect(220, 220, 42, 22));
        noCharactersSpinBox->setMinimum(2);
        noCharactersSpinBox->setMaximum(10);
        noCharactersSpinBox->setValue(5);
        languageComboBox = new QComboBox(settingsMenu);
        languageComboBox->setObjectName(QString::fromUtf8("languageComboBox"));
        languageComboBox->setGeometry(QRect(190, 260, 69, 22));
        languageLabel = new QLabel(settingsMenu);
        languageLabel->setObjectName(QString::fromUtf8("languageLabel"));
        languageLabel->setGeometry(QRect(10, 260, 71, 21));

        retranslateUi(settingsMenu);
        QObject::connect(dialogBtnBox, &QDialogButtonBox::accepted, settingsMenu, qOverload<>(&QDialog::accept));
        QObject::connect(dialogBtnBox, &QDialogButtonBox::rejected, settingsMenu, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(settingsMenu);
    } // setupUi

    void retranslateUi(QDialog *settingsMenu)
    {
        settingsMenu->setWindowTitle(QCoreApplication::translate("settingsMenu", "Settings", nullptr));
        guessListBrowseBtn->setText(QCoreApplication::translate("settingsMenu", "Browse", nullptr));
        answerListBrowseBtn->setText(QCoreApplication::translate("settingsMenu", "Browse", nullptr));
        guessListLabel->setText(QCoreApplication::translate("settingsMenu", "Guess List", nullptr));
        answerListLabel->setText(QCoreApplication::translate("settingsMenu", "Answer list", nullptr));
        wordListSelectionHeaderLabel->setText(QCoreApplication::translate("settingsMenu", "Word Lists Selection", nullptr));
        gameSettingsHeaderLabel->setText(QCoreApplication::translate("settingsMenu", "Game Settings", nullptr));
        noGuessesLabel->setText(QCoreApplication::translate("settingsMenu", "Number of Guesses allowed:", nullptr));
        noCharactersLabel->setText(QCoreApplication::translate("settingsMenu", "Length of Words:", nullptr));
        languageLabel->setText(QCoreApplication::translate("settingsMenu", "Language:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settingsMenu: public Ui_settingsMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSMENU_H
