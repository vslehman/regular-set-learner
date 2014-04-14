////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef OBSERVATION_TABLE_H
#define OBSERVATION_TABLE_H

#include <map>
#include <set>
#include <string>
#include <vector>

#include "alphabet.h"

class Dfa;

class ObservationTable {
public:
	bool isClosed(Alphabet &alphabet);
	bool isConsistent(Alphabet &alphabet);
	
	void addStringToS(std::string s);
	void addStringToE(std::string e);
	
	void addEntry(std::string s, std::string e, bool isMember);
	
	std::unique_ptr<Dfa> getDfaRepresentation();
	
	std::string toString();
	
private:
	std::set<std::string> prefixClosed;
	std::set<std::string> suffixClosed;
	
	std::map<std::pair<std::string, std::string>, bool> table;
	
	bool areRowsEqual(std::string string1, std::string string2);
};

#endif