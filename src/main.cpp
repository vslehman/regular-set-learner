////////////////////////////////////////////////////////////////////////////////
// Vince Lehman
// COMP 4601
////////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "common.hpp"
#include "auto_teacher.hpp"
#include "console_teacher.hpp"
#include "demo_teacher.hpp"
#include "learner.hpp"

//==============================================================================
// int main()
//------------------------------------------------------------------------------
int main(int argc, char ** argv) {
	
	for (int i = 0; i < argc; i++) {
		String arg = argv[i];
		
		// Demo Teacher
		if (arg == "-d") {
			i++;
			if (i < argc) {
				String demoFile = argv[i++];

				int playbackSpeed = 6;
				if (i < argc) {
					playbackSpeed = atoi(argv[i]);
				}
				
				DemoTeacher demoTeacher(demoFile, playbackSpeed);
				Learner demoLearner;
				demoLearner.start(demoTeacher);
				
				return 0;
			}
			else {
				std::cout << "Error: Please provide a demo file to play\n";
				exit(1);
			}
		} // Automated Teacher
		else if (arg == "-a") {
			i++;
			if (i < argc) {
				String dfaFile = argv[i++];
				
				AutoTeacher teacher(dfaFile);
				Learner learner;
				learner.start(teacher);
				
				return 0;
			}
			else {
				std::cout << "Error: Please provide a DFA file\n";
				exit(1);
			}
		}
	}
	
	 // Human Teacher
	ConsoleTeacher teacher;
	Learner learner;
		
	learner.start(teacher);
	
	return 0;
}