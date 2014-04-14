////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include "learner.h"
#include "common.h"

//==============================================================================
// Learner::Learner()
//------------------------------------------------------------------------------
Learner::Learner() {
	
}

//==============================================================================
// void Learner::start()
//------------------------------------------------------------------------------
#include <iostream>
void Learner::start(Teacher &teacher) {
	
	alphabet = teacher.askAlphabet();
	
	// Initialize S and E to {epsilon}.
	init();
	
	// Ask membership query for epsilon
	observeTable.addEntry(EMPTY_STRING, EMPTY_STRING, teacher.askMembership(EMPTY_STRING));

	// Ask membership queries for each a in A
	for (char symbol : alphabet->getSymbols()) {
	
		if (symbol == EMPTY_CHAR) {
			observeTable.addEntry(EMPTY_STRING, EMPTY_STRING, teacher.askMembership(EMPTY_STRING));
		}
		else {
			std::string symbolString(1, symbol);
			observeTable.addEntry(symbolString, EMPTY_STRING, teacher.askMembership(symbolString));
		}
	}
	
	// Construct the initial observation table (S, E, T)
	std::cout << observeTable.toString() << std::endl;;
	
	bool conjectureIsIncorrect = true;
	
	while (conjectureIsIncorrect) {
		
		while (!observeTable.isClosed(*alphabet) || !observeTable.isConsistent(*alphabet)) {
			
			if (!observeTable.isConsistent(*alphabet)) {
				resolveNotConsistent();
			}
			if (!observeTable.isClosed(*alphabet)) {
				resolveNotClosed();
			}
			break;
		}
		
		// The learner was correct
		if (teacher.makeConjecture(observeTable.getDfaRepresentation())) {
			conjectureIsIncorrect = false;
		} // The learner was incorrect
		else {
			std::string t = teacher.getCounterExample();
			
			// Add t and all its prefixes to S
			for (int length = t.length(); length > 0; length--) {
				observeTable.addEntry(t.substr(0, length), EMPTY_STRING, teacher.askMembership(t.substr(0, length)));
			}
		}
	}
	
	outputDfa();
}

//==============================================================================
// void Learner::init()
//------------------------------------------------------------------------------
void Learner::init() {
	observeTable.addStringToS(EMPTY_STRING);
	observeTable.addStringToE(EMPTY_STRING);
}

//==============================================================================
// void Learner::outputDfa()
//------------------------------------------------------------------------------
void Learner::outputDfa() {
	
}

//==============================================================================
// void Learner::resolveNotClosed()
//------------------------------------------------------------------------------
void Learner::resolveNotClosed() {
	
}

//==============================================================================
// void Learner::resolveNotConsistent()
//------------------------------------------------------------------------------
void Learner::resolveNotConsistent() {
	
}