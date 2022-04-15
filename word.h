#ifndef Word_H
#define Word_H

#include <string>

class Word {
protected:
	std::string content;
	int numCharacters;
public:
    //Destructor and Constructors
    ~Word();
    Word();
    Word(const std::string c);
	//Getters and Setters
    int getNumCharacters() const;
    std::string getContent();
    void setContent(const std::string c);
    void setNumCharacters(const int n);
};

#endif
