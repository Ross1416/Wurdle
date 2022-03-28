#ifndef PossGuessWord_H
#define PossGuessWord_H

#include "word.h"
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include "functions.h"

class possGuessWord : public word {
protected:
	float entropy;
	bool guessed;
	std::vector<uint8_t> colourVector;
public:
	//Constructors and destructor
	~possGuessWord();
	possGuessWord();
	possGuessWord(const std::string c, const float e, const bool g, const int n);
	//Getters and Setters
	float getEntropy() const;
	bool getGuessed() const;
	int getColourVector(const int i) const;
	std::vector<uint8_t> getColourVector() const;

	int getNumCharacters() const;
	void createColourVector();
	void createColourVector(const int n);
	void setColourVector(const int i, const int s);
	void determineColourVector(class possAnswerWord* iter);
	void determineColourVector(class possAnswerWord vector);
	std::string displayColourVector(const int i) const;
	void setEntropy(const float e);
	void addEntropy(const float a);
	float calcEntropy(const int possAnswers, const int arg2, const int validAnswers) const;
	void setGuessed(const bool g);
	void setNumCharacters(const int n);
	//Sorting by entropy
	bool operator<(const possGuessWord& ref) const;
	bool compareEntropy(const possGuessWord x1, const possGuessWord x2);
};

#endif