////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef DEMO_TEACHER_HPP
#define DEMO_TEACHER_HPP

#include <queue>

#include "common.hpp"
#include "teacher.hpp"

class DemoTeacher : public Teacher {
public:
	DemoTeacher(String filename, int playbackSpeed);
	bool askMembership(String query);
	bool makeConjecture(Dfa &dfa);
	
	Alphabet askAlphabet();
	String getCounterExample();
	
private:
	String getResponse();
	bool isYes(String s);
	bool isNo(String s);
	std::queue<String> responses;
	int playbackPause;
};

#endif