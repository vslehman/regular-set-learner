////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef CONSOLE_TEACHER_H
#define CONSOLE_TEACHER_H

#include "teacher.h"

class ConsoleTeacher : public Teacher {
public:
	bool askMembership(std::string query);
	bool makeConjecture(std::unique_ptr<Dfa> dfa);
	
	std::unique_ptr<Alphabet> askAlphabet();
	std::string getCounterExample();

private:
	void printMembershipPrompt(std::string query);
};

#endif