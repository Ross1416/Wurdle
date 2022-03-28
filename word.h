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
	word(const std::string c);
	//Getters and Setters
	int getNumCharacters() const;
	std::string getContent() const;
	void setContent(const std::string c);
	void setNumCharacters(const int n);
};

#endif
