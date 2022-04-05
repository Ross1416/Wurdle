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
