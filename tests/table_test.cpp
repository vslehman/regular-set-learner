////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "table_test.hpp"

bool TableTest_isClosed() {
	
	// Table is not closed
	Alphabet a;
	a.addSymbol('0');
	a.addSymbol('1');
	
	// Figure 2
	ObservationTable table1;
	table1.addEntry("", "", true);
	table1.addEntry("0", "", false);
	table1.addEntry("1", "", false);
	
	table1.addStringToS("");
	table1.addStringToE("");
	
	if (table1.isClosed(a)) {
		std::cout << "Closed" << std::endl;
		return false;
	}
	
	// Table is closed
	// Figure 3
	ObservationTable table2;
	table2.addEntry("", "", true);
	table2.addEntry("0", "", false);
	table2.addEntry("1", "", false);
	table2.addEntry("00", "", true);
	table2.addEntry("01", "", false);
	
	table2.addStringToS("");
	table2.addStringToS("0");
	table2.addStringToE("");
	
	if (!table2.isClosed(a)) {
		return false;
	}
	
	return true;
	
}

bool TableTest_isConsistent() {
	
	
	// Table is not consistent
	Alphabet a;
	a.addSymbol('0');
	a.addSymbol('1');
	
	// Figure 8
	ObservationTable table1;
	table1.addStringToS("");
	table1.addStringToS("0");
	table1.addStringToS("1");
	table1.addStringToS("11");
	table1.addStringToS("01");
	table1.addStringToS("011");
	
	table1.addStringToE("");
	table1.addStringToE("0");
	
	table1.addEntry("", "", true);
	table1.addEntry("", "0", false);
	table1.addEntry("0", "", false);
	table1.addEntry("0", "0", true);
	table1.addEntry("1", "", false);
	table1.addEntry("1", "0", false);
	table1.addEntry("11", "", true);
	table1.addEntry("11", "0", false);
	table1.addEntry("01", "", false);
	table1.addEntry("01", "0", false);
	table1.addEntry("011", "", false);
	table1.addEntry("011", "0", true);
	table1.addEntry("00", "", true);
	table1.addEntry("00", "0", false);
	table1.addEntry("10", "", false);
	table1.addEntry("10", "0", false);
	table1.addEntry("110", "", false);
	table1.addEntry("110", "0", true);
	table1.addEntry("111", "", false);
	table1.addEntry("111", "0", false);
	table1.addEntry("010", "", false);
	table1.addEntry("010", "0", false);
	table1.addEntry("0110", "", true);
	table1.addEntry("0110", "0", false);
	table1.addEntry("0111", "", false);
	table1.addEntry("0111", "0", false);
	
	if (table1.isConsistent(a)) {
		std::cout << "Consistent" << std::endl;
		return false;
	}
	
	// Table is Consistent
	ObservationTable table2;
	table2.addEntry("", "", true);
	table2.addEntry("0", "", false);
	table2.addEntry("1", "", false);
	table2.addEntry("01", "", false);
	
	if (!table2.isConsistent(a)) {
		return false;
	}
	
	return true;
}

bool TableTest_resolveNotClosed() {
	// Table is not closed
	Alphabet a;
	a.addSymbol('0');
	a.addSymbol('1');
	
	// Figure 2
	ObservationTable table1;
	table1.addEntry("", "", true);
	table1.addEntry("0", "", false);
	table1.addEntry("1", "", false);
	
	table1.addStringToS("");
	table1.addStringToE("");
	
	if (table1.getS().count("0") != 0) {
		return false;
	}
	
	table1.resolveNotClosed(a);
	
	if (table1.getS().count("0") != 1) {
		return false;
	}

	return true;
}

bool TableTest_resolveNotConsistent() {
	// Table is not consistent
	Alphabet a;
	a.addSymbol('0');
	a.addSymbol('1');
	
	// Figure 8
	ObservationTable table1;
	table1.addStringToS("");
	table1.addStringToS("0");
	table1.addStringToS("1");
	table1.addStringToS("11");
	table1.addStringToS("01");
	table1.addStringToS("011");
	
	table1.addStringToE("");
	table1.addStringToE("0");
	
	table1.addEntry("", "", true);
	table1.addEntry("", "0", false);
	table1.addEntry("0", "", false);
	table1.addEntry("0", "0", true);
	table1.addEntry("1", "", false);
	table1.addEntry("1", "0", false);
	table1.addEntry("11", "", true);
	table1.addEntry("11", "0", false);
	table1.addEntry("01", "", false);
	table1.addEntry("01", "0", false);
	table1.addEntry("011", "", false);
	table1.addEntry("011", "0", true);
	table1.addEntry("00", "", true);
	table1.addEntry("00", "0", false);
	table1.addEntry("10", "", false);
	table1.addEntry("10", "0", false);
	table1.addEntry("110", "", false);
	table1.addEntry("110", "0", true);
	table1.addEntry("111", "", false);
	table1.addEntry("111", "0", false);
	table1.addEntry("010", "", false);
	table1.addEntry("010", "0", false);
	table1.addEntry("0110", "", true);
	table1.addEntry("0110", "0", false);
	table1.addEntry("0111", "", false);
	table1.addEntry("0111", "0", false);
	
	if (table1.getE().count("1") != 0) {
		return false;
	}
	
	table1.resolveNotConsistent(a);
	
	if (table1.getE().count("1") != 1) {
		return false;
	}
	
	return true;
}

bool TableTest_addStringToS() {
	ObservationTable table;
	table.addStringToS("001");
	
	if (table.getS().count("001") != 1) {
		return false;
	}
	
	return true;
}

bool TableTest_addStringToE() {
	ObservationTable table;
	table.addStringToE("001");
	
	if (table.getE().count("001") != 1) {
		return false;
	}
	
	return true;
}

bool TableTest_addEntry() {
	ObservationTable table;
	table.addEntry("0", "0", true);
	
	if (table.isInTable("0", "0") != true) {
		return false;
	}
	
	if (table.isInTable("1", "0") == true) {
		return false;
	}
	
	return true;
}

bool TableTest_isInTable() {
	ObservationTable table;
	table.addEntry("0", "0", true);
	
	if (table.isInTable("0", "0") != true) {
		return false;
	}
	
	if (table.isInTable("1", "0") == true) {
		return false;
	}
	
	return true;
}

bool TableTest_isMember() {
	ObservationTable table;
	table.addEntry("0", "0", true);
	
	if (table.isMember("0", "0") != true) {
		return false;
	}

	
	if (table.isMember("00") != true) {
		return false;
	}

	
	if (table.isMember("1") == true) {
		return false;
	}
	
	return true;
}

bool TableTest_row() {
	ObservationTable table;
	
	table.addStringToS("");
	table.addStringToE("");
	table.addStringToE("0");
	table.addStringToE("1");
	
	table.addEntry("", "", true);
	table.addEntry("", "0", false);
	table.addEntry("", "1", false);
	
	if (table.row("") != "100") {
		return false;
	}
	
	if (table.row("1") == "100") {
		return false;
	}
	
	return true;
}

bool TableTest_areRowsEqual() {
	ObservationTable table;
	
	table.addStringToS("");
	table.addStringToE("");
	table.addStringToE("0");
	table.addStringToE("1");
	
	table.addEntry("", "", true);
	table.addEntry("", "0", false);
	table.addEntry("", "1", false);
	
	table.addEntry("0", "", true);
	table.addEntry("0", "0", false);
	table.addEntry("0", "1", false);
	
	table.addEntry("0", "1", true);
	table.addEntry("0", "1", false);
	table.addEntry("0", "1", false);
	
	// Rows should be equal
	if (!table.areRowsEqual("", "0")) {
		return false;
	}
	
	// Rows should not be equal
	if (table.areRowsEqual("", "1")) {
		return false;
	}
	
	return true;
}

bool TableTest::runTests() {
	test("isClosed", &TableTest_isClosed);
	test("isConsistent", &TableTest_isConsistent);
	test("resolveNotClosed", &TableTest_resolveNotClosed);
	test("resolveNotConsistent", &TableTest_resolveNotConsistent);
	test("addStringToS", &TableTest_addStringToS);
	test("addStringToE", &TableTest_addStringToE);
	test("addEntry", &TableTest_addEntry);
	test("isInTable", &TableTest_isInTable);
	test("isMember", &TableTest_isMember);
	test("row", &TableTest_row);
	test("areRowsEqual", &TableTest_areRowsEqual);

}