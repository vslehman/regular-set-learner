#ifndef LEARNER_TEST_H
#define LEARNER_TEST_H

#include "test.h"
#include "learner.h"

class LearnerTest : public Test {
	friend class Learner;
	
public:
	
private:
	bool runTests();
};

bool LearnerTest_init();
bool LearnerTest_outputDfa();
bool LearnerTest_resolveNotClosed();
bool LearnerTest_resolveNotConsistent();
bool LearnerTest_extendT();

#endif