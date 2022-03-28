#include "possAnswerWord.h"
#include "possGuessWord.h"
#include <iostream>

	//Constructors and destructor
	possAnswerWord::~possAnswerWord() {}

	possAnswerWord::possAnswerWord() {
		content = "";
		isValid = true;
		numCharacters = 5;
		createCheckedVector(5);
	}

	possAnswerWord::possAnswerWord(const std::string c, const bool v, const int n) {
		content = c;
		isValid = v;
		numCharacters = n;
		createCheckedVector(n);
	}

	//Getters and setters

	std::vector<bool> possAnswerWord::getCheckedVector() const { return checkedVector; }

	bool possAnswerWord::getCheckedVector(const int i) const { return checkedVector[i]; }

	void possAnswerWord::createCheckedVector() {
		checkedVector.clear();
		for (int i = 0; i < getNumCharacters(); i++) {
			checkedVector.push_back(false);
		}
	}

	void possAnswerWord::createCheckedVector(const int n) {
		checkedVector.clear();
		for (int i = 0; i < n; i++) {
			checkedVector.push_back(false);
		}
	}

	void possAnswerWord::setCheckedVector(const int i, const bool b) {
		checkedVector[i] = b;
	}

	bool possAnswerWord::getValid() const { return isValid; }

	void possAnswerWord::setValid(const bool v) { isValid = v; }

	//List version
	void possAnswerWord::answerSetValid(guessWord* iter) { //Calls setValid and sets it to value returned by answerCheckValid
		setValid(answerCheckValid(iter));
	}
	//List Version
	bool possAnswerWord::answerCheckValid(guessWord* iter) { //Returns if possAnswer is valid or not (ONLY based on the current guess, passed it)

		int numChars = iter->getNumCharacters();
		int guessColour;
		std::vector<bool> countedVector;

		for (int i = 0; i < numChars; i++) {

			guessColour = iter->getColourVector(i);

			//If the colour of the guess character is GREEN and the characters don't match, then return FALSE
			if ((guessColour == 3) && (iter->getContent()[i] != getContent()[i])) {
				return false;
			} else if((guessColour == 3) && (iter->getContent()[i] == getContent()[i])) {
				countedVector.push_back(true);
			}
			else {
				countedVector.push_back(false);
			}
		}

		for (int i = 0; i < numChars; i++) {
			guessColour = iter->getColourVector(i);
			//If the colour of the guess character is YELLOW, then loop through to see if the possAnswerWord matches
			if ((guessColour == 2)) {
				bool found = false;
				for (int j = 0; j < numChars; j++) {
					//If a match is no found at any position APART from the position of the yellow in the guess AND the character hasn't already been counted, then false is returned
					if ((getContent()[j] == iter->getContent()[i]) && (i != j) && !(countedVector[j])) {
						found = true;
						countedVector[j] = true;
						break;
					}
				}
				if (found == false) {
					return false;
				}
			}
			//If the colour of the guess character is GREY, then loop through to make sure that the answer doesn't contain that letter
			else if ((guessColour == 1)) {
				for (int j = 0; j < numChars; j++) {
					if ((iter->getContent()[i] == getContent()[j]) && !(countedVector[j])) {
						/*
						std::cout << "----------------------------------------------------\n";
						std::cout << getContent() << " Problem letter: " << iter->getContent()[i] << std::endl;
						*/
						return false;
					}
				}
			}
		}
		return true;
	}

	//Vector Version
	void possAnswerWord::answerSetValid(guessWord vector) { //Calls setValid and sets it to value returned by answerCheckValid
		setValid(answerCheckValid(vector));
	}
	//Vector version
	bool possAnswerWord::answerCheckValid(guessWord vector) { //Returns if possAnswer is valid or not (ONLY based on the current guess, passed it)

		int numChars = vector.getNumCharacters();
		int guessColour;
		std::vector<bool> countedVector;

		for (int i = 0; i < numChars; i++) {

			guessColour = vector.getColourVector(i);

			//If the colour of the guess character is GREEN and the characters don't match, then return FALSE
			if ((guessColour == 3) && (vector.getContent()[i] != getContent()[i])) {
				return false;
			}
			else if ((guessColour == 3) && (vector.getContent()[i] == getContent()[i])) {
				countedVector.push_back(true);
			}
			else {
				countedVector.push_back(false);
			}
		}

		for (int i = 0; i < numChars; i++) {
			guessColour = vector.getColourVector(i);
			//If the colour of the guess character is YELLOW, then loop through to see if the possAnswerWord matches
			if ((guessColour == 2)) {
				bool found = false;
				for (int j = 0; j < numChars; j++) {
					//If a match is no found at any position APART from the position of the yellow in the guess AND the character hasn't already been counted, then false is returned
					if ((getContent()[j] == vector.getContent()[i]) && (i != j) && !(countedVector[j])) {
						found = true;
						countedVector[j] = true;
						break;
					}
				}
				if (found == false) {
					return false;
				}
			}
			//If the colour of the guess character is GREY, then loop through to make sure that the answer doesn't contain that letter
			else if ((guessColour == 1)) {
				for (int j = 0; j < numChars; j++) {
					if ((vector.getContent()[i] == getContent()[j]) && !(countedVector[j])) {
						/*
						std::cout << "----------------------------------------------------\n";
						std::cout << getContent() << " Problem letter: " << iter->getContent()[i] << std::endl;
						*/
						return false;
					}
				}
			}
		}
		return true;
	}

	////////////////////////////////////////////////////////
	// OPTIMISE ME!
	////////////////////////////////////////////////////////
	bool possAnswerWord::answerCheckValid(possGuessWord* iter) { //Returns if possAnswer is valid or not (ONLY based on the current guess, passed it)
		int numChars = iter->getNumCharacters();
		int guessColour;
		std::vector<bool> countedVector;

		for (int i = 0; i < numChars; i++) {

			guessColour = iter->getColourVector(i);
			//If the colour of the guess character is GREEN and the characters don't match, then return FALSE
			if ((guessColour == 3) && (iter->getContent()[i] != getContent()[i])) {
				return false;
			}				
			else if ((guessColour == 3) && (iter->getContent()[i] == getContent()[i])) {
				countedVector.push_back(true);
			}
			else {
				countedVector.push_back(false);
			}
		}

		for (int i = 0; i < numChars; i++) {
			guessColour = iter->getColourVector(i);
			//If the colour of the guess character is YELLOW, then loop through to see if the possAnswerWord matches
			if ((guessColour == 2)) {
				bool found = false;
				for (int j = 0; j < numChars; j++) {
					//If a match is no found at any position APART from the position of the yellow in the guess AND the character hasn't already been counted, then false is returned
					if ((getContent()[j] == iter->getContent()[i]) && (i != j) && !(countedVector[j])) {
						found = true;
						countedVector[j] = true;
						break;
					}
				}
				if (found == false) {
					return false;
				}				}
			//If the colour of the guess character is GREY, then loop through to make sure that the answer doesn't contain that letter
			else if ((guessColour == 1)) {
				for (int j = 0; j < numChars; j++) {
					if ((iter->getContent()[i] == getContent()[j]) && !(countedVector[j])) {
						return false;
					}
				}
			}
		}
		return true;
	}