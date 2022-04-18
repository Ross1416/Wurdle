// mainwindow.cpp
// Author: Ross Inglis
// Last modified: 12/04/22

#ifndef LETTERWIDGET_H
#define LETTERWIDGET_H

#include<QLabel>
#include<QWidget>
#include<QHBoxLayout>
#include<QFrame>
#include<QStyle>

#include<string>

// LETTER WIDGET
// Individual widget with a rounded square containing single characte

class LetterWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *layout;
    QLabel *letter;
    std::string colour;
    bool highlightState;

public:
    explicit LetterWidget(QWidget *parent = nullptr);
    virtual ~LetterWidget();

    // SET/GET CHARACTER
    void setLetter(char);
    std::string getLetter() {return letter->text().toStdString();};

    // BACKGROUND COLOUR
    void setColour(std::string);

    // HIGHLIGHT
    void highlight();
    void unhighlight();

    // UPDATE STYLESHEET
    void updateStyle();

};

#endif // LETTERWIDGET_H
