#include "game.h"

Game::~Game() {}

Game::Game(){
    guessList = "guessList.txt";
    answerList = "answerList.txt";
    numCharacters = 5;
    maxGuesses = 6;
    possGuessIndex = 0;
    possAnswerIndex = 0;
    totalPossGuesses = 0;
    totalPossAnswers = 0;
    totalGuesses = 0;
}


Game::Game(const unsigned int n, const unsigned int mG) {
    numCharacters = n;
    maxGuesses = mG;
    possGuessIndex = 0;
    possAnswerIndex = 0;
    totalPossGuesses = 0;
    totalPossAnswers = 0;
    totalGuesses = 0;
}


void Game::setNumCharacters(const unsigned int n){
    numCharacters = n;
}
unsigned int Game::getNumCharacters() const{
    return numCharacters;
}

void Game::setMaxGuesses(const unsigned int mG){
    maxGuesses = mG;
}
unsigned int Game::getMaxGuesses() const{
    return maxGuesses;
}

void Game::setGuessList(std::string gL) {
    guessList = gL;
}

std::string Game::getGuessList() const {
    return guessList;
}

void Game::setAnswerList(std::string aL) {
    answerList = aL;
}

std::string Game::getAnswerList() const {
    return answerList;
}

std::vector<possGuessWord> Game::getPossGuessVector() const {
    return possGuessVector;
}

std::vector<possAnswerWord> Game::getPossAnswerVector() const {
    return possAnswerVector;
}

std::vector<guessWord> Game::getGuessedVector() const {
    return guessedVector;
}

void Game::readUnprocAnswers() {
    int i = 0;
    possAnswerVector.clear();
    std::ifstream answerInFile(answerList);
    if (answerInFile.is_open()) {
        for (std::string line; getline(answerInFile, line);) {
            if ((line.size() == 0) || (line.length() != numCharacters)) { //If the line is empty or the number of characters are invalid then the line is skipped
                continue;
            }
            possAnswerWord* x = new possAnswerWord(line, true, numCharacters);
            possAnswerVector.push_back(*x);
            i++;
        }
    }
    answerInFile.close();
    totalPossGuesses = i;
}

void Game::readUnprocGuesses() {
    int i = 0;
    possGuessVector.clear();
    std::ifstream guessInFile(guessList);
    if (guessInFile.is_open()) {
        for (std::string line; getline(guessInFile, line);) {
            if ((line.size() == 0) || (line.length() != numCharacters)) { //If the line is empty or the number of characters are invalid then the line is skipped
                continue;
            }
            possGuessWord* x = new possGuessWord(line, 0, false, numCharacters);
            possGuessVector.push_back(*x);
            i++;
        }
    }
    guessInFile.close();
    totalPossGuesses = i;
}

void Game::precomputeColours() {
    preprocColours.clear(); //Clear the preprocColours vector
    preprocColours.resize(possGuessVector.size(), std::vector<std::vector<uint8_t>>(possAnswerVector.size(), std::vector<uint8_t>(numCharacters))); //Resizes the preprocColours vector to the correct size
    for (unsigned int i = 0; i < possGuessVector.size(); i++) { //Assigns the precomputed colour vectors for each cell in the lookup table
        for (unsigned int j = 0; j < possAnswerVector.size(); j++) {
            possGuessVector[i].determineColourVector(possAnswerVector[j]);
            preprocColours[i][j] = possGuessVector[i].getColourVector();
        }
    }
}

void Game::calcEntropies() {
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
    possGuessVectorSorted.clear();
    possGuessVectorSorted = possGuessVector;
    std::sort(possGuessVectorSorted.begin(), possGuessVectorSorted.end(), compareEntropy);
}

/*
bool compareEntropy(const possGuessWord x1, const possGuessWord x2) {
    return (x1.getEntropy() > x2.getEntropy());
}
*/
