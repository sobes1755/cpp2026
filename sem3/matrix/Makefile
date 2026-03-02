.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: matrix

matrix: matrix.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

PHONY: run

run:
	./matrix

.PHONY: clean

clean:
	-rm ./matrix
