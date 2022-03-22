#ifndef PossGuessWord_H
#define PossGuessWord_H

#include "word.h"
#include <list>
#include <vector>
#include "math.h"

class possGuessWord : public word {
protected:
	float entropy;
	bool guessed;
	std::vector<int> colourVector;
public:
	//Constructors and destructor
	~possGuessWord();
	possGuessWord();
	possGuessWord(std::string c, float e, bool g, int n);
	//Getters and Setters
	float getEntropy();
	bool getGuessed();
	int getColourVector(int i);
	int getNumCharacters();
	void createColourVector();
	void createColourVector(int n);
	void setColourVector(int i, int s);
	void determineColourVector(class possAnswerWord* iter);
	std::string displayColourVector(int i);
	void setEntropy(float e);
	void addEntropy(float a);
    float calcEntropy(int possAnswers, int validAnswers);
	void setGuessed(bool g);
	void setNumCharacters(int n);
};

#endif
