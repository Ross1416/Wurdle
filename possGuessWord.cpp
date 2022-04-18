// possGuessWord.cpp
// Author: Angus Mulligan
// Last modified: 12/04/22
#include "possGuessWord.h"
#include "possAnswerWord.h"

//Destructor and Constructors
possGuessWord::~possGuessWord() {}

possGuessWord::possGuessWord() {
	content = "";
	entropy = 0;
    initialEntropy = 0;
	guessed = false;
	numCharacters = 5;
	createColourVector();
}

possGuessWord::possGuessWord(const std::string c, const float e, const bool g, const int n) {
	content = c;
	entropy = e;
    initialEntropy = e;
	guessed = g;
	numCharacters = n;
	createColourVector(numCharacters);
}

//Getters and Setters
float possGuessWord::getEntropy() const { return entropy; }

float possGuessWord::getInitialEntropy() const { return initialEntropy; }

bool possGuessWord::getGuessed() const { return guessed; }

int possGuessWord::getColourVector(const int i) const { return colourVector[i]; }

std::vector<uint8_t> possGuessWord::getColourVector() { return colourVector; }


int possGuessWord::getNumCharacters() const { return numCharacters; }

void possGuessWord::createColourVector() { //Create vector of colours for each character
	colourVector.clear();
	for (int i = 0; i < getNumCharacters(); i++) {
		colourVector.push_back(0);
	}
}

void possGuessWord::createColourVector(const int n) {
	colourVector.clear();
	for (int i = 0; i < n; i++) {
		colourVector.push_back(0);
	}
}

void possGuessWord::setEntropy(const float e) { entropy = e; }

void possGuessWord::setInitialEntropy (const float e) { initialEntropy = e; }

void possGuessWord::addEntropy(const float a) { entropy += a; }

float possGuessWord::calcEntropy(const int possAnswers, const int totalPossAnswers, const int validAnswers) const {
	if (validAnswers == 0) {
		return 0;
	}
	float pAnswers = float(possAnswers);
	float vAnswers = float(validAnswers);
    float tPAnswers = float(totalPossAnswers);
    return (1/pAnswers)*log2(tPAnswers/vAnswers);
}

void possGuessWord::setGuessed(bool g) { guessed = g; }

void possGuessWord::setColourVector(int i, int s) {
	colourVector[i] = s;
}

//Iterator version
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


//Vector Version
void possGuessWord::determineColourVector(possAnswerWord vector) {
	createColourVector();
	vector.createCheckedVector();
	for (int i = 0; i < numCharacters; i++) {//Loop through currentGuess and set greens

		if (content[i] == vector.getContent()[i]) {
			vector.setCheckedVector(i, true);
			setColourVector(i, 3);
		}
	}
	for (int i = 0; i < numCharacters; i++) {
		if (getColourVector(i) == 3) {
			continue;
		}
		for (int j = 0; j < numCharacters; j++) { //Loop through currentAnswer and set remaining yellows and greys
			//If the current answer character hasn't been used AND the guess character isn't yellow AND the characters match, THEN set it to yellow
			if ((content[i] == vector.getContent()[j]) && (!(vector.getCheckedVector(j))) && (colourVector[i] != 2)) {
				vector.setCheckedVector(j, true);
				setColourVector(i, 2);
			}
			//If the current answer character hasn't been used AND the guess character is blank, THEN set it to grey
			else if (!(vector.getCheckedVector(j)) && (colourVector[i] == 0)) {
				setColourVector(i, 1);
			}
		}
	}
}

std::string possGuessWord::displayColourVector(const int i) const {
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


void possGuessWord::setNumCharacters(const int n) { numCharacters = n; }

//Sorting by entropy
bool possGuessWord::operator<(const possGuessWord& ref) const {
	return (ref.entropy < entropy); //Overloads comparison operator, allowing the .sort() function to be used on a list
}

bool possGuessWord::compareEntropy(const possGuessWord x1, const possGuessWord x2) {
	return (x1.entropy > x2.entropy);
}
