.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: toupper

toupper: toupper.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

PHONY: run

run:
	tr -dc '[:alnum:] \n' < /dev/urandom | head -c 256M > random.txt 
	time -p ./toupper < random.txt > upper.txt

.PHONY: clean

clean:
	-rm ./random.txt
	-rm ./upper.txt
	-rm ./toupper
