#include<QLabel>
#include<QHBoxLayout>
#include<QFrame>
#include<QStyle>
#include "letterwidget.h"
#include<iostream>

// LETTER WIDGET CONSTRUCTOR
LetterWidget::LetterWidget(QWidget *parent) : QWidget{parent}
{
    // Create layout
    layout = new QHBoxLayout(this);
    // Set margins and spacings
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    // Create label
    letter = new QLabel(this);
    // Set frame style
    letter->setLineWidth(1);
    letter->setStyleSheet("QFrame{border: 2px solid grey;border-radius: 5px;font: 10pt 'Arial';background-color: white}");
    // Align label with centre of layout
    letter->setAlignment(Qt::AlignCenter);

    // Set margins and geometry
    letter->setMargin(0);
    letter->setMaximumHeight(40);
    letter->setMaximumWidth(40);
    letter->setMinimumHeight(40);
    letter->setMinimumWidth(40);
    // Add label to layout

    // set unhighlighted
    highlightState = false;
    layout->addWidget(letter);

}

// LETTER WIDGET DESTRUCTOR
LetterWidget::~LetterWidget()
{

}

// SET THE LETTER WIDGET LABEL TEXT
void LetterWidget::setLetter(char l)
{
    letter->setText(QString(l));
}

// SET THE LETTER WIDGET BACKGROUND COLOUR
void LetterWidget::setColour(std::string colour)
{
//    QVariant qColour = QString::fromStdString(colour);
//    letter->setProperty("background-color",qColour);
    this->colour = colour;
//    std::string style = "QFrame{border: 1px solid black;border-radius: 5px;font: 10pt 'Arial';background-color: "+colour+"}";
//    letter->setStyleSheet(QString::fromStdString(style));
}

// SET THE HIGHLIGHT STATE TRUE (to apply this the letter widget's  style sheet must be updated)
void LetterWidget::highlight()
{
    highlightState = true;
}

// SET THE HIGHLIGHT STATE FALSE (to apply this the letter widget's  style sheet must be updated)
void LetterWidget::unhighlight()
{
    highlightState = false;
}

// UPDATE THE LETTER WIDGET STYLESHEET
void LetterWidget::updateStyle()
{
    std::string borderColour;
    if (highlightState)
    {
        borderColour = "black";
    }
    else{
        borderColour = "grey";
    }
    std::string style = "QFrame{border: 2px solid " + borderColour + ";border-radius: 5px;font: 10pt 'Arial';background-color: "+this->colour+"}";
//    std::cout << style << std::endl;
    letter->setStyleSheet(QString::fromStdString(style));
}


