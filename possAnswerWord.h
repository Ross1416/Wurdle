// possAnswerWord.h
// Author: Angus Mulligan
// Last modified: 12/04/22
#ifndef PossAnswerWord_H
#define PossAnswerWord_H



#include "Word.h"
#include "guessWord.h"
#include <vector>
#include <string>

class possAnswerWord : public Word {
protected:
	bool isValid;
	std::vector<bool> checkedVector;
public:
    //Constructors and destructor
	~possAnswerWord();
	possAnswerWord();
    possAnswerWord(const std::string c, const bool v, const int n);
	//Getters and setters
    std::vector<bool> getCheckedVector() const;
    bool getCheckedVector( int i) ;
    bool getValid() const;
    void setValid(const bool v);
	void createCheckedVector();
    void createCheckedVector(const int n);
    void setCheckedVector( int i,  bool b);
	//List version
	void answerSetValid(guessWord* iter);
	bool answerCheckValid(guessWord* iter);
	//Vector version
	void answerSetValid(guessWord vector);
	bool answerCheckValid(guessWord vector);
	bool answerCheckValid(class possGuessWord* iter);
};

#endif
