////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef LEARNER_TEST_HPP
#define LEARNER_TEST_HPP

#include "learner.hpp"
#include "test.hpp"

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