////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "auto_teacher.hpp"
#include "common.hpp"

//==============================================================================
// bool AutoTeacher::AutoTeacher()
//------------------------------------------------------------------------------
AutoTeacher::AutoTeacher(String filename) {
	dfaFile = filename;
	// Initialize dfa and get alphabet
	alphabet = unknownSetDfa.loadFromFile(filename);
}

//==============================================================================
// bool AutoTeacher::askMembership()
//------------------------------------------------------------------------------
bool AutoTeacher::askMembership(String query) {
	bool isMember = unknownSetDfa.doesAcceptString(query);
	std::cout << isMember << std::endl;
	return isMember;
}

//==============================================================================
// std::unique_ptr<Alphabet> AutoTeacher::askAlphabet()
//------------------------------------------------------------------------------
Alphabet AutoTeacher::askAlphabet() {
	return alphabet;
}

//==============================================================================
// bool AutoTeacher::makeConjecture()
//------------------------------------------------------------------------------
bool AutoTeacher::makeConjecture(Dfa &conjectureDfa) {
	// Get symmetric difference dfa
	Dfa symDiffDfa = Dfa::getSymmetricDifference(unknownSetDfa, conjectureDfa, alphabet);
	
	lastSymmetricDifferenceDfa = symDiffDfa;
	
	// If symmetric difference dfa accepts nothing, accept
	// Otherwise, reject
	bool areSameLanguage = symDiffDfa.acceptsNothing();
	std::cout << areSameLanguage << std::endl;
	std::cout << "Press enter to continue" << std::endl;
	std::cin.ignore();
	return areSameLanguage;
}

//==============================================================================
// String AutoTeacher::getCounterExample()
//------------------------------------------------------------------------------
String AutoTeacher::getCounterExample() {
	// Find string accepted by dfa
	return lastSymmetricDifferenceDfa.getAcceptedString(alphabet);
}