////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef DFA_HPP
#define DFA_HPP

#include <map>
#include <vector>
#include <string>

#include "alphabet.hpp"
#include "common.hpp"

const int NULL_STATE = -1;

class Dfa {
public:
	Dfa();
	
	Alphabet loadFromFile(String filename);
	
	void addState(String s, bool isAcceptState);
	void addTransition(int currentState, char symbol, int nextState);
	
	String toString();
	String toGraphVizString();
	int getStateNumber(String s);
	
	bool doesAcceptString(String s);
	String getAcceptedString(Alphabet &alphabet);
	bool acceptsNothing();
	
	static Dfa getComplement(Dfa &dfa);
	static Dfa getIntersection(Dfa &firstDfa, Dfa &secondDfa, Alphabet alphabet);
	static Dfa getSymmetricDifference(Dfa &firstDfa, Dfa &secondDfa, Alphabet alphabet);
	static Dfa getUnion(Dfa &firstDfa, Dfa &secondDfa, Alphabet alphabet);
	
private:
	std::pair<String, bool> depthFirst(int currentState, Alphabet alphabet, std::set<int> &statesVisited, char lastSymbol);
	
	std::set<int> 	parseAcceptStates(String line);
	Alphabet 		parseAlphabet(String line);
	int 			parseStates(String line);
	void 			parseTransition(String line);
	
	int numStates;
	std::set<int> acceptStates;
	std::map<std::pair<int, char>, int> transitionTable;
	std::map<String, std::pair<int, bool>> states;
};

#endif