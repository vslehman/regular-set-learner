////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include "console_teacher.h"
#include "demo_teacher.h"
#include "learner.h"

//==============================================================================
// int main()
//------------------------------------------------------------------------------
int main(int argc, char ** argv) {
	
	DemoTeacher demoTeacher;
	Learner demoLearner;
	
	demoLearner.start(demoTeacher);
	
	ConsoleTeacher teacher;
	Learner learner;
	
	learner.start(teacher);
	
	return 0;
}