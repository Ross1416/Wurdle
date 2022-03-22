#ifndef GuessWord_H
#define GuessWord_H

#include "word.h"
#include "answerWord.h"
#include <vector>

class guessWord : public word {
protected:
	float entropy;
	std::vector<int> colourVector;
public:
	//Constructors and destructor
	~guessWord();
	guessWord();
	guessWord(std::string c, float e, int n);

	//Getters and Setters
	float getEntropy();
	int getColourVector(int i);
	void createColourVector(); //Create vector of colours for each character
	void createColourVector(int n);
	void setColourVector(int i, int s);
	void determineColourVector(answerWord a); //Sets the colours based on the current answer
	std::string displayColourVector(int i); //Returns value of colour vector as a string value
	void setEntropy(float e);
};

#endif
