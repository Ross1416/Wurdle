#include "answerWord.h"

	//Constructors and destructor
	answerWord::~answerWord() {}

	answerWord::answerWord() {
		content = "";
		numCharacters = 5;
		createCheckedVector(5);
	}

	answerWord::answerWord(std::string c, int n) {
		content = c;
		numCharacters = n;
		createCheckedVector(n);
	}

	//Getters and Setters

	std::vector<bool> answerWord::getCheckedVector() { return checkedVector; }

	bool answerWord::getCheckedVector(int i) { return checkedVector[i]; }

	void answerWord::createCheckedVector() {
		checkedVector.clear();
		for (int i = 0; i < getNumCharacters(); i++) {
			checkedVector.push_back(false);
		}
	}

	void answerWord::createCheckedVector(int n) {
		checkedVector.clear();
		for (int i = 0; i < n; i++) {
			checkedVector.push_back(false);
		}
	}

	void answerWord::setCheckedVector(int i, bool b) {
		checkedVector[i] = b;
	}