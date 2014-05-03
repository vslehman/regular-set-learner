////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef TEACHER_HPP
#define TEACHER_HPP

#include <string>

#include "alphabet.hpp"
#include "common.hpp"
#include "dfa.hpp"

class Teacher {
public:
	virtual ~Teacher(){};
	virtual bool askMembership(String query) = 0;
	virtual Alphabet askAlphabet() = 0;
	virtual bool makeConjecture(Dfa &dfa) = 0;
	virtual String getCounterExample() = 0;
};

#endif