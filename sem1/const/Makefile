.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

.PHONY: all

all: constexpr consteval

constexpr: constexpr.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

consteval: consteval.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

PHONY: run

run:
	./constexpr
	./consteval

.PHONY: clean

clean:
	-rm ./constexpr
	-rm ./consteval
