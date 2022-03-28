#ifndef Entropy_H
#define Entropy_H

#include <vector>
#include <string>
#include <iostream>

class entropy {
protected:
	std::vector<uint8_t> colourVector;
	int times;
public:
	//Constructors and destructor
	~entropy() { /*std::cout << "Destructor called!" << std::endl;*/ }
	entropy(const std::vector<uint8_t> cV, const int i);

	//Getters and Setters
	int getTimes() const;
	void addTimes();
	void addTimes(const int i);
	void setTimes(const int i);
	std::vector<uint8_t> getColourVector() const;
	int getColourVector(const int i) const;
	void createColourVector(const int n); //Create vector of colours for each character
	void setColourVector(const std::vector<uint8_t> cV);
	void setColourVector(const int i, const uint8_t s);
	std::string displayColourVector(const int i) const; //Returns value of colour vector as a string value
};

#endif