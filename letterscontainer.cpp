#include "letterscontainer.h"

#include "letterscontainer.h"
#include<QGridLayout>
#include<vector>

LettersContainer::LettersContainer(int w, int h, QWidget *parent)
    : QWidget{parent}
{
    layout = new QGridLayout(this);

    this->width = w;
    this->height = h;
    this->selectedRow = 0;

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

void LettersContainer::setLetterColour(std::string c, int x, int y)
{
    letters[y][x]->setColour(c);
}

void LettersContainer::setLetterText(char c, int x, int y)
{
    letters[y][x]->setLetter(c);
}

void LettersContainer::setCurrentLetterText(char c)
{
    letters[this->getSelectedRow()][this->getSelectedColumn()]->setLetter(c);
}

char LettersContainer::getCurrentLetterText()
{
    return letters[this->getSelectedRow()][this->getSelectedColumn()]->getLetter().c_str()[0];
}

void LettersContainer::highlightCurrentLetter()
{
    letters[this->getSelectedRow()][this->getSelectedColumn()]->highlight();
}

void LettersContainer::unhighlightCurrentLetter()
{
    letters[this->getSelectedRow()][this->getSelectedColumn()]->unhighlight();
}

void LettersContainer::setLetterHighlight(int x, int y)
{
    letters[y][x]->highlight();
}

void LettersContainer::setLetterUnhighlight(int x, int y)
{
    letters[y][x]->unhighlight();
}

void LettersContainer::setSelectedRow(int row)
{
    this->selectedRow = row;
}

void LettersContainer::incrementSelectedRow()
{
    this->selectedRow = this->selectedRow + 1;
}

void LettersContainer::incrementSelectedColumn()
{
    if (this->selectedColumn < this->width-1)
    {
        this->selectedColumn = this->selectedColumn + 1;

    }
}

void LettersContainer::decrementSelectedColumn()
{
    if (this->selectedColumn > 0)
    {
        this->selectedColumn = this->selectedColumn - 1;
    }
}


void LettersContainer::setSelectedColumn(int col)
{
    this->selectedColumn = col;
}

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
