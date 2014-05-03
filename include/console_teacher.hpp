////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef CONSOLE_TEACHER_HPP
#define CONSOLE_TEACHER_HPP

#include <queue>

#include "common.hpp"
#include "teacher.hpp"

class ConsoleTeacher : public Teacher {
public:
	bool askMembership(String query);
	bool makeConjecture(std::unique_ptr<Dfa> dfa);
	
	std::unique_ptr<Alphabet> askAlphabet();
	String getCounterExample();

private:
	void writeDemoToFile();
	void printMembershipPrompt(String query);
	bool isYes(String s);
	bool isNo(String s);
	
	std::queue<String> inputRecorder;
};

#endif