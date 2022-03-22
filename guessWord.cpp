#include "guessWord.h"

	//Constructors and destructor
guessWord::~guessWord() {}

	guessWord::guessWord() {
		content = "";
		entropy = 0;
		numCharacters = 5;
		createColourVector();
	}

	guessWord::guessWord(std::string c, float e, int n) {
		content = c;
		entropy = e;
		numCharacters = n;
		createColourVector(numCharacters);
	}

	//Getters and Setters
	float guessWord::getEntropy() { return entropy; }

	int guessWord::getColourVector(int i) { return colourVector[i]; }

	void guessWord::createColourVector() { //Create vector of colours for each character
		colourVector.clear();
		for (int i = 0; i < getNumCharacters(); i++) {
			colourVector.push_back(0);
		}
	}

	void guessWord::createColourVector(int n) {
		colourVector.clear();
		for (int i = 0; i < n; i++) {
			colourVector.push_back(0);
		}
	}

	void guessWord::setColourVector(int i, int s) {
		colourVector[i] = s;
	}

	void guessWord::determineColourVector(answerWord a) {
		createColourVector();
		a.createCheckedVector();
		for (int i = 0; i < numCharacters; i++) {//Loop through currentGuess and set greens
			if (content[i] == a.getContent()[i]) {
				a.setCheckedVector(i, true);
				setColourVector(i, 3);
				continue;
			}
		}
		for (int i = 0; i < numCharacters; i++) {
			for (int j = 0; j < numCharacters; j++) { //Loop through currentAnswer and set remaining yellows and greys
				//If the current answer character hasn't been used AND the guess character isn't yellow AND the characters match, THEN set it to yellow
				if ((content[i] == a.getContent()[j]) && !(a.getCheckedVector(j)) && (colourVector[i] != 2)) {
					a.setCheckedVector(j, true);
					setColourVector(i, 2);
				}
				//If the current answer character hasn't been used AND the guess character is blank, THEN set it to grey
				else if (!(a.getCheckedVector(j)) && (colourVector[i] == 0)) {
					setColourVector(i, 1);
				}
			}
		}
	}

	std::string guessWord::displayColourVector(int i) {
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

	void guessWord::setEntropy(float e) { entropy = e; }