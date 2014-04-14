CC=g++
CXXFLAGS=-Wall

INC=include/
SRC=src/*.cpp
CXXFLAGS=-Wall -std=c++11 -I$(INC)
TARGET=bin/rsl.out

all:
	$(CC) $(CXXFLAGS) $(SRC) -o $(TARGET)
