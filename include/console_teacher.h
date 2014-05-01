////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef CONSOLE_TEACHER_H
#define CONSOLE_TEACHER_H

#include "common.h"
#include "teacher.h"

class ConsoleTeacher : public Teacher {
public:
	bool askMembership(String query);
	bool makeConjecture(std::unique_ptr<Dfa> dfa);
	
	std::unique_ptr<Alphabet> askAlphabet();
	String getCounterExample();

private:
	void printMembershipPrompt(String query);
	bool isYes(String s);
	bool isNo(String s);
};

#endif