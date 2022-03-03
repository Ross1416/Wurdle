#include "letterscontainer.h"

#include "letterscontainer.h"
#include<QGridLayout>
#include<vector>

LettersContainer::LettersContainer(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout *layout = new QGridLayout(this);
//    layout->setHorizontalSpacing(0);
//    layout->setVerticalSpacing(0);

//    QWidget *w1 = new QWidget;
//    QWidget *w2 = new QWidget;
//    QWidget *w3 = new QWidget;
//    LetterWidget *newLetter1 = new LetterWidget(w1);
//    LetterWidget *newLetter2 = new LetterWidget(w2);
//    LetterWidget *newLetter3 = new LetterWidget(w3);
//    layout->addWidget(newLetter1,0,0); //,Qt::AlignLeft);
//    layout->addWidget(newLetter2,0,1); //,Qt::AlignLeft);
//    layout->addWidget(newLetter3,0,2); //,Qt::AlignLeft);

//    x = 50;
//    y = 50;
    w = 7;
    h = 6;

    QWidget *widget = new QWidget;
    LetterWidget *newLetter = new LetterWidget(widget);


    for (int j=0; j<h;j++)
    {
        std::vector<LetterWidget*> row;
        for (int i=0; i<w;i++)
        {
            widget = new QWidget;
            newLetter = new LetterWidget(widget);
//            int xPos = i*50+x;
//            int yPos = j*50+y;
//            newLetter->setX(xPos);
//            newLetter->setY(yPos);
//            auto n = *newLetter;
//            row.push_back(*newLetter);
            row.push_back(newLetter);
            layout->addWidget(newLetter,j,i);



        }
        letters.push_back(row);
    }
//    newLetter->setLetter('k');


    for (int j=0; j<h;j++)
    {
        for (int i=0; i<w;i++)
        {
            letters[j][i]->setLetter('B');
            letters[j][i]->setColour("red");
        }
    }
}

LettersContainer::~LettersContainer()
{

}
