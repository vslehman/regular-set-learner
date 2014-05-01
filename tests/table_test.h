#ifndef TABLE_TEST_H
#define TABLE_TEST_H

#include "test.h"
#include "observation_table.h"

class TableTest : public Test {
	friend class ObservationTable;
	
public:
	
private:
	bool runTests();
};

bool TableTest_isClosed();
bool TableTest_isConsistent();
bool TableTest_resolveNotClosed();
bool TableTest_resolveNotConsistent();
bool TableTest_addStringToS();
bool TableTest_addStringToE();
bool TableTest_addEntry();
bool TableTest_isInTable();
bool TableTest_isMember();
bool TableTest_row();
bool TableTest_areRowsEqual();

#endif