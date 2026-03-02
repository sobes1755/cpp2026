.POSIX:

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: println insertion

insertion: insertion.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

println: println.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

PHONY: run

run:
	./insertion
	./println

.PHONY: clean

clean:
	-rm ./insertion
	-rm ./println
