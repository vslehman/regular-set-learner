////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef LEARNER_H
#define LEARNER_H

#include "teacher.h"
#include "observation_table.h"

class Alphabet;

class Learner {
public:
	Learner();
	
	void start(Teacher &teacher);
	
private:
	void init();
	void outputDfa();
	
	void resolveNotClosed();
	void resolveNotConsistent();
	
private:
	std::unique_ptr<Alphabet> alphabet;
	ObservationTable observeTable;
};

#endif