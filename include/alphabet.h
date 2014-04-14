////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef ALPHABET_H
#define ALPHABET_H

#include <set>
#include <string>

class Alphabet {
public:
	void addSymbol(char sybmol);
	const std::set<char> &getSymbols(){return symbols;}
	
	std::string toString();
	
private:
	std::set<char> symbols;
};

#endif