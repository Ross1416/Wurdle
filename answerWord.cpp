#include "answerWord.h"

    //Constructors and destructor
	answerWord::~answerWord() {}

	answerWord::answerWord() {
		content = "";
		numCharacters = 5;
		createCheckedVector(5);
	}

    answerWord::answerWord(const std::string c, const int n) {
		content = c;
		numCharacters = n;
		createCheckedVector(n);
	}

	//Getters and Setters

    std::vector<bool> answerWord::getCheckedVector() const { return checkedVector; }

    bool answerWord::getCheckedVector(const int i) const { return checkedVector[i]; }

	void answerWord::createCheckedVector() {
		checkedVector.clear();
		for (int i = 0; i < getNumCharacters(); i++) {
			checkedVector.push_back(false);
		}
	}

    void answerWord::createCheckedVector(const int n) {
		checkedVector.clear();
		for (int i = 0; i < n; i++) {
			checkedVector.push_back(false);
		}
	}

    void answerWord::setCheckedVector(const int i, const bool b) {
		checkedVector[i] = b;
    }
