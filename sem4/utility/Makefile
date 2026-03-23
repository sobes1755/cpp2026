.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

SRCS = $(wildcard *.cpp)
BINS = $(SRCS:.cpp=)

.PHONY: all

all: $(BINS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

safecomp: safecomp.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -Wno-sign-compare

.PHONY: clean

clean:
	rm -f $(BINS)
