CC=g++
CXXFLAGS=-Wall

INC=include/
SRC=src/*.cpp
CXXFLAGS=-Wall -g -std=c++11 -I$(INC)
TARGET=bin/rsl.out

all: test rsl
	@echo done

test:
	@echo Building tests... 
	$(CC) $(CXXFLAGS) -Itests/ tests/*.cpp $(filter-out src/main.cpp, $(wildcard src/*.cpp))  -o bin/tests.out
	@echo "...Done"
	@echo "\nRunning tests..."
	@./bin/tests.out
	@echo "...Done\n"

	

rsl:
	@echo Building rsl...
	$(CC) $(CXXFLAGS) $(SRC) -o $(TARGET)
