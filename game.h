// game.h
// Author: Angus Mulligan
// Last modified: 18/04/22
#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <vector>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <math.h>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "functions.h"
#include "entropy.h"
#include "possGuessWord.h"
#include "possAnswerWord.h"
#include "answerWord.h"
#include "guessWord.h"

class Game : public QObject{
    Q_OBJECT
private:

    std::string guessList; //Name of the guessList
    std::string answerList; //Name of the answerList

    unsigned int numCharacters;
    unsigned int maxGuesses;

    unsigned int possGuessIndex;
    unsigned int answerIndex;

    std::vector<possGuessWord> possGuessVector;
    unsigned int totalPossGuesses;

    std::vector<possGuessWord> possGuessVectorSorted; //Stores possGuessVector, sorted by entropy

    std::vector<possAnswerWord> possAnswerVector; //Vector of possible Answer Words
    unsigned int totalPossAnswers;

    std::vector<guessWord>guessedVector; //Vector of words that have been guessed
    unsigned int totalGuesses;

    answerWord currentAnswer; //Stores the answer

    std::vector<std::vector<std::vector<uint8_t>>> preprocColours; //Stores the preprocessed Colour vectors for lookup table of possGuessWords and possAnswerWords

    bool cancel;
    bool hasPrecomputedColours;
    bool hasEntropy;
    bool initial;
    bool hasInitialEntropy;

    bool guessListLoaded;
    bool answerListLoaded;
public:

    //Destructor and Constructors
    ~Game();
    Game();
    Game(const unsigned int n, const unsigned int mG);
    //Setters and Getters
    void setNumCharacters(const unsigned int n);
    unsigned int getNumCharacters() const;
    void setMaxGuesses(const unsigned int mG);
    unsigned int getMaxGuesses() const;
    void setGuessList(std::string gL);
    std::string getGuessList() const;
    void setAnswerList(std::string aL);
    std::string getAnswerList() const;
    void setPossGuessIndex(const unsigned int i);
    unsigned int getPossGuessIndex();
    void setAnswerIndex(const unsigned int i);
    unsigned int getAnswerIndex();
    unsigned int getTotalGuesses() const;
    void setTotalGuesses(const unsigned int i);
    unsigned int getTotalAnswers() const;
    void setTotalAnswers(const unsigned int i);
    answerWord getCurrentAnswer() const;
    void setCurrentAnswer(const std::string s, const unsigned int n);

    std::vector<possGuessWord> getPossGuessVector();
    std::vector<possAnswerWord> getPossAnswerVector() const;
    std::vector<possGuessWord> getPossGuessVectorSorted() const;
    std::vector<guessWord> getGuessedVector() const;

    int readUnprocAnswers(); //Function for reading in the txt for the possAnswerVector
    int readUnprocGuesses(); //Function for reading in the txt for the possGuessVector

    void precomputeColours(); //Clears, resizes and calculates the precomputed colour vectors for the current possGuessVector and possAnswerVectors, stores result in the preprocColours vector

    //bool compareEntropy(const possGuessWord x1, const possGuessWord x2);


    bool isValidGuess(const std::string s); //Determines if the string entered as a guess is a valid guess, if it is, then it is pushed to the back of the guessedVector
    bool isCorrectGuess(const std::string s);

    void randomAnswer(); //Determines a random answer

    void setAnswer(const unsigned int i); //Allows an answer to be set by inputting an integer of where it is in the vector

    void reset(); //Resets all relevant aspects of the game when called, doesn't reset the lists, colourVectors or entropies

    void setValidAnswers(); //Iterates through the possAnswerVector and determines which answers are still valid based on the current game conditions

    void setInitialEntropies(); //Sets the values for the initial entropies based on the calculated entropies

    void resetToInitialEntropies(); //Resets the current entropy values based on the initial entropy values
    void calcEntropies();

//    void Combined();

    void cancelCalculations();
    void uncancelCalculations();
    bool getCancel();

    bool getHasPrecomputerColours();
    bool getHasInitialEntropy();

    bool getGuessListLoaded();
    bool getAnswerListLoaded();
signals:
    void precomputeColorsSignal(int percent);
    void calcEntropySignal(int percent);
};

#endif // GAME_H
