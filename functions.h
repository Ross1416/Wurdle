#ifndef Functions_H
#define Functions_H

#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include "possGuessWord.h"
#include "possAnswerWord.h"
#include "entropy.h"
#include "math.h"
#include <memory>

//Reading in unprocessed txt file
//Takes in the name, number of characters and a pointer to a list, returns the number of possGuesses
int readUnprocFile(const std::string filename, const int numCharacters, std::list<possGuessWord>& list);
int readUnprocFile(const std::string filename, const int numCharacters, std::vector<possGuessWord>& vector);

//Writing to processed txt file
//void writeProcFile(const std::string filename, std::list<possGuessWord>& list);

//Reading in processed txt file




//Takes in the name, number of characters and a pointer to a list, returns the number of possGuesses
int readUnprocFile(const std::string filename, const int numCharacters, std::list<possAnswerWord>& list);
int readUnprocFile(const std::string filename, const int numCharacters, std::vector<possAnswerWord>& vector);

std::string displayColourVector(const uint8_t i);

bool compareEntropy(const possGuessWord x1, const possGuessWord x2);

void precomputeColours(std::vector<possGuessWord>& possGuessVector, const std::vector<possAnswerWord>& possAnswerVector, std::vector<std::vector<std::vector<uint8_t>>>& preprocColours);

//Takes in the possGuessVector, possAnswerVector, preprocColour Vector, possGuessVectorSorted, numCharacters and totalPossAnswerWords; Then calculates entropy and sets possGuessVectorSorted to the sorted possGuessVector
void  calcEntropies(std::vector<possGuessWord>& possGuessVector, const std::vector<possAnswerWord>& possAnswerVector, const std::vector<std::vector<std::vector<uint8_t>>>& preprocColours, std::vector<possGuessWord>& sortedVector, const int numCharacters, const int totalPossAnswers);
#endif 
