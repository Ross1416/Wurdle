#include "Word.h"

//Destructor and Constructor
Word::~Word() {}

Word::Word() {
	content = "";
}

Word::Word(const std::string c) {
	content = c;
}

//Getters and Setters
std::string Word::getContent() { return content; }

int Word::getNumCharacters() const { return numCharacters; }

void Word::setContent(const std::string c) { content = c; }

void Word::setNumCharacters(const int n) { numCharacters = n; }
