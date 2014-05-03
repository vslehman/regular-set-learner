////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef DFA_HPP
#define DFA_HPP

#include <map>
#include <vector>
#include <string>

#include "common.hpp"

const int NULL_STATE = -1;

class Dfa {
public:
	Dfa();
	void addState(String s, bool isAcceptState);
	
	String toString();
	String toGraphVizString();
	int getStateNumber(String s);
	
	void addTransition(int currentState, char symbol, int nextState);
	
private:
	int numStates;
	std::vector<int> acceptStates;
	
	std::map<std::pair<int, char>, int> transitionTable;
	std::map<String, std::pair<int, bool>> states;
};

#endif