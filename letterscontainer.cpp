#include "letterscontainer.h"

#include "letterscontainer.h"
#include<QGridLayout>
#include<vector>

//LETTER CONTAINER CONSTRUCTOR
LettersContainer::LettersContainer(int w, int h, QWidget *parent)
    : QWidget{parent}
{
    layout = new QGridLayout(this);

    this->width = w;
    this->height = h;
    this->selectedRow = 0;
    this->selectedColumn = 0;

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

        // do i need to delete row??
//        for (int j=0; j<height;j++)
//        {
//            delete row[j];
//        }

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
// INCREMENT SELECTED ROW BY 1
void LettersContainer::incrementSelectedRow()
{
    // !!!!!!NEED TO CHECK FOR OUT OF BOUNDS
    this->selectedRow = this->selectedRow + 1;
}

// INCREMENTED SELECTED COLUMN BY 1
void LettersContainer::incrementSelectedColumn()
{
    // Check to ensure selected row will not be incremented out of bounds
    if (this->selectedColumn < this->width-1)
    {
        this->selectedColumn = this->selectedColumn + 1;

    }
}
// DECREMENTED SELECTED COLUMN BY 1
void LettersContainer::decrementSelectedColumn()
{
    // Check to ensure selected row will not be decremented out of bounds
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
    return currentWord;
}

// SET THE SELECTED COLUMN OF LETTER WIDGETS
void LettersContainer::setSelectedColumn(int col)
{
    this->selectedColumn = col;
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
