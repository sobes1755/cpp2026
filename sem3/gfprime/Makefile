.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: gfprime

gfprime: gfprime.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

PHONY: run

run:
	./gfprime

.PHONY: clean

clean:
	-rm ./gfprime
