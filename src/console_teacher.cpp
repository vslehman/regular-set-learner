////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include "console_teacher.h"
#include <iostream>
#include "common.h"

//==============================================================================
// bool ConsoleTeacher::askMembership()
//------------------------------------------------------------------------------
bool ConsoleTeacher::askMembership(std::string query) {
	
	std::string input = "NULL";
	
	while (true) {
		
		printMembershipPrompt(query);
		
		std::cin >> input;
		
		if (input == "1") {
			return true;
		}
		else if (input == "0") {
			return false;
		}
		
		std::cout << "Error on input\n";
		input = "NULL";
	}
}

//==============================================================================
// std::unique_ptr<Alphabet> ConsoleTeacher::askMembership()
//------------------------------------------------------------------------------
std::unique_ptr<Alphabet> ConsoleTeacher::askAlphabet() {
	std::cout << "Please enter each symbol in the alphabet followed by the return key\n";
	std::cout << "Type 'end' followed by the return key to finalize the alphabet\n";
	
	std::unique_ptr<Alphabet> alphabet(new Alphabet);
	std::string input = "NULL";
	
	while (input != "end") {
		std::cout << "> ";
		std::cin >> input;
		
		if (input == "end") {
			break;
		}
		else if (input.length() > 1) {
			std::cout << "Please enter only one symbol at a time.\n";
		}
		else {
			alphabet->addSymbol(input.at(0));
		}
	}
	
	std::cout << alphabet->toString() << std::endl;
	
	return alphabet;
}

//==============================================================================
// bool ConsoleTeacher::makeConjecture()
//------------------------------------------------------------------------------
bool ConsoleTeacher::makeConjecture(std::unique_ptr<Dfa> dfa) {
	return false;
}

//==============================================================================
// std::string ConsoleTeacher::getCounterExample()
//------------------------------------------------------------------------------
std::string ConsoleTeacher::getCounterExample() {
	std::cout << "Please provide a counter-example:";
	std::cout << "> ";
	
	std::string input;
	std::cin >> input;
	
	return input;
}

//==============================================================================
// void ConsoleTeacher::printMembershipPrompt()
//------------------------------------------------------------------------------
void ConsoleTeacher::printMembershipPrompt(std::string query) {

	// Print unicode epsilon
	if (query == EMPTY_STRING) {
		query = EPSILON_STRING;
	}
	
	std::cout << "Is " + query + " a member of the unknown regular set?\n";
	std::cout << "0.) No\n";
	std::cout << "1.) Yes\n";
	std::cout << "> ";
}