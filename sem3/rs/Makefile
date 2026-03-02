.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: rs

rs: rs.cpp gfprime.h matrix.h
	$(CXX) rs.cpp -o $@ $(CXXFLAGS)

PHONY: run

run:
	./rs

.PHONY: clean

clean:
	-rm ./rs
