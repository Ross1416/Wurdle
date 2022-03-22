#include "possGuessWord.h"
#include "possAnswerWord.h"

//Destructor and Constructors
possGuessWord::~possGuessWord() {}

possGuessWord::possGuessWord() {
	content = "";
	entropy = 0;
	guessed = false;
	numCharacters = 5;
	createColourVector();
}

possGuessWord::possGuessWord(std::string c, float e, bool g, int n) {
	content = c;
	entropy = e;
	guessed = g;
	numCharacters = n;
	createColourVector(numCharacters);
}

//Getters and Setters
float possGuessWord::getEntropy() { return entropy; }

bool possGuessWord::getGuessed() { return guessed; }

int possGuessWord::getColourVector(int i) { return colourVector[i]; }

int possGuessWord::getNumCharacters() { return numCharacters; }

void possGuessWord::createColourVector() { //Create vector of colours for each character
	colourVector.clear();
	for (int i = 0; i < getNumCharacters(); i++) {
		colourVector.push_back(0);
	}
}

void possGuessWord::createColourVector(int n) {
	colourVector.clear();
	for (int i = 0; i < n; i++) {
		colourVector.push_back(0);
	}
}

void possGuessWord::setEntropy(float e) { entropy = e; }

void possGuessWord::addEntropy(float a) { entropy += a; }

float possGuessWord::calcEntropy(int possAnswers, int validAnswers) {
    if (validAnswers == 0) {
		return 0;
	}
	float pAnswers = float(possAnswers);
	float vAnswers = float(validAnswers);
	return (1/pAnswers)*log2(pAnswers/vAnswers);
}

void possGuessWord::setGuessed(bool g) { guessed = g; }

void possGuessWord::setColourVector(int i, int s) {
	colourVector[i] = s;
}

void possGuessWord::determineColourVector(possAnswerWord* iter) {
	createColourVector();
	iter->createCheckedVector();
	for (int i = 0; i < numCharacters; i++) {//Loop through currentGuess and set greens
		if (content[i] == iter->getContent()[i]) {
			iter->setCheckedVector(i, true);
			setColourVector(i, 3);
			continue;
		}
	}
	for (int i = 0; i < numCharacters; i++) {
		for (int j = 0; j < numCharacters; j++) { //Loop through currentAnswer and set remaining yellows and greys
			//If the current answer character hasn't been used AND the guess character isn't yellow AND the characters match, THEN set it to yellow
			if ((content[i] == iter->getContent()[j]) && !(iter->getCheckedVector(j)) && (colourVector[i] != 2)) {
				iter->setCheckedVector(j, true);
				setColourVector(i, 2);
			}
			//If the current answer character hasn't been used AND the guess character is blank, THEN set it to grey
			else if (!(iter->getCheckedVector(j)) && (colourVector[i] == 0)) {
				setColourVector(i, 1);
			}
		}
	}
}

std::string possGuessWord::displayColourVector(int i) {
	switch (colourVector[i]) {
	case 0:
		return "Blank";
	case 1:
		return "Grey";
	case 2:
		return "Yellow";
	case 3:
		return "Green";
	default:
		return "Blank";
	}
}

void possGuessWord::setNumCharacters(int n) { numCharacters = n; }
