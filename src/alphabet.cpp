////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include "alphabet.h"

//==============================================================================
// void Alphabet::addSymbol()
//------------------------------------------------------------------------------
void Alphabet::addSymbol(char symbol) {
	symbols.insert(symbol);
}

//==============================================================================
// void Alphabet::addSymbol()
//------------------------------------------------------------------------------
std::string Alphabet::toString() {
	std::string string = "A = {";
	
	for (char symbol : symbols) {
		string.append(1, symbol);
		string += ", ";
	}
	
	string.erase(string.length() - 2);
	string += "}";
	
	return string;
}