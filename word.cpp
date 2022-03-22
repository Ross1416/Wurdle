#include "word.h"

//Destructor and Constructor
word::~word() {}

word::word() {
	content = "";
}

word::word(std::string c) {
	content = c;
}

//Getters and Setters
std::string word::getContent() { return content; }

int word::getNumCharacters() { return numCharacters; }

void word::setContent(std::string c) { content = c; }

void word::setNumCharacters(int n) { numCharacters = n; }