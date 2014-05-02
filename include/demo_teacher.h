////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef DEMO_TEACHER_H
#define DEMO_TEACHER_H

#include <queue>

#include "common.h"
#include "teacher.h"

class DemoTeacher : public Teacher {
public:
	DemoTeacher(String filename, int playbackSpeed);
	bool askMembership(String query);
	bool makeConjecture(std::unique_ptr<Dfa> dfa);
	
	std::unique_ptr<Alphabet> askAlphabet();
	String getCounterExample();
	
private:
	void printMembershipPrompt(String query);
	String getResponse();
	bool isYes(String s);
	bool isNo(String s);
	std::queue<String> responses;
	int playbackPause;
};

#endif