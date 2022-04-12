#ifndef LETTERSCONTAINER_H
#define LETTERSCONTAINER_H

#include <QWidget>
#include<QGridLayout>
#include<vector>
#include<QTimer>
#include<algorithm>
#include <vector>

#include "letterwidget.h"

// LETTER CONTAINER
// Widget that contains and handles all the individual letter widgets contained with in this.
// Only a single instance of this should be in the program.

class LettersContainer : public QWidget
{
    Q_OBJECT
public:
    explicit LettersContainer(int, int, QWidget *parent = nullptr);
    virtual ~LettersContainer();
private:
    int width;
    int height;
    int selectedRow;
    int selectedColumn;

    QGridLayout *layout;                                // QT Grid layout that will contain the letter widgets
    std::vector<std::vector<LetterWidget*>> letters;    // 2d vector of letter widgets

public:
    int getW() {return width;};
    int getH() {return height;};

    // BACKGROUND COLOUR
    void setLetterColour(std::string,int,int);

    // TEXT
    void setLetterText(char,int,int);
    void setCurrentLetterText(char);
    char getCurrentLetterText();

    // HIGHLIGHTS
    void highlightCurrentLetter();
    void unhighlightCurrentLetter();
    void setLetterHighlight(int,int);
    void setLetterUnhighlight(int,int);

    // SELECTED ROW
    void setSelectedRow(int);
    int getSelectedRow() {return selectedRow;};
    void incrementSelectedRow();

    // SELECTED COLUMN
    int getSelectedColumn() {return selectedColumn;};
    void setSelectedColumn(int);
    void incrementSelectedColumn();
    void decrementSelectedColumn();

    // GET WORD FROM CURRENT ROW
    std::string getCurrentWord();

    // UPDATE STYLESHEETS OF ALL WIDGETS
    void updateLetterStyles();

    // UPDATE BACKGROUND COLOURS OF WIDGETS IN SELECTED ROW
    void UpdateCurrentColours(const std::vector<uint8_t> colours);

    // INVALID GUESSES
    void invalidGuess();

// slots can recieve QT signals
public slots:
    void invalidGuessReset();

};

#endif // LETTERSCONTAINER_H

