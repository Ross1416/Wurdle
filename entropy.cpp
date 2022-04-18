// entropy.cp
// Author: Angus Mulligan
// Last modified: 05/04/22
#include "entropy.h"

//Constructors and destructors
//entropy::~entropy() {}


entropy::entropy(const std::vector<uint8_t> cV, const int i) {
	colourVector = cV;
	times = i;
}

//Getters and setters

int entropy::getTimes() const { return times; }
void entropy::addTimes() { times += 1; }
void entropy::addTimes(const int i) { times += i; }
void entropy::setTimes(const int i) { times = i; }

std::vector<uint8_t> entropy::getColourVector() const { return colourVector; }

int entropy::getColourVector(const int i) const { return colourVector[i]; }

void entropy::createColourVector(const int numChars) { //Create vector of colours for each character
	colourVector.clear();
	for (int i = 0; i < numChars; i++) {
		colourVector.push_back(0);
	}
}

void entropy::setColourVector(const std::vector<uint8_t> cV) {
	colourVector = cV;
}

void entropy::setColourVector(const int i, const uint8_t s) {
	colourVector[i] = s;
}

std::string entropy::displayColourVector(const int i) const {
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
