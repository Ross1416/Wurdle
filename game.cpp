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
