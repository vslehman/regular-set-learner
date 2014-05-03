CC=g++
CXXFLAGS=-Wall

INC=include/
SRC=src/*.cpp
TESTS_INC=-Itests/include/
TESTS_SRC=tests/src/*.cpp $(filter-out src/main.cpp, $(wildcard src/*.cpp))
TESTS_TARGET=-o bin/tests.out
CXXFLAGS=-Wall -g -std=c++11 -I$(INC)
TARGET=bin/rsl.out

all: test rsl
	@echo done

test:
	@echo Building tests... 
	$(CC) $(CXXFLAGS) $(TESTS_INC) $(TESTS_SRC) $(TESTS_TARGET) 
	@echo "...Done"
	@echo "\nRunning tests..."
	@./bin/tests.out
	@echo "...Done\n"

	

rsl:
	@echo Building rsl...
	$(CC) $(CXXFLAGS) $(SRC) -o $(TARGET)
