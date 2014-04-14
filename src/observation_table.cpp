////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include "observation_table.h"
#include "common.h"
#include <iostream>

typedef std::map<std::pair<std::string, std::string>, bool>::iterator TableIterator;

//==============================================================================
// bool ObservationTable::isClosed()
//------------------------------------------------------------------------------
bool ObservationTable::isClosed(Alphabet &alphabet) {
	// Is consistent when s1 and s2 are elements of S such that
	// row(s1) = row(s2), for all a in A, row(s1.a)=row(s2.a).
	
	for (std::string s1 : prefixClosed) {
		for (std::string s2 : suffixClosed) {
			if (areRowsEqual(s1, s2)) {
				for (char symbol : alphabet.getSymbols()) {
					if (!areRowsEqual(s1.append(1, symbol), s2.append(1, symbol))) {
						return false;
					}
				}
			}
		}
	}
	
	return true;
}

//==============================================================================
// bool ObservationTable::isConsistent()
//------------------------------------------------------------------------------
bool ObservationTable::isConsistent(Alphabet &alphabet) {
	// Is closed if for each t in S.A there exists an s in S such that
	// row(t) = row(s)
	
	// Get strings in S.A
	std::vector<std::string> sCatA;
	for (std::string s : prefixClosed) {
		for (char symbol : alphabet.getSymbols()) {
			sCatA.push_back(s.append(1, symbol));
		}
	}
	
	// Compare each string in S.A to the rows of strings in S
	for (std::string t : sCatA) {
		bool foundMatch = false;
		
		for (std::string s : prefixClosed) {
			if (areRowsEqual(t, s)) {
				foundMatch = true;
				break;
			}
		}
		
		if (foundMatch == false) {
			return false;
		}
	}
	
	return true;
	
}

//==============================================================================
// void ObservationTable::addStringToS()
//------------------------------------------------------------------------------
void ObservationTable::addStringToS(std::string s) {
	prefixClosed.insert(s);
}

//==============================================================================
// void ObservationTable::addStringToE()
//------------------------------------------------------------------------------
void ObservationTable::addStringToE(std::string e) {
	suffixClosed.insert(e);
}

//==============================================================================
// void ObservationTable::addEntry()
//------------------------------------------------------------------------------
void ObservationTable::addEntry(std::string s, std::string e, bool isMember) {
	addStringToS(s);
	addStringToE(e);
	table[std::pair<std::string, std::string>(s, e)] = isMember;
}

//==============================================================================
// std::unique_ptr<Dfa> ObservationTable::getDfaRepresentation()
//------------------------------------------------------------------------------
std::unique_ptr<Dfa> ObservationTable::getDfaRepresentation() {
	
}

//==============================================================================
// std::string ObservationTable::toString()
//------------------------------------------------------------------------------
std::string ObservationTable::toString() {
	
	std::string header = "T\t";
	std::string rows;
	bool firstPass = true;
	
	for (std::string s : prefixClosed) {
		
		if (s == EMPTY_STRING) {
			rows += EPSILON_STRING + "|\t";
		}
		else {
			rows += s + "|\t";
		}
		
		for (std::string e : suffixClosed) {
			if (firstPass) {
				if (e == EMPTY_STRING) {
					header += EPSILON_STRING + "\t";
				}
				else {
					header += e + "\t";
				}
			}
			
			bool isMember = table[std::pair<std::string, std::string>(s, e)];
			
			if (isMember) {
				rows += "1";
			}
			else {
				rows += "0";
			}
			
			rows += "\t";
		}
		firstPass = false;
		rows += "\n";
	}
	
	return header + "\n" + rows;
}

//==============================================================================
// bool ObservationTable::areRowsEqual()
//------------------------------------------------------------------------------
bool ObservationTable::areRowsEqual(std::string string1, std::string string2) {
	
	for (std::string e : suffixClosed) {
		TableIterator firstIt = table.find(std::pair<std::string, std::string>(string1, e));
		TableIterator secondIt = table.find(std::pair<std::string, std::string>(string2, e));
		
		// No entry for either one
		if (firstIt == table.end() && secondIt == table.end()) {
			continue;
		} // One is found but not the other
		else if ((firstIt != table.end() && secondIt == table.end()) || (firstIt == table.end() && secondIt != table.end())) {
			return false;
		}
		else if ((*firstIt) != (*secondIt)) {
			return false;
		}
	}
	
	return true;
}