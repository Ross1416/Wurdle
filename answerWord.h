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
	answerWord(const std::string c, const int n);
	//Getters and Setters
	std::vector<bool> getCheckedVector() const;
	bool getCheckedVector(const int i) const;
	void createCheckedVector();
	void createCheckedVector(const int n);
	void setCheckedVector(const int i, const bool b);
};

#endif