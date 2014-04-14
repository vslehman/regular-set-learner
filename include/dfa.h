////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef DFA_H
#define DFA_H

#include <map>
#include <vector>

class Dfa {
public:
	
	
private:
	std::vector<int> states;
	std::vector<int> acceptStates;
	
	int startState;
	
	std::map<std::pair<int, char>, int> transitionTable;
};

#endif