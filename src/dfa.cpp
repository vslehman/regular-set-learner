////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>

#include "common.hpp"
#include "dfa.hpp"

//==============================================================================
// Dfa::Dfa()
//------------------------------------------------------------------------------
Dfa::Dfa() : numStates(0) {
	
}

//==============================================================================
// Alphabet Dfa::loadFromFile()
//------------------------------------------------------------------------------
Alphabet Dfa::loadFromFile(String filename) {
	std::cout << "Loading Dfa...\n";
	String line;
	std::ifstream inFile(filename);
	
	int loadedStates = 0;
	Alphabet loadedAlphabet;
	std::set<int> loadedAcceptStates;
	
	
	if (inFile.is_open())
	{
		while (getline(inFile,line))
		{
			char parseType = line.at(0);
			
			switch (parseType) {
				case 'Q': {
					loadedStates = parseStates(line);
					break;
				}
				case 'A': {
					loadedAlphabet = parseAlphabet(line);
					break;
				}
				case 'F': {
					loadedAcceptStates = parseAcceptStates(line);
					break;
				}
				case 'd': {
					parseTransition(line);
					break;
				}
				case '#': {
					break;
				}
				default: {
					std::cout << "ERROR in DFA file syntax!" << std::endl;
					break;
				}
			}
		}
		
		inFile.close();
	}
	
	for (int i = 0; i < loadedStates; i++) {
		bool isAcceptState = false;
		
		if (loadedAcceptStates.count(i) == 1) {
			isAcceptState = true;
		}
		
		addState("q" + std::to_string(i), isAcceptState);
	}
	
	std::cout << "...Done\n";
	
	std::cout << toString() << std::endl;
	
	return loadedAlphabet;
}

//==============================================================================
// std::set<int> Dfa::parseAcceptStates()
//------------------------------------------------------------------------------
std::set<int> Dfa::parseAcceptStates(String line) {
	int currentPos = 3;
	int lastDelimiter = 2;
	std::set<int> loadedAcceptStates;

	for (; currentPos < line.length(); currentPos++) {
		if ((line.at(currentPos) == ',' || line.at(currentPos == '}')) && currentPos - lastDelimiter > 1) {
			loadedAcceptStates.insert(atoi(line.substr(lastDelimiter + 1, currentPos - lastDelimiter).c_str()));
			lastDelimiter = currentPos;
		}
	}
	
	return loadedAcceptStates;
}

//==============================================================================
// Alphabet Dfa::parseAlphabet()
//------------------------------------------------------------------------------
Alphabet Dfa::parseAlphabet(String line) {
	int currentPos = 3;
	int lastDelimiter = 3;
	Alphabet alphabet;
	
	for (; currentPos < line.length(); currentPos++) {
		if (line.at(currentPos) == ',' || line.at(currentPos) == '}') {
			alphabet.addSymbol(line.at(currentPos - 1));
			lastDelimiter = currentPos;
		}
	}
	
	return alphabet;
}

//==============================================================================
// int Dfa::parseStates()
//------------------------------------------------------------------------------
int Dfa::parseStates(String line) {
	return atoi(line.substr(2).c_str());
}

//==============================================================================
// void Dfa::parseTransition()
//------------------------------------------------------------------------------
void Dfa::parseTransition(String line) {
	int currentState;
	char symbol;
	int nextState = 0;
	
	int currentPos = 2;
	int lastDelimiter = 2;
	Alphabet alphabet;
	
	for (; currentPos < line.length(); currentPos++) {
		if (line.at(currentPos) == ',') {
			currentState = atoi(line.substr(lastDelimiter, currentPos - lastDelimiter).c_str());
			lastDelimiter = currentPos;
		}
		else if (line.at(currentPos) == ')') {
			symbol = line.at(currentPos - 1);
		}
		else if (line.at(currentPos) == '=') {
			nextState = atoi(&line.at(currentPos + 1));
			break;
		}
	}
	
	addTransition(currentState, symbol, nextState);
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
		
		deltaString += " q" + std::to_string(currentState) + " -> q" + std::to_string(nextState) +
		               " [label=\"" + symbol + "\"]\n";
	}
	
	return header + qString + deltaString + "\n}";
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
	std::pair<int, bool> state(numStates, isAcceptState);
	states[s] = state;
	
	if (isAcceptState) {
		acceptStates.insert(numStates);
	}
	
	numStates++;
}

//==============================================================================
// void Dfa::addTransition(int currentState, char symbol, int nextState)
//------------------------------------------------------------------------------
void Dfa::addTransition(int currentState, char symbol, int nextState) {
	transitionTable[std::pair<int, char>(currentState, symbol)] = nextState;
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

//==============================================================================
// bool Dfa::doesAcceptString(
//------------------------------------------------------------------------------
bool Dfa::doesAcceptString(String s) {
	int currentState = 0;
	int currentChar = 0;
	
	while (currentChar < s.length()) {
		currentState = transitionTable[std::pair<int, char>(currentState, s.at(currentChar))];
		currentChar++;
	}
	
	int finalState = currentState;

	std::map<String, std::pair<int, bool>>::iterator it;
	for (it = states.begin(); it != states.end(); it++) {
		if (it->second.first == finalState) {
			return it->second.second;
		}
	}

	return false;
}

//==============================================================================
// String Dfa::getAcceptedString(
//------------------------------------------------------------------------------
String Dfa::getAcceptedString(Alphabet &alphabet) {
	
	std::set<int> statesVisited;
	int currentState = 0;

	return depthFirst(currentState, alphabet, statesVisited, '\0').first;
}

//==============================================================================
// String Dfa::depthFirst()
//------------------------------------------------------------------------------
std::pair<String, bool> Dfa::depthFirst(int currentState, Alphabet alphabet, std::set<int> &statesVisited, char lastSymbol) {
		
	// Have we arrived at an accept state?
	if (acceptStates.count(currentState) == 1) {
		return std::pair<String, bool>(String(1, lastSymbol), true);
	} // Has this state already been visited?
	else if (statesVisited.count(currentState) == 1) {
		return std::pair<String, bool>("", false);
	}
	
	statesVisited.insert(currentState);
	
	for (char symbol : alphabet.getSymbols()) {
		
		int nextState = transitionTable[std::pair<int, char>(currentState, symbol)];
		
		std::pair<String, bool> result = depthFirst(nextState, alphabet, statesVisited, symbol);
		
		// Path leads to accept state
		if (result.second == true) {
			return std::pair<String, bool>(lastSymbol + result.first, true);
		}
	}
	
	return std::pair<String, bool>("", false);
}


//==============================================================================
// bool Dfa::acceptsNothing()
//------------------------------------------------------------------------------
bool Dfa::acceptsNothing() {
	
	std::set<int> markedStates;
	markedStates.insert(0);
	
	bool newStateWasMarked = false;
	
	do {
		newStateWasMarked = false;
		
		for (int state : markedStates) {
		
			// Mark any states that can be transitioned into
			std::map<std::pair<int, char>, int>::iterator transitions;
			for (transitions = transitionTable.begin(); transitions != transitionTable.end(); transitions++) {
				if (transitions->first.first == state) {
				
					int nextState = transitions->second;
				
					// Is the state unmarked?
					if (markedStates.count(nextState) == 0) {
						markedStates.insert(nextState);
						newStateWasMarked = true;
					}
				}
			}
		}
	}
	while (newStateWasMarked);
	
	// Was an accept state marked?
	std::map<String, std::pair<int, bool>>::iterator it;
	for (it = states.begin(); it != states.end(); it++) {
		
		int stateNumber = it->second.first;
		bool isAcceptState = it->second.second;
		
		if (isAcceptState) {
			// There is an accept state that is marked
			if (markedStates.count(stateNumber) == 1) {
				return false;
			}
		}
	}
	
	return true;
}

//==============================================================================
// Dfa Dfa::getComplement()
//------------------------------------------------------------------------------
Dfa Dfa::getComplement(Dfa &dfa) {
	
	Dfa returnDfa = dfa;
	
	std::map<String, std::pair<int, bool>>::iterator it;
	for (it = returnDfa.states.begin(); it != returnDfa.states.end(); it++) {
		it->second.second = !it->second.second;
	}
	
	return returnDfa;
}

//==============================================================================
// Dfa Dfa::getIntersection()
//------------------------------------------------------------------------------
Dfa Dfa::getIntersection(Dfa &firstDfa, Dfa &secondDfa, Alphabet alphabet) {
	Dfa intersectDfa;
	
	// Q = {(r1, r2) | r1 in Q1 and r2 in Q2)}
	std::map<String, std::pair<int, bool>>::iterator firstIt;
	std::map<String, std::pair<int, bool>>::iterator secondIt;
	
	// Add states and accept states
	for (firstIt = firstDfa.states.begin(); firstIt != firstDfa.states.end(); firstIt++) {
		for (secondIt = secondDfa.states.begin(); secondIt != secondDfa.states.end(); secondIt++) {
			
			String cross = std::to_string(firstIt->second.first) + std::to_string(secondIt->second.first);
			bool isAcceptState = firstIt->second.second && secondIt->second.second;
			
			intersectDfa.addState(cross, isAcceptState);
		}
	}

	// d((r1, r2), a) = (d(r1, a), d(r2, a))
	// Add transitions
	for (firstIt = firstDfa.states.begin(); firstIt != firstDfa.states.end(); firstIt++) {
		for (secondIt = secondDfa.states.begin(); secondIt != secondDfa.states.end(); secondIt++) {
			for (char symbol : alphabet.getSymbols()) {
				
				String cross = std::to_string(firstIt->second.first) + std::to_string(secondIt->second.first);
				int crossStateNumber = intersectDfa.getStateNumber(cross);
				
				int firstNextState = firstDfa.transitionTable[std::pair<int, char>(firstIt->second.first, symbol)];
				int secondNextState = secondDfa.transitionTable[std::pair<int, char>(secondIt->second.first, symbol)];
				
				intersectDfa.addTransition(crossStateNumber, symbol, firstNextState * secondDfa.numStates + secondNextState);
			}
		}
	}
	
	return intersectDfa;
}

//==============================================================================
// Dfa Dfa::getSymmetricDifference()
//------------------------------------------------------------------------------
Dfa Dfa::getSymmetricDifference(Dfa &firstDfa, Dfa &secondDfa, Alphabet alphabet) {
	
	// !L(B)
	Dfa notSecondDfa = Dfa::getComplement(secondDfa);

	// L(A) intersect !L(B)
	Dfa leftHand = Dfa::getIntersection(firstDfa, notSecondDfa, alphabet);

	// !L(A)
	Dfa notFirstDfa = Dfa::getComplement(firstDfa);

	// !L(A) intersect L(B)
	Dfa rightHand = Dfa::getIntersection(notFirstDfa, secondDfa, alphabet);

	// (L(A) intersect !L(B)) union (!L(A) intersect L(B))
	return Dfa::getUnion(leftHand, rightHand, alphabet);
}

//==============================================================================
// Dfa Dfa::getUnion()
//------------------------------------------------------------------------------
Dfa Dfa::getUnion(Dfa &firstDfa, Dfa &secondDfa, Alphabet alphabet) {
	
	Dfa unionDfa;
	
	// Q = {(r1, r2) | r1 in Q1 and r2 in Q2)}
	std::map<String, std::pair<int, bool>>::iterator firstIt;
	std::map<String, std::pair<int, bool>>::iterator secondIt;
	
	// Add states and accept states
	for (firstIt = firstDfa.states.begin(); firstIt != firstDfa.states.end(); firstIt++) {
		for (secondIt = secondDfa.states.begin(); secondIt != secondDfa.states.end(); secondIt++) {
			
			String cross = std::to_string(firstIt->second.first) + std::to_string(secondIt->second.first);
			bool isAcceptState = firstIt->second.second || secondIt->second.second;
			
			unionDfa.addState(cross, isAcceptState);
		}
	}

	// d((r1, r2), a) = (d(r1, a), d(r2, a))
	// Add transitions
	for (firstIt = firstDfa.states.begin(); firstIt != firstDfa.states.end(); firstIt++) {
		for (secondIt = secondDfa.states.begin(); secondIt != secondDfa.states.end(); secondIt++) {
			for (char symbol : alphabet.getSymbols()) {
				
				String cross = std::to_string(firstIt->second.first) + std::to_string(secondIt->second.first);
				int crossStateNumber = unionDfa.getStateNumber(cross);
				
				int firstNextState = firstDfa.transitionTable[std::pair<int, char>(firstIt->second.first, symbol)];
				int secondNextState = secondDfa.transitionTable[std::pair<int, char>(secondIt->second.first, symbol)];
			
				unionDfa.addTransition(crossStateNumber, symbol, firstNextState * secondDfa.numStates + secondNextState);
			}
		}
	}
	
	return unionDfa;
}