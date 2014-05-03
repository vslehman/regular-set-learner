////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>

#include "common.hpp"
#include "console_teacher.hpp"

//==============================================================================
// bool ConsoleTeacher::askMembership()
//------------------------------------------------------------------------------
bool ConsoleTeacher::askMembership(String query) {
	
	String input = "NULL";
	
	while (true) {
		
		printMembershipPrompt(query);
		
		std::cin >> input;
		
		if (isYes(input)) {
			inputRecorder.push(input);
			std::cout << std::endl;
			return true;
		}
		else if (isNo(input)) {
			inputRecorder.push(input);
			std::cout << std::endl;
			return false;
		}
		else {
			std::cout << "Error on input\n";
			input = "NULL";
		}
	}
}

//==============================================================================
// std::unique_ptr<Alphabet> ConsoleTeacher::askAlphabet()
//------------------------------------------------------------------------------
std::unique_ptr<Alphabet> ConsoleTeacher::askAlphabet() {
	std::cout << "Please enter each symbol in the alphabet followed by the return key\n";
	std::cout << "Type 'end' followed by the return key to finalize the alphabet\n";
	
	std::unique_ptr<Alphabet> alphabet(new Alphabet);
	String input = "NULL";
	
	while (input != "end") {
		std::cout << "> ";
		std::cin >> input;
		
		if (input == "end") {
			inputRecorder.push(input);
			break;
		}
		else if (input.length() > 1) {
			std::cout << "Please enter only one symbol at a time.\n";
		}
		else {
			inputRecorder.push(input);
			alphabet->addSymbol(input.at(0));
		}
	}
	
	std::cout << "\n" + alphabet->toString() + "\n" << std::endl;
	
	return alphabet;
}

//==============================================================================
// bool ConsoleTeacher::makeConjecture()
//------------------------------------------------------------------------------
bool ConsoleTeacher::makeConjecture(std::unique_ptr<Dfa> dfa) {
	std::cout << dfa->toString() << std::endl;
	
	std::cout << "Is this a correct acceptor for the language?" << std::endl;
	std::cout << "(Y)es or (N)o?\n";
	
	String input = "NULL";
	
	while (input == "NULL") {
		std::cout << "> ";
		std::cin >> input;
		
		if (isYes(input)) {
			writeDemoToFile();
			return true;
		}
		else if (isNo(input)) {
			return false;
		}
		else {
			std::cout << "Error on input\n";
			input = "NULL";
		}
	}
	
	return false;
}

//==============================================================================
// String ConsoleTeacher::getCounterExample()
//------------------------------------------------------------------------------
String ConsoleTeacher::getCounterExample() {
	std::cout << "Please provide a counter-example:";
	std::cout << "> ";
	
	String input;
	std::cin >> input;
	
	inputRecorder.push(input);
	
	return input;
}

//==============================================================================
// void ConsoleTeacher::printMembershipPrompt()
//------------------------------------------------------------------------------
void ConsoleTeacher::printMembershipPrompt(String query) {

	// Print unicode epsilon
	if (query == EMPTY_STRING) {
		query = EPSILON_STRING;
	}
	
	std::cout << "\nIs " + query + " a member of the unknown regular set?\n";
	std::cout << "(Y)es or (N)o?\n";
	std::cout << "> ";
}

//==============================================================================
// bool ConsoleTeacher::isYes()
//------------------------------------------------------------------------------
bool ConsoleTeacher::isYes(String s) {
	if (s == "Y" || s == "y" || s == "yes" || s == "1") {
		return true;
	}
	else {
		return false;
	}
}

//==============================================================================
// bool ConsoleTeacher::isNo()
//------------------------------------------------------------------------------
bool ConsoleTeacher::isNo(String s) {
	if (s == "N" || s == "n" || s == "no" || s == "0") {
		return true;
	}
	else {
		return false;
	}
}

//==============================================================================
// void ConsoleTeacher::writeDemoToFile()
//------------------------------------------------------------------------------
void ConsoleTeacher::writeDemoToFile() {
	std::cout << "Save demo as:" << std::endl;
	std::cout << "> ";
	
	String filename;
	std::cin >> filename;
	
	// Write demo to file
	
	std::ofstream outFile("demo/" + filename);
	if (outFile.is_open())
	{
		while (!inputRecorder.empty()) {
			outFile << inputRecorder.front() + "\n";
			inputRecorder.pop();
		}
		
		outFile.close();
	}
	
	system("dot -Tpdf tmp/tmp.dot -o tmp/tmp.pdf > /dev/null 2>&1");
	system("open tmp/tmp.pdf");


}