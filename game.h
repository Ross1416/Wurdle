#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <math.h>
#include <memory>
#include "functions.h"
#include "entropy.h"
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

    std::vector<std::vector<std::vector<uint8_t>>> preprocColours; //Stores the preprocessed Colour vectors for lookup table of possGuessWords and possAnswerWords
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

    void readUnprocAnswers(); //Function for reading in the txt for the possAnswerVector
    void readUnprocGuesses(); //Function for reading in the txt for the possGuessVector

    void precomputeColours(); //Clears, resizes and calculates the precomputed colour vectors for the current possGuessVector and possAnswerVectors, stores result in the preprocColours vector

    //bool compareEntropy(const possGuessWord x1, const possGuessWord x2);
    void calcEntropies();
};

#endif // GAME_H
