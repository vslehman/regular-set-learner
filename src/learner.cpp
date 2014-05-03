////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <stdlib.h>

#include "common.hpp"
#include "learner.hpp"

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
	
	askAlphabet(teacher);
	
	// Initialize S and E to {epsilon}.
	init();
	
	// Ask membership query for epsilon
	makeMembershipQuery(EMPTY_STRING, EMPTY_STRING, EMPTY_STRING, teacher);

	// Ask membership queries for each a in A
	for (char symbol : alphabet->getSymbols()) {
	
		if (symbol == EMPTY_CHAR) {
			makeMembershipQuery(EMPTY_STRING, EMPTY_STRING, EMPTY_STRING, teacher);
		}
		else {
			String symbolString(1, symbol);
			makeMembershipQuery(symbolString, EMPTY_STRING, symbolString, teacher);
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
		if (makeConjecture(teacher)) {
			conjectureIsIncorrect = false;
		} // The learner was incorrect
		else {
			printCounterExamplePrompt();
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
			
			// Is the information already in the table?
			if (observeTable.isInTable(query)) {
				observeTable.addEntry(s, e, observeTable.isMember(query));
			} // Need to ask the teacher
			else {
				makeMembershipQuery(s, e, query, teacher);
			}
		}
	}
	
	// Ask S . A . E
	for (String s : setS) {
		for (char a : alphabet->getSymbols()) {
			for (String e : setE) {

				String query = s + a;
				
				// Is the information already in the table?
				if (observeTable.isInTable(query + e)) {
					observeTable.addEntry(query, e, observeTable.isMember(query + e));
				} // Need to ask the teacher
				else {
					makeMembershipQuery(query, e, query + e, teacher);
				}
			}
		}
	}
}

//==============================================================================
// void Learner::askAlphabet()
//------------------------------------------------------------------------------
void Learner::askAlphabet(Teacher &teacher) {
	printAlphabetPrompt();
	alphabet = teacher.askAlphabet();
}

//==============================================================================
// bool Learner::makeConjecture()
//------------------------------------------------------------------------------
bool Learner::makeConjecture(Teacher &teacher) {
	std::cout << "Is this a correct acceptor for the language?" << std::endl;
	std::unique_ptr<Dfa> dfa = observeTable.getDfaRepresentation(*alphabet);
	std::cout << dfa->toString() << std::endl;
	std::cout << "(Y)es or (N)o?\n";
	
	bool result = teacher.makeConjecture(*(dfa.get()));
	
	return result;
}

//==============================================================================
// void Learner::makeMembershipQuery()
//------------------------------------------------------------------------------
void Learner::makeMembershipQuery(String s, String e, String query, Teacher &teacher) {
	printMembershipPrompt(query);
	observeTable.addEntry(s, e, teacher.askMembership(query));
}

//==============================================================================
// void Learner::printAlphabetPrompt()
//------------------------------------------------------------------------------
void Learner::printAlphabetPrompt() {
	std::cout << "Please enter each symbol in the alphabet followed by the return key\n";
	std::cout << "Type 'end' followed by the return key to finalize the alphabet\n";
}

//==============================================================================
// void Learner::printCounterExamplePrompt()
//------------------------------------------------------------------------------
void Learner::printCounterExamplePrompt() {
	std::cout << "Please provide a counter-example:";
	std::cout << "> ";
}

//==============================================================================
// void Learner::printMembershipPrompt()
//------------------------------------------------------------------------------
void Learner::printMembershipPrompt(String query) {
	
	// Print unicode epsilon
	if (query == EMPTY_STRING) {
		query = EPSILON_STRING;
	}
	
	std::cout << "\nIs " + query + " a member of the unknown regular set?\n";
	std::cout << "(Y)es or (N)o?\n";
	std::cout << "> ";
}