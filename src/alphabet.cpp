////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include "alphabet.hpp"

//==============================================================================
// void Alphabet::addSymbol()
//------------------------------------------------------------------------------
void Alphabet::addSymbol(char symbol) {
	symbols.insert(symbol);
}

//==============================================================================
// String Alphabet::toString()
//------------------------------------------------------------------------------
String Alphabet::toString() {
	String string = "A = {";
	
	for (char symbol : symbols) {
		string += symbol;
		string += ", ";
	}
	
	// Remove last comma
	string.erase(string.length() - 2);
	
	string += "}";
	
	return string;
}