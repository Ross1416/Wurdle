#ifndef PossAnswerWord_H
#define PossAnswerWord_H



#include "word.h"
#include "guessWord.h"
#include <vector>
#include <string>

class possAnswerWord : public word {
protected:
	bool isValid;
	std::vector<bool> checkedVector;
public:
	//Constructors and destructor
	~possAnswerWord();
	possAnswerWord();
	possAnswerWord(std::string c, bool v, int n);
	//Getters and setters
	std::vector<bool> getCheckedVector();
	bool getCheckedVector(int i);
	bool getValid();
	void setValid(bool v);
	void createCheckedVector();
	void createCheckedVector(int n);
	void setCheckedVector(int i, bool b);
	void answerSetValid(guessWord* iter);
	bool answerCheckValid(guessWord* iter);
	bool answerCheckValid(class possGuessWord* iter);
};

#endif