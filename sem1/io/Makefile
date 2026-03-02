.POSIX:

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: int char get getline sstream

int: int.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

char: char.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

get: get.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

getline: getline.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

sstream: sstream.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

PHONY: run

run:
	./int
	./char
	./get
	./getline
	./sstream

.PHONY: clean

clean:
	-rm ./int
	-rm ./char
	-rm ./get
	-rm ./getline
	-rm ./sstream
