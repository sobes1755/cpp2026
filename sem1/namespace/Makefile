.POSIX:

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: numbers using

numbers: numbers.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

using: using.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

PHONY: run

run:
	./numbers
	./using

.PHONY: clean

clean:
	-rm ./numbers
	-rm ./using
