.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: ruleoffive

ruleoffive: ruleoffive.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

PHONY: run

run:
	./ruleoffive

.PHONY: clean

clean:
	-rm ./ruleoffive
