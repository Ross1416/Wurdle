#ifndef GuessWord_H
#define GuessWord_H

#include "word.h"
#include "answerWord.h"
#include <vector>
#include <stdint.h>

class guessWord : public word {
protected:
	float entropy;
	std::vector<uint8_t> colourVector;
public:
    //Constructors and destructor
	~guessWord();
	guessWord();
    guessWord(const std::string c, const float e, const int n);
    guessWord(const std::string c, const float e, const int n, const std::vector<uint8_t> cV);

	//Getters and Setters
    float getEntropy() const;
    int getColourVector( int i) ;
    std::vector<uint8_t> getColourVector();
	void createColourVector(); //Create vector of colours for each character
    void createColourVector(const int n);
    void setColourVector(const std::vector<uint8_t> cV);
    void setColourVector(const int i, const uint8_t s);
	void determineColourVector(answerWord a); //Sets the colours based on the current answer
    std::string displayColourVector(const int i) const; //Returns value of colour vector as a string value
    void setEntropy(const float e);
};

#endif
