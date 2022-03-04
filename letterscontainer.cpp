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

    for (int j=0; j<height;j++)
    {
        std::vector<LetterWidget*> row;
        for (int i=0; i<width;i++)
        {
            QWidget *widget = new QWidget;
            LetterWidget *newLetter = new LetterWidget(widget);
            row.push_back(newLetter);
            layout->addWidget(newLetter,j,i);
        }
        letters.push_back(row);
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

void LettersContainer::setLetterHighlight(int x, int y)
{
    letters[y][x]->setHighlight();
}

void LettersContainer::setLetterUnhighlight(int x, int y)
{
    letters[y][x]->setUnhighlight();
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
