#include <iostream>
#include "test.h"

bool Test::test(std::string name, Callback c) {
	std::cout << "Testing " + name + "...\n";
	
	bool status = (*c)();
	
	if (status == true) {
		numPassedTests++;
		std::cout << "...PASSED\n";
	}
	else {
		numFailedTests++;
		std::cout << "...FAILED\n";
	}
	
	return status;
}

bool Test::startTests() {
	runTests();
	std::cout << "Tests passed: " + std::to_string(numPassedTests) +
	             " Tests failed: " + std::to_string(numFailedTests) + "\n";
}