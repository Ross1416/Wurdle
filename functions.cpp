#include "functions.h"

/*
//Reading in an unprocessed file, returns total possGuesses
int readUnprocFile(const std::string filename, const int numCharacters, std::list<possGuessWord>& list) {
	int i = 0;
	std::ifstream guessInFile(filename);
	if (guessInFile.is_open()) {
		for (std::string line; getline(guessInFile, line);) {
			if ((line.size() == 0) || (line.length() != numCharacters)) { //If the line is empty or the number of characters are invalid then the line is skipped
				continue;
			}
			possGuessWord* x = new possGuessWord(line, 0, false, numCharacters);
			list.push_back(*x);
			i++;
		}
	}
	guessInFile.close();
	return i;
}
//Vector Version
int readUnprocFile(const std::string filename, const int numCharacters, std::vector<possGuessWord>& vector) {
	int i = 0;
	std::ifstream guessInFile(filename);
	if (guessInFile.is_open()) {
		for (std::string line; getline(guessInFile, line);) {
			if ((line.size() == 0) || (line.length() != numCharacters)) { //If the line is empty or the number of characters are invalid then the line is skipped
				continue;
			}
			possGuessWord* x = new possGuessWord(line, 0, false, numCharacters);
			vector.push_back(*x);
			i++;
		}
	}
	guessInFile.close();
	return i;
}
*/

/*
int readProcFile(const std::string filename, std::list<possGuessWord>& list) {
	int i = 0;
	int numCharacters = 0;

	std::ifstream guessInFile(filename);
	if (guessInFile.is_open()) {
		for (std::string line; getline(guessInFile, line);) {
			if (line.size() == 0) { //If the line is empty or the number of characters are invalid then the line is skipped
				continue;
			}
			std::vector<std::string>subString;
			std::istringstream ss(line);
			std::string token;

			while (getline(ss, token, ',')) {
				subString.push_back(token);
			}

			possGuessWord* x = new possGuessWord(subString[0], std::stof(subString[1]), false, std::stoi(subString[2]));
			list.push_back(*x);
			i++;
		}
	}
	guessInFile.close();
	return i;
}
*/

/*
//Write the processed file from the filename and the list of possGuessWords
void writeProcFile(const std::string filename, std::list<possGuessWord>& list) {
	std::list<possGuessWord>::iterator funcIter;
	std::ofstream guessOutFile(filename);
	if (guessOutFile.is_open()) {
		for (funcIter = list.begin(); funcIter != list.end(); funcIter++) {
			guessOutFile << funcIter->getContent() << "," << funcIter->getEntropy() << "," << funcIter->getNumCharacters() << "\n";
		}
	}
	guessOutFile.close();
}
*/

/*
//Reading in an unprocessed file, returns total possAnswers
int readUnprocFile(const std::string filename, const int numCharacters, std::list<possAnswerWord>& list) {
	int i = 0;
	std::ifstream answerInFile(filename);
	if (answerInFile.is_open()) {
		for (std::string line; getline(answerInFile, line);) {
			if ((line.size() == 0) || (line.length() != numCharacters)) { //If the line is empty or the number of characters are invalid then the line is skipped
				continue;
			}
			possAnswerWord* x = new possAnswerWord(line, true, numCharacters);
			list.push_back(*x);
			i++;
		}
	}
	answerInFile.close();
	return i;
}
//Vector Version
int readUnprocFile(const std::string filename, const int numCharacters, std::vector<possAnswerWord>& vector) {
	int i = 0;
	std::ifstream answerInFile(filename);
	if (answerInFile.is_open()) {
		for (std::string line; getline(answerInFile, line);) {
			if ((line.size() == 0) || (line.length() != numCharacters)) { //If the line is empty or the number of characters are invalid then the line is skipped
				continue;
			}
			possAnswerWord* x = new possAnswerWord(line, true, numCharacters);
			vector.push_back(*x);
			i++;
		}
	}
	answerInFile.close();
	return i;
}

std::string displayColourVector(const uint8_t i) {
	switch (i) {
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
*/

bool compareEntropy(const possGuessWord x1, const possGuessWord x2) {
	return (x1.getEntropy() > x2.getEntropy());
}

/*
void precomputeColours(std::vector<possGuessWord>& possGuessVector, const std::vector<possAnswerWord>& possAnswerVector, std::vector<std::vector<std::vector<uint8_t>>>& preprocColours){
	for (unsigned int i = 0; i < possGuessVector.size(); i++) {
		for (unsigned int j = 0; j < possAnswerVector.size(); j++) {
			possGuessVector[i].determineColourVector(possAnswerVector[j]);
			preprocColours[i][j] = possGuessVector[i].getColourVector();
		}
	}
}
*/

/*
void calcEntropies(std::vector<possGuessWord>& possGuessVector, const std::vector<possAnswerWord>& possAnswerVector, const std::vector<std::vector<std::vector<uint8_t>>>& preprocColours, std::vector<possGuessWord>& sortedVector, const int numCharacters, const int totalPossAnswers) {
	//Stores the values needed for the entropy calculation
	std::vector<entropy> entropyVector;
	bool found = false;

	for (unsigned int i = 0; i < possGuessVector.size(); i++) {
		possGuessVector[i].setEntropy(0);
		//Skip if it has already been guessed
		if (possGuessVector[i].getGuessed()) {
			continue;
		}

		entropyVector.clear();
		//Find the total number of each distinct colour vector in the possGuessWord's column
		//We can put the first value into the entropyVector because we know that it won't match any values in the entropyVector
		std::unique_ptr<entropy> x(new entropy(preprocColours[i][0], 1));
		entropyVector.push_back(*x);

		for (unsigned int j = 1; j < possAnswerVector.size(); j++) {
			if (!possAnswerVector[j].getValid()) {
				continue;
			}
			found = false;
			for (unsigned int k = 0; k < entropyVector.size(); k++) {
				if (entropyVector[k].getColourVector() == preprocColours[i][j]) {
					entropyVector[k].addTimes();
					found = true;
					break;
				}
			}
			//Otherwise push another value into the entropyVector
			if (!found) {
				std::unique_ptr<entropy> x(new entropy(preprocColours[i][j], 1));
				entropyVector.push_back(*x);
			}
		}

		for (unsigned int k = 0; k < entropyVector.size(); k++) {
			possGuessVector[i].addEntropy(possGuessVector[i].calcEntropy(pow(3, numCharacters), totalPossAnswers, entropyVector[k].getTimes()));
		}
	}
	entropyVector.clear();
	sortedVector.clear();
	sortedVector = possGuessVector;
	std::sort(sortedVector.begin(), sortedVector.end(), compareEntropy);
}
*/
