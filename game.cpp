// game.cpp
// Author: Angus Mulligan
// Last modified: 18/04/22

#include "game.h"

Game::~Game() {}

Game::Game(){
    guessList = "guessList.txt";
    answerList = "answerList.txt";
    numCharacters = 5;
    maxGuesses = 6;
    possGuessIndex = 0;
    answerIndex = 0;
    totalPossGuesses = 0;
    totalPossAnswers = 0;
    totalGuesses = 0;
    cancel = false;
    hasPrecomputedColours = false;
    hasInitialEntropy = false;
    hasEntropy = false;
    guessListLoaded = false;
    answerListLoaded = false;
}


Game::Game(const unsigned int n, const unsigned int mG) {
    numCharacters = n;
    maxGuesses = mG;
    possGuessIndex = 0;
    answerIndex = 0;
    totalPossGuesses = 0;
    totalPossAnswers = 0;
    totalGuesses = 0;
    cancel = false;
    hasPrecomputedColours = false;
    hasInitialEntropy = false;
    hasEntropy = false;
    guessListLoaded = false;
    answerListLoaded = false;
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

std::vector<possGuessWord> Game::getPossGuessVector() {
    return possGuessVector;
}

std::vector<possGuessWord> Game::getPossGuessVectorSorted() const {
    return possGuessVectorSorted;
}


std::vector<possAnswerWord> Game::getPossAnswerVector() const {
    return possAnswerVector;
}

std::vector<guessWord> Game::getGuessedVector() const{
    return guessedVector;
}

unsigned int Game::getTotalGuesses() const {
    return totalGuesses;
}

void Game::setTotalGuesses(const unsigned int i) {
    totalGuesses = i;
}

unsigned int Game::getTotalAnswers() const {
    return totalPossAnswers;
}

void Game::setTotalAnswers(const unsigned int i) {
    totalPossAnswers = i;
}

answerWord Game::getCurrentAnswer() const {
    return currentAnswer;
}

void Game::setCurrentAnswer(const std::string s, const unsigned int n) {
    currentAnswer.setContent(s);
    currentAnswer.setNumCharacters(n);
}

int Game::readUnprocAnswers() {
    answerListLoaded = false;
    bool error = 0;
    int i = 0;
    possAnswerVector.clear();
    std::ifstream answerInFile(answerList);
    if (answerInFile.is_open()) {
        for (std::string line; getline(answerInFile, line);) {
            //If the line is empty or the number of characters are invalid then the line is skipped
            if ((line.size() == 0) || (line.length() != numCharacters)) {
                continue;
            }
            //possAnswerWord* x = new possAnswerWord(line, true, numCharacters);
            std::unique_ptr<possAnswerWord> x(new possAnswerWord(line, true, numCharacters));

            possAnswerVector.push_back(*x);
            i++;
        }
        answerListLoaded = true;
    }
    else {
        error = 1;
    }
    answerInFile.close();
    totalPossAnswers = i;
    //std::cout << "Number of answers: " << totalPossAnswers << std::endl;
    return error;
}

int Game::readUnprocGuesses() {
    guessListLoaded = false;
    int error = 0;
    int i = 0;
    possGuessVector.clear();
//    std::cout << guessList <<std::endl;
    std::ifstream guessInFile(guessList);
    if (guessInFile.is_open()) {
//        std::cout<<"open"<<std::endl;
        for (std::string line; getline(guessInFile, line);) {
            //If the line is empty or the number of characters are invalid then the line is skipped
            if ((line.size() == 0) || (line.length() != numCharacters)) {
                continue;
            }
            //possGuessWord* x = new possGuessWord(line, 0, false, numCharacters);
            std::unique_ptr<possGuessWord> x(new possGuessWord(line, 0, false, numCharacters));
            possGuessVector.push_back(*x);
            //std::cout<<x<<std::endl;
            i++;
        }
        guessListLoaded = true;
    }
    else {
        error = 1;
    }
    guessInFile.close();
    totalPossGuesses = i;
    //std::cout << "Number of guesses: " << totalPossGuesses << std::endl;
    return error;
}

bool Game::getHasPrecomputerColours()
{
    return hasPrecomputedColours;
}


bool Game::getHasInitialEntropy()
{
    return hasInitialEntropy;
}

bool Game::getGuessListLoaded()
{
    return guessListLoaded;
}

bool Game::getAnswerListLoaded()
{
    return answerListLoaded;
}

void Game::precomputeColours() {

    std::cout << "### Precomputing Colours Started ###" << std::endl;

    hasEntropy = false;
    hasPrecomputedColours = false;
    initial = true;

    preprocColours.clear(); //Clear the preprocColours vector
    //Resizes the preprocColours vector to the correct size
    preprocColours.resize(possGuessVector.size(), std::vector<std::vector<uint8_t>>(possAnswerVector.size(), std::vector<uint8_t>(numCharacters)));
    unsigned long long count = 0;
    unsigned int lastEmission = 0;
    unsigned long long divisor = (possGuessVector.size()*possAnswerVector.size());
    unsigned int emissionRate = 0.01*divisor;

    //Assigns the precomputed colour vectors for each cell in the lookup table
    for (unsigned int i = 0; i < possGuessVector.size() && !cancel ; i++) {
        for (unsigned int j = 0; j < possAnswerVector.size() && !cancel; j++) {
            possGuessVector[i].determineColourVector(possAnswerVector[j]);
            preprocColours[i][j] = possGuessVector[i].getColourVector();

            // EMIT PERCENT SIGNAL EVERY 1%
            if (count > lastEmission + emissionRate)
            {
                // plus one so that it goes to 100%
                float percent = (int)(((float)count/divisor)*100)+1;
//                std::cout<<percent<<std::endl;
                emit precomputeColorsSignal(percent);
                lastEmission = count;
            }
            count++;

            if (count == divisor)
            {
                std::cout<<"### Precomputing colours complete ###"<<std::endl;
                hasPrecomputedColours = true;

            }
        }
        //std::cout << i << std::endl;
    }
    this->calcEntropies();
}

void Game::calcEntropies() {
    //Stores the values needed for the entropy calculation
    std::cout << "### Started entropy calc ###" << std::endl;

    hasEntropy = false;

    std::vector<entropy> entropyVector;
    bool found = false;

    unsigned long long count = 0;
    unsigned int lastEmission = 0;
    unsigned long long divisor = (possGuessVector.size()*possAnswerVector.size());
    unsigned int emissionRate = 0.01*divisor;

    for (unsigned int i = 0; i < possGuessVector.size() && !cancel; i++) {
        possGuessVector[i].setEntropy(0);
        //Skip if it has already been guessed
        if (possGuessVector[i].getGuessed()) {
            continue;
        }

        entropyVector.clear();
        //Find the total number of each distinct colour vector in the possGuessWord's column
        for (unsigned int j = 0; j < possAnswerVector.size() && !cancel; j++) {

            if (!possAnswerVector[j].getValid()) {
                count++;
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

            // EMIT PERCENT SIGNAL EVERY 1%
            if (count > lastEmission + emissionRate)
            {
                float percent = (int)(((float)count/divisor)*100)+1; // plus one so that it goes to 100%
//                std::cout<<percent<<std::endl;
                emit calcEntropySignal(percent);
                lastEmission = count;

                if (percent >= 100)
                {
                    hasEntropy = true;
                    std::cout << "### Finished entropy calc ###" << std::endl;
                }
            }
            count++;
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



//void Game::Combined()
//{
//    this->precomputeColours();
//    this->calcEntropies();
//}

void Game::cancelCalculations()
{
    cancel = true;
}
void Game::uncancelCalculations()
{
    cancel = false;
}

bool Game::getCancel()
{
    return cancel;
}

/*
bool compareEntropy(const possGuessWord x1, const possGuessWord x2) {
    return (x1.getEntropy() > x2.getEntropy());
}
*/

bool Game::isValidGuess(const std::string s) {
//    std::cout<<possGuessVector.size()<<std::endl;
    for (unsigned int i = 0; i < possGuessVector.size(); i++) {
//        std::cout << possGuessVector[i].getContent() << std::endl;
        if ((possGuessVector[i].getContent() == s) && !(possGuessVector[i].getGuessed())) {
            possGuessIndex = i;
            possGuessVector[i].setGuessed(true); //Make sure the same word can't be guessed twice
            //Push new guessed word into guessedList
            std::unique_ptr<guessWord> x(new guessWord(s, 0, numCharacters, preprocColours[possGuessIndex][answerIndex]));
            guessedVector.push_back(*x);
            totalGuesses++;
            totalPossGuesses--;
            return true;
        }
    }
    return false;
}

bool Game::isCorrectGuess(const std::string s)
{
    if (currentAnswer.getContent() == s)
        return true;
    else
        return false;
}

void Game::setPossGuessIndex(const unsigned int i) {
    possGuessIndex = i;
}

unsigned int Game::getPossGuessIndex() {
    return possGuessIndex;
}

void Game::setAnswerIndex(const unsigned int i) {
    answerIndex = i;
}

unsigned int Game::getAnswerIndex() {
    return answerIndex;
}

void Game::randomAnswer() {
    //Program will crash if totalPossAnswers is < 1; therefore error handling is used
    try {
        //std::cout << "Total poss answers: " << totalPossAnswers << std::endl;
        if (totalPossAnswers < 1) {
            throw(totalPossAnswers);
        } else {
            srand((unsigned) time(0));
            unsigned int randomIndex = rand() % totalPossAnswers; //Generates random number for answer
            //std::cout << randomIndex << std::endl;
            currentAnswer.setContent(possAnswerVector[randomIndex].getContent());
            currentAnswer.setNumCharacters(numCharacters);
            answerIndex = randomIndex;
            std::cout << "Current Answer is: " << currentAnswer.getContent() << std::endl;
        }
    }
    catch (unsigned int tPA){
        std::cout << "Error: There are no possible answers!" << std::endl;
    }
    catch (...) {
        std::cout << "Standard Error!" << std::endl;
    }
}

void Game::setAnswer(const unsigned int i) {
    //Allows an answer to be set by inputting an integer of where it is in the vector
    try {
        if ((i > totalPossAnswers) || (i < 0)) {
            //If the input index is not a valid value of the possAnswerVector then throw error
            throw(i);
        } else {
            //Sets current answer
            currentAnswer.setContent(possAnswerVector[i].getContent());
            currentAnswer.setNumCharacters(numCharacters);
            answerIndex = i;
        }
    }
    catch (unsigned int i){
        std::cout << "Error: Index of answer is too large!" << std::endl;
    }
    catch (...) {
        std::cout << "Standard Error!" << std::endl;
    }
}

void Game::reset() {
    guessedVector.clear();
    for (unsigned int i = 0; i < possGuessVector.size(); i++) {
        possGuessVector[i].setGuessed(false); //No guesses have been made
    }

    for (unsigned int i = 0; i < possAnswerVector.size(); i++) {
        possAnswerVector[i].setValid(true); //All answers are valid due to no information
    }

    answerIndex = 0;
    possGuessIndex = 0;
    totalGuesses = 0;

    totalPossGuesses = possGuessVector.size();
    totalPossAnswers = possAnswerVector.size();
}

void Game::setValidAnswers() {
    for (unsigned int i = 0; i < possAnswerVector.size(); i++) {
        possAnswerVector[i].answerSetValid(guessedVector[totalGuesses - 1]);
    }
}

void Game::setInitialEntropies() {
    for (unsigned int i = 0; i < possGuessVector.size(); i++) {
        possGuessVector[i].setInitialEntropy(possGuessVector[i].getEntropy());
    }
    std::cout << "Initial entropies set" << std::endl;
    hasInitialEntropy = true;
}

void Game::resetToInitialEntropies() {

    if (hasInitialEntropy)
    {
        for (unsigned int i = 0; i < possGuessVector.size(); i++) {
            possGuessVector[i].setEntropy(possGuessVector[i].getInitialEntropy());
        }
        possGuessVectorSorted.clear();
        possGuessVectorSorted = possGuessVector;
        std::sort(possGuessVectorSorted.begin(), possGuessVectorSorted.end(), compareEntropy);
        std::cout << "Finished resetting to initial entropy" << std::endl;
    }



}
