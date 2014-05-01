////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#ifndef TEACHER_H
#define TEACHER_H

#include <string>

#include "alphabet.h"
#include "common.h"
#include "dfa.h"

class Teacher {
public:
	virtual ~Teacher(){};
	virtual bool askMembership(String query) = 0;
	virtual std::unique_ptr<Alphabet> askAlphabet() = 0;
	virtual bool makeConjecture(std::unique_ptr<Dfa> dfa) = 0;
	virtual String getCounterExample() = 0;
};

#endif