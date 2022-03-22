#ifndef Word_H
#define Word_H

#include <string>

class word {
protected:
	std::string content;
	int numCharacters;
public:
	//Destructor and Constructors
	~word();
	word();
	word(std::string c);
	//Getters and Setters
	int getNumCharacters();
	std::string getContent();
	void setContent(std::string c);
	void setNumCharacters(int n);
};

#endif
