.POSIX:

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: class

class: class.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

PHONY: run

run:
	./class

.PHONY: clean

clean:
	-rm ./class
