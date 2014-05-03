////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "common.hpp"
#include "dfa.hpp"
#include "observation_table.hpp"

//==============================================================================
// bool ObservationTable::isClosed()
//------------------------------------------------------------------------------
bool ObservationTable::isClosed(Alphabet &alphabet) {
	// Is closed if for each t in S.A there exists an s in S such that
	// row(t) = row(s)
	
	// Get strings in S.A
	std::vector<String> sCatA;
	for (String s : prefixClosed) {
		for (char symbol : alphabet.getSymbols()) {
			sCatA.push_back(s + symbol);
		}
	}
	
	// Compare each string in S.A to the rows of strings in S
	for (String t : sCatA) {
		bool foundMatch = false;
		
		for (String s : prefixClosed) {
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
// bool ObservationTable::isConsistent()
//------------------------------------------------------------------------------
bool ObservationTable::isConsistent(Alphabet &alphabet) {
	// Is consistent when s1 and s2 are elements of S such that
	// row(s1) = row(s2), for all a in A, row(s1 . a)=row(s2 . a).
	
	for (String s1 : prefixClosed) {
		for (String s2 : prefixClosed) {
			if (areRowsEqual(s1, s2)) {
				//std::cout << "s1: " + s1 + " s2: " + s2 + "\n";
				//std::cout << "row(s1) == row(s2)" << std::endl;
				//std::cout << row(s1) + " == " + row(s2) + "\n";
				for (char symbol : alphabet.getSymbols()) {
					if (!areRowsEqual(s1 + symbol, s2 + symbol)) {
						return false;
					}
				}
			}
		}
	}
	
	return true;
}

//==============================================================================
// void ObservationTable::addStringToS()
//------------------------------------------------------------------------------
void ObservationTable::addStringToS(String s) {
	prefixClosed.insert(s);
}

//==============================================================================
// void ObservationTable::addStringToE()
//------------------------------------------------------------------------------
void ObservationTable::addStringToE(String e) {
	suffixClosed.insert(e);
}

//==============================================================================
// void ObservationTable::addEntry()
//------------------------------------------------------------------------------
void ObservationTable::addEntry(String s, String e, bool isMember) {
	table[TablePair(s, e)] = isMember;
	membershipMap[s + e] = isMember;
}

//==============================================================================
// bool ObservationTable::isInTable()
//------------------------------------------------------------------------------
bool ObservationTable::isInTable(String s, String e) {
	TableIterator it = table.find(TablePair(s, e));
	
	if (it == table.end()) {
		return false;
	} else {
		return true;
	}
}

//==============================================================================
// bool ObservationTable::isInTable()
//------------------------------------------------------------------------------
bool ObservationTable::isInTable(String s) {
	return (membershipMap.count(s) == 1);
}

//==============================================================================
// bool ObservationTable::isMember()
//------------------------------------------------------------------------------
bool ObservationTable::isMember(String s, String e) {
	return (table.find(TablePair(s, e)))->second;
}

//==============================================================================
// bool ObservationTable::isMember()
//------------------------------------------------------------------------------
bool ObservationTable::isMember(String s) {
	return (membershipMap.find(s))->second;
}

//==============================================================================
// std::unique_ptr<Dfa> ObservationTable::getDfaRepresentation()
//------------------------------------------------------------------------------
std::unique_ptr<Dfa> ObservationTable::getDfaRepresentation(Alphabet &alphabet) {
	
	std::unique_ptr<Dfa> dfa(new Dfa);
	std::set<String> uniqueRows;
	
	// Add states
	for (String s : prefixClosed) {
		
		// Rows with the same data should only count as one state
		// Has this row data been seen before?
		if (uniqueRows.count(row(s)) == 0) {
			uniqueRows.insert(row(s));
			dfa->addState(row(s), isMember(s));
		}
	}
	
	// Add transitions
	for (String s : prefixClosed) {
		for (char a : alphabet.getSymbols()) {
			
			int currentState = dfa->getStateNumber(row(s));
			
			// Find match for row and the corresponding string
			String result = row(s + a);
			
			String nextStateString;
			for (String stringToCheck : prefixClosed) {
				if (row(s + a) == row(stringToCheck)) {
					nextStateString = stringToCheck;
					break;
				}
			}
		
			// Get next state number
			int nextState = dfa->getStateNumber(row(nextStateString));
			
			if (nextState != NULL_STATE) {
				dfa->addTransition(currentState, a, nextState);
			}
		}
	}
	
	return dfa;
}

//==============================================================================
// String ObservationTable::toStringTable()
//------------------------------------------------------------------------------
String ObservationTable::toStringTable() {
	
	String header = "T\t";
	String rows;
	bool firstPass = true;
	
	for (String s : prefixClosed) {
		
		if (s == EMPTY_STRING) {
			rows += EPSILON_STRING + "|\t";
		}
		else {
			rows += s + "|\t";
		}
		
		for (String e : suffixClosed) {
			if (firstPass) {
				if (e == EMPTY_STRING) {
					header += EPSILON_STRING + "\t";
				}
				else {
					header += e + "\t";
				}
			}
			
			bool isMember = table[std::pair<String, String>(s, e)];
			
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
// String ObservationTable::toStringSets()
//------------------------------------------------------------------------------
String ObservationTable::toStringSets() {
	String string = "S = {";
	
	for (String s : prefixClosed) {
		string += s + ", ";
	}
	
	string.erase(string.length() - 2);
	string += "}\n";
	
	string += "E = {";
	for (String e : suffixClosed) {
		string += e + ", ";
	}
	
	string.erase(string.length() - 2);
	string += "}\n";
	
	return string;
}

//==============================================================================
// String ObservationTable::row()
//------------------------------------------------------------------------------
String ObservationTable::row(String s) {
	
	String row;
	
	for (String e : suffixClosed) {
		
		if (table[TablePair(s, e)] == true) {
			row += "1";
		}
		else {
			row += "0";
		}
	}
	
	return row;
}

//==============================================================================
// bool ObservationTable::areRowsEqual()
//------------------------------------------------------------------------------
bool ObservationTable::areRowsEqual(String string1, String string2) {

	return (row(string1) == row(string2));
}

//==============================================================================
// void ObservationTable::resolveNotClosed()
//------------------------------------------------------------------------------
void ObservationTable::resolveNotClosed(Alphabet &alphabet) {
	
	String candidateString;
	char candidateSymbol;
	bool searchIsDone = false;
	
	// Find s1 in S and a in A such that
	// row(s1 . a) is different from row(s) for all s in S
	for (String s1 : prefixClosed) {
		for (char a : alphabet.getSymbols()) {
			
			bool foundMatch = false;
			
			// Compare s1 to all s in S
			for (String s : prefixClosed) {
				foundMatch = (row(s1 + a) == row(s));
				
				if (foundMatch == true) {
					break;
				}
			}
			
			// row(s1 . a) is different from row(s) for all s in S
			if (foundMatch == false) {
				candidateString = s1;
				candidateSymbol = a;
				searchIsDone = true;
				break;
			}
		}
		
		if (searchIsDone) {
			break;
		}
	}
	
	
	// Add s1 . a to S
	addStringToS(candidateString + candidateSymbol);
	
}

//==============================================================================
// void ObservationTable::resolveNotConsistent()
//------------------------------------------------------------------------------
void ObservationTable::resolveNotConsistent(Alphabet &alphabet) {
	
	char candidateSymbol;
	String candidateSuffix;
	bool searchIsDone = false;
	
	// Find s1 and s2 in S, a in A, and e in E such that
	// row(s1) = row(s2) and T(s1 . a . e) != T(s2 . a. e)
	for (String s1 : prefixClosed) {
		for (String s2 : prefixClosed) {
			for (char a : alphabet.getSymbols()) {
				for (String e : suffixClosed) {
					// Are the rows not the same?
					if (row(s1) != row(s2)) {
						continue;
					}
					
					//std::cout << row(s1) + " == " + row(s2) + "\n";
					
					if (isMember(s1 + a + e) != isMember(s2 + a + e)) {
						//std::cout << "T(" + s1 + a + e + ") != T(" + s2 + a + e + ")\n";
						candidateSymbol = a;
						candidateSuffix = e;
						searchIsDone = true;
						break;
					}
				}
				
				if (searchIsDone) {
					break;
				}
			}
			
			if (searchIsDone) {
				break;
			}
		}
		
		if (searchIsDone) {
			break;
		}
	}
	
	// Add a . e to E
	addStringToE(candidateSymbol + candidateSuffix);
}