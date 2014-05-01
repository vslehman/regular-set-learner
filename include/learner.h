////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef LEARNER_H
#define LEARNER_H

#include "common.h"
#include "observation_table.h"
#include "teacher.h"

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
	std::unique_ptr<Alphabet> alphabet;
	ObservationTable observeTable;
};

#endif