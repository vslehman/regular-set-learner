////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef TABLE_TEST_HPP
#define TABLE_TEST_HPP

#include "observation_table.hpp"
#include "test.hpp"

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