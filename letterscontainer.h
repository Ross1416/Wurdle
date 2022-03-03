#ifndef LETTERSCONTAINER_H
#define LETTERSCONTAINER_H

#include <QWidget>
#include <vector>
#include "letterwidget.h"

class LettersContainer : public QWidget
{
    Q_OBJECT
public:
    explicit LettersContainer(QWidget *parent = nullptr);
    virtual ~LettersContainer();
private:
    int xPos;   // x pos in main windows#
    int yPos;   // y pos in main window
    int w;      // number of letters wide
    int h;      // number of letters high

    std::vector<std::vector<LetterWidget*>> letters; // 2d vector of letter widgets
//    std::vector<LetterWidget*> letters;
public:
    int getXPos() {return xPos;};
    int getYPos() {return yPos;};

    int getW() {return w;};
    int getH() {return h;};


signals:

};

#endif // LETTERSCONTAINER_H

