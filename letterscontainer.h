#ifndef LETTERSCONTAINER_H
#define LETTERSCONTAINER_H

#include <QWidget>
#include <vector>
#include "letterwidget.h"

class LettersContainer : public QWidget
{
    Q_OBJECT
public:
    explicit LettersContainer(int, int, QWidget *parent = nullptr);
    virtual ~LettersContainer();
private:
    int width;      // number of letters wide
    int height;      // number of letters high
    int selectedRow;
    int selectedColumn;

    QGridLayout *layout;
    std::vector<std::vector<LetterWidget*>> letters; // 2d vector of letter widgets
public:
    int getW() {return width;};
    int getH() {return height;};

    void setLetterColour(std::string,int,int);
    void setLetterText(char,int,int);
    void setCurrentLetterText(char);
    void setLetterHighlight(int,int);
    void setLetterUnhighlight(int,int);

    void setSelectedRow(int);
    void incrementSelectedRow();
    int getSelectedRow() {return selectedRow;};

    void incrementSelectedLetter();
    void decrementSelectedLetter();

    void setSelectedColumn(int);
    void incrementSelectedColumn();
    int getSelectedColumn() {return selectedColumn;};



    void updateLetterStyles();

signals:

};

#endif // LETTERSCONTAINER_H

