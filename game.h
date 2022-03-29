#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "possGuessWord.h"
#include "possAnswerWord.h"
#include "answerWord.h"
#include "guessWord.h"

class Game {
private:

    std::string guessList; //Name of the guessList
    std::string answerList; //Name of the answerList

    unsigned int numCharacters;
    unsigned int maxGuesses;

    unsigned int possGuessIndex;
    unsigned int possAnswerIndex;

    std::vector<possGuessWord> possGuessVector;
    unsigned int totalPossGuesses;

    std::vector<possGuessWord> possGuessVectorSorted; //Stores possGuessVector, sorted by entropy

    std::vector<possAnswerWord> possAnswerVector; //Vector of possible Answer Words
    unsigned int totalPossAnswers;

    std::vector<guessWord>guessedVector; //Vector of words that have been guessed
    unsigned int totalGuesses;

    answerWord currentAnswer(); //Stores the answer
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

    std::vector<possGuessWord> getPossGuessVector() const;
    std::vector<possAnswerWord> getPossAnswerVector() const;
    std::vector<guessWord> getGuessedVector() const;

};

#endif // GAME_H
