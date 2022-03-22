#ifndef AnswerWord_H
#define AnswerWord_H

#include "word.h"
#include <vector>

class answerWord : public word {
protected:
	std::vector<bool> checkedVector;
public:
	//Constructors and destructor
	~answerWord();
	answerWord();
	answerWord(std::string c, int n);
	//Getters and Setters
	std::vector<bool> getCheckedVector();
	bool getCheckedVector(int i);
	void createCheckedVector();
	void createCheckedVector(int n);
	void setCheckedVector(int i, bool b);
};

#endif