#include "word.h"

//Destructor and Constructor
word::~word() {}

word::word() {
	content = "";
}

word::word(const std::string c) {
	content = c;
}

//Getters and Setters
std::string word::getContent() const { return content; }

int word::getNumCharacters() const { return numCharacters; }

void word::setContent(const std::string c) { content = c; }

void word::setNumCharacters(const int n) { numCharacters = n; }