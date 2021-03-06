// possGuessWord.h
// Author: Angus Mulligan
// Last modified: 12/04/22
#ifndef PossGuessWord_H
#define PossGuessWord_H

#include "Word.h"
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdint.h>
//#include "functions.h"
#include <math.h>

class possGuessWord : public Word {
protected:
	float entropy;
    float initialEntropy; //Stores the entropy for the first guess
	bool guessed;
	std::vector<uint8_t> colourVector;
public:
    //Constructors and destructor
	~possGuessWord();
	possGuessWord();
    possGuessWord(const std::string c, const float e, const bool g, const int n);
	//Getters and Setters
    float getEntropy() const;
    float getInitialEntropy() const;
    bool getGuessed() const;
    int getColourVector(const int i) const;
    std::vector<uint8_t> getColourVector();

    int getNumCharacters() const;
	void createColourVector();
    void createColourVector(const int n);
    void setColourVector(const int i, const int s);
	void determineColourVector(class possAnswerWord* iter);
	void determineColourVector(class possAnswerWord vector);
    std::string displayColourVector(const int i) const;
    void setEntropy(const float e);
    void setInitialEntropy( const float e);
    void addEntropy(const float a);
    float calcEntropy(const int possAnswers, const int arg2, const int validAnswers) const;
    void setGuessed(const bool g);
    void setNumCharacters(const int n);
	//Sorting by entropy
    bool operator<(const possGuessWord& ref) const;
    bool compareEntropy(const possGuessWord x1, const possGuessWord x2);
};

#endif
