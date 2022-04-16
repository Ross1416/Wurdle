#include "letterscontainer.h"

#include<iostream>

//LETTER CONTAINER CONSTRUCTOR
LettersContainer::LettersContainer(int w, int h, QWidget *parent)
    : QWidget{parent}
{
    // Create grid layout
    layout = new QGridLayout(this);

    // Set initial variables
    this->width = w;
    this->height = h;
    this->selectedRow = 0;
    this->selectedColumn = 0;

    // Add letter widgets to layout
    for (int j=0; j<height;j++)
    {
        std::vector<LetterWidget*> row;
        for (int i=0; i<width;i++)
        {
//            QWidget *widget = new QWidget;
            LetterWidget *newLetter = new LetterWidget(this); // DO QT WIDGET POINTERS DELETE AUTOMATICALLY?
            row.push_back(newLetter);
            layout->addWidget(newLetter,j,i);
        }
        letters.push_back(row);
    }
}

// LETTER CONTAINER DESTRUCTOR
LettersContainer::~LettersContainer()
{
    delete layout;
    for (int j=0; j<height;j++)
    {
        for (int i=0; i<width;i++)
        {
            delete letters[j][i];
        }
    }
}

// SET SPECIFIC LETTER BACKGROUND COLOUR
void LettersContainer::setLetterColour(std::string c, int x, int y)
{
    letters[y][x]->setColour(c);
}

// SET SPECIFIC LETTER CHARACTER
void LettersContainer::setLetterText(char c, int x, int y)
{
    letters[y][x]->setLetter(c);
}

// SET THE CURRENTLY SELECTED/HIGHLIGHTED LETTER WIDGET CHARACTER
void LettersContainer::setCurrentLetterText(char c)
{
    letters[this->getSelectedRow()][this->getSelectedColumn()]->setLetter(c);
}

// GET THE CURRENTLY SELECTED/HIGHLIGHTED LETTER WIDGET CHARACTER
char LettersContainer::getCurrentLetterText()
{
    return letters[this->getSelectedRow()][this->getSelectedColumn()]->getLetter().c_str()[0];
}

// HIGHLIGHT THE CURRENTLY SELECTED/HIGHLIGHTED LETTER WIDGET CHARACTER (must remember to update styles to apply this)
void LettersContainer::highlightCurrentLetter()
{
    letters[this->getSelectedRow()][this->getSelectedColumn()]->highlight();
}
// UNHIGHLIGHT THE CURRENTLY SELECTED/HIGHLIGHTED LETTER WIDGET CHARACTER (must remember to update styles to apply this)
void LettersContainer::unhighlightCurrentLetter()
{
    letters[this->getSelectedRow()][this->getSelectedColumn()]->unhighlight();
}
// HIGHLIGHT A SPECICFIC LETTER (must remember to update styles to apply this)
void LettersContainer::setLetterHighlight(int x, int y)
{
    letters[y][x]->highlight();
}
// UNHIGHLIGHT A SPECIFIC LETTER (must remember to update styles to apply this)
void LettersContainer::setLetterUnhighlight(int x, int y)
{
    letters[y][x]->unhighlight();
}
// SET THE SELECTED ROW OF LETTER WIDGETS
void LettersContainer::setSelectedRow(int row)
{
    this->selectedRow = row;
}

// SET THE SELECTED COLUMN OF LETTER WIDGETS
void LettersContainer::setSelectedColumn(int col)
{
    this->selectedColumn = col;
}

// INCREMENT SELECTED ROW BY 1
void LettersContainer::incrementSelectedRow()
{
    // Check to ensure selected row will not be incremented out of bounds
    if (this->selectedRow < this->height-1)
    {
        this->unhighlightCurrentLetter();
        this->selectedRow = this->selectedRow + 1;
        this->setSelectedColumn(0);
        this->highlightCurrentLetter();
        this->updateLetterStyles();
    }
}

// INCREMENTED SELECTED COLUMN BY 1
void LettersContainer::incrementSelectedColumn()
{
    // Check to ensure selected column will not be incremented out of bounds
    if (this->selectedColumn < this->width-1)
    {
        this->selectedColumn = this->selectedColumn + 1;

    }
}
// DECREMENTED SELECTED COLUMN BY 1
void LettersContainer::decrementSelectedColumn()
{
    // Check to ensure selected column will not be decremented out of bounds
    if (this->selectedColumn > 0)
    {
        this->selectedColumn = this->selectedColumn - 1;
    }
}

// GET THE CURRENT WORD FROM ALL THE CHARARCTERS IN THE CURRENTLY SELECTED ROW
std::string LettersContainer::getCurrentWord()
{
    std::string currentWord = "";
    // Iterate through all letter widgets in row
    for (int i = 0; i<width; i++)
    {
        std::string letter = letters[this->getSelectedRow()][i]->getLetter();
        // Check if letter widget is blank - If Y: add character to word; N: set current word empty and break from loop
        if (letter != " " && letter != "")
            currentWord += letter;
        else
        {
            currentWord = "";
            break;
        }
    }


    transform(currentWord.begin(), currentWord.end(), currentWord.begin(), tolower);  // Transforms the current word into all lower case
    return currentWord;                                                               // as this is the format of the word lists
}

// UPDATE ALL LETTER WIDGET'S STYLESHEETS
void LettersContainer::updateLetterStyles()
{
    for (int j=0; j<height;j++)
    {
        for (int i=0; i<width;i++)
        {
            letters[j][i]->updateStyle();
        }
    }
}

// CALLED WHEN INVALID GUESS IS INPUT
void LettersContainer::invalidGuess()
{
    // Set all letterwidgets background colour to red in selected row
    for (int i=0; i<width;i++)
    {
        letters[this->selectedRow][i]->setColour("red");
        letters[this->selectedRow][i]->updateStyle();
    }

    // Start timer to reset the letter widgets after 300 ms
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(invalidGuessReset()));
    timer->start(300);
}

// RESET CURRENT ROW AFTER INVALID GUESS (DRIVEN BY TIMER)
void LettersContainer::invalidGuessReset()
{
    for (int i=0; i<width;i++)
    {
        letters[this->selectedRow][i]->setColour("white");
//        letters[this->selectedRow][i]->setLetter(' ');
        letters[this->selectedRow][i]->updateStyle();
    }
//    this->unhighlightCurrentLetter();
//    this->setSelectedColumn(0);
//    this->highlightCurrentLetter();
//    this->updateLetterStyles();
}

// UPDATE THE LETTERWIDGETS BACKGROUND COLOURS IN SELECTED ROW
void LettersContainer::UpdateCurrentColours(const std::vector<uint8_t> colours)
{
    for (int i=0; i<width;i++)
    {
        std::string colour = "white";
        switch((int)colours[i])
        {
        // Blank
        case 0:
            break;
        // Grey
        case 1:
           colour = "grey";
           break;
        // Yellow
        case 2:
            colour = "yellow";
            break;
        // Green
        case 3:
            colour = "green";
            break;
        }

        letters[this->selectedRow][i]->setColour(colour);
        letters[this->selectedRow][i]->updateStyle();
    }
}



