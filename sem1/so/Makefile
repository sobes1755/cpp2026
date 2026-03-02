.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: libctrdtrlib.so main

libctrdtrlib.so: ctrdtrlib.cpp
	$(CXX) $(CXXFLAGS) -fPIC -shared $< -o $@

main: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -L. -lctrdtrlib

PHONY: run

run:
	readelf -l ./main
	LD_LIBRARY_PATH=. ./main

.PHONY: clean

clean:
	-rm -f ./libctrdtrlib.so
	-rm -f ./main
