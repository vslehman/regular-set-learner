////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include "console_teacher.h"
#include "common.h"
#include "demo_teacher.h"
#include "learner.h"
#include <iostream>

//==============================================================================
// int main()
//------------------------------------------------------------------------------
int main(int argc, char ** argv) {
	
	bool isDemo = false;
	String demoFile;
	int playbackSpeed = 6;
	
	for (int i = 0; i < argc; i++) {
		String arg = argv[i];
		if (arg == "-d") {
			i++;
			isDemo = true;
			if (i < argc) {
				demoFile = argv[i];

				i++;
				if (i < argc) {
					playbackSpeed = atoi(argv[i]);
				}
			}
			else {
				std::cout << "Error: Please provide a demo file to play\n";
				exit(1);
			}
		}
	}
	
	if (isDemo) {
		DemoTeacher demoTeacher(demoFile, playbackSpeed);
		Learner demoLearner;
		demoLearner.start(demoTeacher);
	}
	else {
		ConsoleTeacher teacher;
		Learner learner;
	
		learner.start(teacher);
	}
	
	return 0;
}