////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef AUTO_TEACHER_HPP
#define AUTO_TEACHER_HPP

#include "common.hpp"
#include "dfa.hpp"
#include "teacher.hpp"

class AutoTeacher : public Teacher {
public:
	AutoTeacher(String filename);
	bool askMembership(String query);
	bool makeConjecture(Dfa &conjectureDfa);
	
	Alphabet askAlphabet();
	String getCounterExample();
	
private:
	Alphabet alphabet;
	String dfaFile;
	Dfa unknownSetDfa;
	Dfa lastSymmetricDifferenceDfa;
};

#endif