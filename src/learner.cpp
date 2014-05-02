////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <stdlib.h>
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
			String symbolString(1, symbol);
			observeTable.addEntry(symbolString, EMPTY_STRING, teacher.askMembership(symbolString));
		}
	}
	
	// Construct the initial observation table (S, E, T)
	std::cout << observeTable.toStringTable() << std::endl;
	
	bool conjectureIsIncorrect = true;
	
	while (conjectureIsIncorrect) {
		
		while (!observeTable.isClosed(*alphabet) || !observeTable.isConsistent(*alphabet)) {
			
			if (!observeTable.isConsistent(*alphabet)) {
				std::cout << "Table is not consistent..." << std::endl;
				resolveNotConsistent(teacher);
			}
			if (!observeTable.isClosed(*alphabet)) {
				std::cout << "Table is not closed..." << std::endl;
				resolveNotClosed(teacher);
			}
		}
		std::cout << observeTable.toStringSets() << std::endl;
		std::cout << observeTable.toStringTable() << std::endl;
		
		outputDfa();
		
		// The learner was correct
		if (teacher.makeConjecture(observeTable.getDfaRepresentation(*alphabet))) {
			conjectureIsIncorrect = false;
		} // The learner was incorrect
		else {
			String t = teacher.getCounterExample();
			
			// Add t and all its prefixes to S
			for (int length = t.length(); length > 0; length--) {
				observeTable.addStringToS(t.substr(0, length));
			}
			
			// Extend T to (S u S . A) . E using membership queries
			extendT(teacher);
			
		}
		
		std::cout << observeTable.toStringSets() << std::endl;
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
	
	// Write dot file
	std::unique_ptr<Dfa> dfa = observeTable.getDfaRepresentation(*alphabet);
	String dotFileString = dfa->toGraphVizString();
	
	std::ofstream outFile("tmp/tmp.dot");
	if (outFile.is_open())
	{
		outFile << dotFileString;
		outFile.close();
	}
	
	system("dot -Tpdf tmp/tmp.dot -o tmp/tmp.pdf > /dev/null 2>&1");
	system("open tmp/tmp.pdf");
}

//==============================================================================
// void Learner::resolveNotClosed()
//------------------------------------------------------------------------------
void Learner::resolveNotClosed(Teacher &teacher) {
	std::cout << "Resolving...\n";

	observeTable.resolveNotClosed(*alphabet);
	
	// Extend T to (S u S . A) . E using membership queries
	extendT(teacher);
	
	std::cout << "...Done\n\n";
}

//==============================================================================
// void Learner::resolveNotConsistent()
//------------------------------------------------------------------------------
void Learner::resolveNotConsistent(Teacher &teacher) {
	std::cout << "...resolving\n";
	
	observeTable.resolveNotConsistent(*alphabet);
	
	// Extend T to (S u S . A) . E using membership queries
	extendT(teacher);
	
	std::cout << "...Done\n\n";
}

//==============================================================================
// void Learner::extendT()
//------------------------------------------------------------------------------
void Learner::extendT(Teacher& teacher) {
	
	const std::set<String>& setS = observeTable.getS();
	const std::set<String>& setE = observeTable.getE();
	
	// Ask S . E
	for (String s : setS) {
		for (String e : setE) {
			String query = s + e;
			
			if (!observeTable.isInTable(s, e)) {
				observeTable.addEntry(s, e, teacher.askMembership(query));
			}
		}
	}
	
	// Ask S . A . E
	for (String s : setS) {
		for (char a : alphabet->getSymbols()) {
			for (String e : setE) {

				String query = s + a;

				if (!observeTable.isInTable(query, e)) {
					observeTable.addEntry(query, e, teacher.askMembership(query + e));
				}
			}
		}
	}
}