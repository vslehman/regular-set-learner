////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "common.hpp"
#include "demo_teacher.hpp"

//==============================================================================
// bool DemoTeacher::DemoTeacher()
//------------------------------------------------------------------------------
DemoTeacher::DemoTeacher(String filename, int playbackSpeed) {

	// Playback speed [0-10] slow to fast
	// Pause in microseconds
	playbackPause = (10 - playbackSpeed) * 500000;
	
	std::cout << "Loading demo file...\n";
	String line;
	std::ifstream inFile(filename);
	
	if (inFile.is_open())
	{
		while (getline(inFile,line))
		{
			responses.push(line);
		}
		
		inFile.close();
	}
	
	std::cout << "...Done\n";

}

//==============================================================================
// bool DemoTeacher::askMembership()
//------------------------------------------------------------------------------
bool DemoTeacher::askMembership(String query) {
	
	String input = "NULL";
	
	while (true) {
		
		input = getResponse();
		std::cout << input << std::endl;
		
		if (isYes(input)) {
			std::cout << std::endl;
			return true;
		}
		else if (isNo(input)) {
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
// std::unique_ptr<Alphabet> DemoTeacher::askAlphabet()
//------------------------------------------------------------------------------
Alphabet DemoTeacher::askAlphabet() {
	
	Alphabet alphabet;
	String input = "NULL";

	while (input != "end") {
		std::cout << "> ";
		input = getResponse();
		std::cout << input << std::endl;
		if (input == "end") {
			break;
		}
		else if (input.length() > 1) {
			std::cout << "Please enter only one symbol at a time.\n";
		}
		else {
			alphabet.addSymbol(input.at(0));
		}
	}
	
	std::cout << "\n" + alphabet.toString() + "\n" << std::endl;
	
	return alphabet;
}

//==============================================================================
// bool DemoTeacher::makeConjecture()
//------------------------------------------------------------------------------
bool DemoTeacher::makeConjecture(Dfa &dfa) {
	
	String input = "NULL";
	
	while (input == "NULL") {
		std::cout << "> ";
		std::cin >> input;
		
		if (isYes(input)) {
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
// String DemoTeacher::getCounterExample()
//------------------------------------------------------------------------------
String DemoTeacher::getCounterExample() {
	
	String input;
	input = getResponse();
	std::cout << input << std::endl;
	
	return input;
}

//==============================================================================
// bool DemoTeacher::isYes()
//------------------------------------------------------------------------------
bool DemoTeacher::isYes(String s) {
	if (s == "Y" || s == "y" || s == "yes" || s == "1") {
		return true;
	}
	else {
		return false;
	}
}

//==============================================================================
// bool DemoTeacher::isNo()
//------------------------------------------------------------------------------
bool DemoTeacher::isNo(String s) {
	if (s == "N" || s == "n" || s == "no" || s == "0") {
		return true;
	}
	else {
		return false;
	}
}

//==============================================================================
// String DemoTeacher::getResponse()
//------------------------------------------------------------------------------
String DemoTeacher::getResponse() {
	String temp = responses.front();
	responses.pop();
	usleep(playbackPause);
	return temp;
}