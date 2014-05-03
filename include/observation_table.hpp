////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef OBSERVATION_TABLE_HPP
#define OBSERVATION_TABLE_HPP

#include <map>
#include <set>
#include <string>
#include <vector>

#include "alphabet.hpp"
#include "common.hpp"

typedef std::map<std::pair<String, String>, bool>::iterator TableIterator;
typedef std::pair<String, String> TablePair;

class Dfa;

class ObservationTable {
public:
	bool isClosed(Alphabet &alphabet);
	bool isConsistent(Alphabet &alphabet);
	
	void resolveNotClosed(Alphabet &alphabet);
	void resolveNotConsistent(Alphabet &alphabet);
	
	void addStringToS(String s);
	void addStringToE(String e);
	
	const std::set<String>& getS(){return prefixClosed;};
	const std::set<String>& getE(){return suffixClosed;};
	
	void addEntry(String s, String e, bool isMember);
	bool isInTable(String s, String e);
	bool isInTable(String s);
	bool isMember(String s, String e);
	bool isMember(String s);
	
	std::unique_ptr<Dfa> getDfaRepresentation(Alphabet &alphabet);
	
	String toStringTable();
	String toStringSets();
	
	String row(String s);
	bool areRowsEqual(String string1, String string2);
	
private:
	std::set<std::string> prefixClosed;
	std::set<std::string> suffixClosed;
	
	std::map<TablePair, bool> table;
	std::map<String, bool> membershipMap;
};

#endif