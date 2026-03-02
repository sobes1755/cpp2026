.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: welford normal

welford: welford.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

normal: normal.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

PHONY: run

run:
	./normal 123.456 7.89 1048576 > doubles.txt
	./welford < doubles.txt

.PHONY: clean

clean:
	-rm ./doubles.txt
	-rm ./normal
	-rm ./welford

