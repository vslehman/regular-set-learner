////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef LEARNER_HPP
#define LEARNER_HPP

#include "common.hpp"
#include "observation_table.hpp"
#include "teacher.hpp"

class Alphabet;

class Learner {
public:
	Learner();
	
	void start(Teacher &teacher);
	
private:
	void init();
	void outputDfa();
	
	void resolveNotClosed(Teacher &teacher);
	void resolveNotConsistent(Teacher &teacher);
	
	void extendT(Teacher &teacher);
	
private:
	void askAlphabet(Teacher &teacher);
	bool makeConjecture(Teacher &teacher);
	void makeMembershipQuery(String s, String e, String query, Teacher &teacher);
	
	void printAlphabetPrompt();
	void printCounterExamplePrompt();
	void printMembershipPrompt(String query);
	
	Alphabet alphabet;
	ObservationTable observeTable;
};

#endif