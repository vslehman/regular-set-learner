////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef ALPHABET_H
#define ALPHABET_H

#include <set>
#include <string>

#include "common.h"

class Alphabet {
public:
	void addSymbol(char sybmol);
	const std::set<char> &getSymbols(){return symbols;}
	
	String toString();
	
private:
	std::set<char> symbols;
};

#endif