#ifndef TEST_H
#define TEST_H

#include <string>

class Test;
typedef bool (*Callback)(void);

class Test {
public:
	bool test(std::string name, Callback c);
	bool startTests();
	
private:
	virtual bool runTests() = 0;
	int numFailedTests;
	int numPassedTests;
};

#endif