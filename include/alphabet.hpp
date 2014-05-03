////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef ALPHABET_HPP
#define ALPHABET_HPP

#include <set>
#include <string>

#include "common.hpp"

class Alphabet {
public:
	void addSymbol(char sybmol);
	const std::set<char> &getSymbols(){return symbols;}
	
	String toString();
	
private:
	std::set<char> symbols;
};

#endif