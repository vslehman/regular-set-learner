////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include "common.h"
#include "dfa.h"

//==============================================================================
// Dfa::Dfa()
//------------------------------------------------------------------------------
Dfa::Dfa() : numStates(0) {
	
}

//==============================================================================
// String Dfa::toGraphVizString()
//------------------------------------------------------------------------------
String Dfa::toGraphVizString() {
	String header = "digraph graphname {\n"
	                "  overlap=\"false\"\n"
	                "  nodesep=\"0.6\"\n"
	                "  edge [fontname=\"DejaVu Sans Mono\",fontsize=\"12pt\" arrowsize=\"0.5\" splines=\"true\" concentrate=\"true\"];\n"
	                "  node [shape=ellipse,fontname=\"DejaVu Sans Mono\",fontsize=\"12pt\" fixedsize=\"false\"];\n"
	                "  start [fixedsize=\"true\" style=\"invis\" width=\"0\" height=\"0\"]\n";
	
	String qString;
	
	// States
	std::map<String, std::pair<int, bool>>::iterator it;
	for (it = states.begin(); it != states.end(); it++) {
		
		int stateNumber = it->second.first;
		bool isAcceptState = it->second.second;
		
		qString += "q" + std::to_string(stateNumber);
		
		if (isAcceptState) {
			qString += " [shape=doublecircle]";
		}
		
		qString += "\n";
	}
	
	// Transitions
	String deltaString = "start -> q0 [label=\"\"]\n";
	
	std::map<std::pair<int, char>, int>::iterator transitions;
	for (transitions = transitionTable.begin(); transitions != transitionTable.end(); transitions++) {
		
		int currentState = transitions->first.first;
		char symbol = transitions->first.second;
		int nextState = transitions->second;
		
		deltaString += "q" + std::to_string(currentState) + " -> q" + std::to_string(nextState) +
		               " [label=\"" + symbol + "]\n";
	}
	
	return header + qString + deltaString;
}


//==============================================================================
// String Dfa::toString()
//------------------------------------------------------------------------------
String Dfa::toString() {
	String string = "M = (Q, " + SIGMA_STRING + ", " + DELTA_STRING + ", q0, F) :\n";
	
	String qString = "Q = { ";
	String fString = "F = { ";
	
	// States
	std::map<String, std::pair<int, bool>>::iterator it;
	for (it = states.begin(); it != states.end(); it++) {
		
		int stateNumber = it->second.first;
		bool isAcceptState = it->second.second;
		
		qString += "q" + std::to_string(stateNumber) + ", ";
		
		if (isAcceptState) {
			fString += "q" + std::to_string(stateNumber) + ", ";
		}
	}
	qString += "}\n";
	fString += "}\n";
	
	// Transitions
	String deltaString;
	
	std::map<std::pair<int, char>, int>::iterator transitions;
	for (transitions = transitionTable.begin(); transitions != transitionTable.end(); transitions++) {
		
		int currentState = transitions->first.first;
		char symbol = transitions->first.second;
		int nextState = transitions->second;
		
		deltaString += DELTA_STRING + "( q" + std::to_string(currentState) + ", " +
		               symbol + ") = q" + std::to_string(nextState) + "\n";
	}
	
	string += qString + fString + deltaString;
	
	return string;
}

//==============================================================================
// void Dfa::addState(String s, bool isAcceptState)
//------------------------------------------------------------------------------
void Dfa::addState(String s, bool isAcceptState) {
	std::pair<int, bool> state(numStates++, isAcceptState);
	states[s] = state;
}

//==============================================================================
// void Dfa::addTransition(int currentState, char symbol, int nextState)
//------------------------------------------------------------------------------
void Dfa::addTransition(int currentState, char symbol, int nextState) {
	
	std::pair<int, char> input(currentState, symbol);
	
	transitionTable[input] = nextState;
}

//==============================================================================
// int Dfa::getStateNumber(String s)
//------------------------------------------------------------------------------
int Dfa::getStateNumber(String s) {
	std::map<String, std::pair<int, bool>>::iterator it = states.find(s);
	
	if (it == states.end()) {
		return NULL_STATE;
	}
	else {
		return it->second.first;
	}
}