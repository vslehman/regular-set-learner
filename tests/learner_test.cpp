#include "learner_test.h"

bool LearnerTest_init() {
	return false;
}

bool LearnerTest_outputDfa() {
	return false;
}

bool LearnerTest_resolveNotClosed() {
	return false;
}

bool LearnerTest_resolveNotConsistent() {
	return false;
}

bool LearnerTest_extendT() {
	return false;
}

bool LearnerTest::runTests() {

	test("init", &LearnerTest_init);
	test("resolveNotClosed", &LearnerTest_resolveNotClosed);
	test("resolveNotConsistent", &LearnerTest_resolveNotConsistent);
	test("extendT", &LearnerTest_extendT);
}