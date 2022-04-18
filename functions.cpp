// functinos.cpp
// Author: Angus Mulligan
// Last modified: 05/04/22
#include "functions.h"

bool compareEntropy(const possGuessWord x1, const possGuessWord x2) {
	return (x1.getEntropy() > x2.getEntropy());
}
